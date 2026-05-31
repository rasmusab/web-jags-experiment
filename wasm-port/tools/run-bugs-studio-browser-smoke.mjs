#!/usr/bin/env node

import fs from "node:fs/promises";

const defaults = {
  cdp: "http://127.0.0.1:9222",
  url: "http://127.0.0.1:8765/demos/bugs-studio/?runtime=openblas",
  adapt: 20,
  burnin: 20,
  samples: 50,
  timeoutMs: 120000,
  pollMs: 500,
};

function parseArgs(argv) {
  const options = { ...defaults };
  for (const arg of argv) {
    const match = arg.match(/^--([^=]+)=(.*)$/);
    if (!match) {
      throw new Error(`Unknown argument: ${arg}`);
    }
    const [, key, value] = match;
    if (["adapt", "burnin", "samples", "timeoutMs", "pollMs", "limit"].includes(key)) {
      options[key] = Number(value);
    } else {
      options[key] = value;
    }
  }
  return options;
}

function timestamp() {
  return new Date().toISOString().replace(/[-:]/g, "").replace(/[.].*/, "");
}

function cacheBustUrl(url) {
  const parsed = new URL(url);
  parsed.searchParams.set("smoke", String(Date.now()));
  return parsed.toString();
}

async function fetchJson(url, options = {}) {
  const response = await fetch(url, options);
  if (!response.ok) {
    throw new Error(`${url}: HTTP ${response.status}`);
  }
  return response.json();
}

async function createTarget(cdpBase, url) {
  const endpoint = `${cdpBase.replace(/\/$/, "")}/json/new?${encodeURIComponent(url)}`;
  try {
    return await fetchJson(endpoint, { method: "PUT" });
  } catch (_error) {
    return fetchJson(endpoint);
  }
}

class CDPClient {
  constructor(wsUrl) {
    this.wsUrl = wsUrl;
    this.nextId = 1;
    this.pending = new Map();
    this.handlers = new Map();
  }

  async connect() {
    this.socket = new WebSocket(this.wsUrl);
    await new Promise((resolve, reject) => {
      this.socket.addEventListener("open", resolve, { once: true });
      this.socket.addEventListener("error", reject, { once: true });
    });
    this.socket.addEventListener("message", (event) => this.onMessage(event));
  }

  onMessage(event) {
    const message = JSON.parse(event.data);
    if (message.id && this.pending.has(message.id)) {
      const { resolve, reject } = this.pending.get(message.id);
      this.pending.delete(message.id);
      if (message.error) {
        reject(new Error(message.error.message || JSON.stringify(message.error)));
      } else {
        resolve(message.result || {});
      }
      return;
    }
    if (message.method && this.handlers.has(message.method)) {
      for (const handler of this.handlers.get(message.method)) {
        handler(message.params || {});
      }
    }
  }

  on(method, handler) {
    if (!this.handlers.has(method)) {
      this.handlers.set(method, []);
    }
    this.handlers.get(method).push(handler);
  }

  send(method, params = {}) {
    const id = this.nextId++;
    this.socket.send(JSON.stringify({ id, method, params }));
    return new Promise((resolve, reject) => {
      this.pending.set(id, { resolve, reject });
    });
  }

  close() {
    this.socket?.close();
  }
}

async function evaluate(client, expression, options = {}) {
  const result = await client.send("Runtime.evaluate", {
    expression,
    awaitPromise: options.awaitPromise ?? false,
    returnByValue: true,
    userGesture: options.userGesture ?? false,
  });
  if (result.exceptionDetails) {
    throw new Error(result.exceptionDetails.text || "Runtime.evaluate failed");
  }
  return result.result?.value;
}

function jsString(value) {
  return JSON.stringify(String(value));
}

async function pageState(client) {
  return evaluate(client, `(() => {
    const text = (selector) => document.querySelector(selector)?.textContent?.trim() || "";
    return {
      url: location.href,
      title: document.title,
      status: text("#status"),
      isError: document.querySelector("#status")?.classList.contains("error") || false,
      runDisabled: document.querySelector("#run-button")?.disabled ?? true,
      parameterCount: text("#parameter-count"),
      sampleCount: text("#sample-count"),
      elapsed: text("#elapsed-time"),
      summaryRows: document.querySelectorAll("#summary-table tbody tr").length,
      plotCards: document.querySelectorAll(".parameter-card").length,
      examples: Array.isArray(window.CLASSIC_BUGS_EXAMPLES)
        ? window.CLASSIC_BUGS_EXAMPLES.map((example) => example.id)
        : [],
      hasPlotly: typeof window.Plotly === "object",
    };
  })()`);
}

async function waitFor(client, predicate, timeoutMs, pollMs, label) {
  const start = Date.now();
  let last;
  while (Date.now() - start < timeoutMs) {
    last = await pageState(client);
    if (predicate(last)) {
      return last;
    }
    await new Promise((resolve) => setTimeout(resolve, pollMs));
  }
  throw new Error(`${label} timed out after ${timeoutMs} ms. Last state: ${JSON.stringify(last)}`);
}

async function waitForReady(client, options) {
  return waitFor(
    client,
    (state) => state.status.startsWith("Ready") && !state.runDisabled &&
      state.examples.length > 0 && state.hasPlotly,
    options.timeoutMs,
    options.pollMs,
    "bugs-studio ready",
  );
}

async function runExample(client, id, options) {
  await evaluate(client, `(() => {
    const setValue = (selector, value) => {
      const input = document.querySelector(selector);
      input.value = String(value);
      input.dispatchEvent(new Event("input", { bubbles: true }));
      input.dispatchEvent(new Event("change", { bubbles: true }));
    };
    const select = document.querySelector("#example-select");
    select.value = ${jsString(id)};
    select.dispatchEvent(new Event("change", { bubbles: true }));
    setValue("#adapt-input", ${options.adapt});
    setValue("#burnin-input", ${options.burnin});
    setValue("#iterations-input", ${options.samples});
    document.querySelector("#run-button").click();
  })()`, { userGesture: true });

  const started = Date.now();
  const finalState = await waitFor(
    client,
    (state) => !state.runDisabled &&
      !state.status.startsWith("Starting") &&
      !state.status.startsWith("Running"),
    options.timeoutMs,
    options.pollMs,
    `run ${id}`,
  );

  return {
    id,
    ok: finalState.status.startsWith("Complete.") && !finalState.isError,
    wallMs: Date.now() - started,
    status: finalState.status,
    parameterCount: finalState.parameterCount,
    sampleCount: finalState.sampleCount,
    elapsed: finalState.elapsed,
    summaryRows: finalState.summaryRows,
    plotCards: finalState.plotCards,
  };
}

async function navigate(client, url) {
  await client.send("Page.navigate", { url });
}

async function main() {
  const options = parseArgs(process.argv.slice(2));
  const target = await createTarget(options.cdp, options.url);
  if (!target.webSocketDebuggerUrl) {
    throw new Error("Chrome target did not include a webSocketDebuggerUrl");
  }

  const client = new CDPClient(target.webSocketDebuggerUrl);
  const events = [];
  await client.connect();
  client.on("Runtime.exceptionThrown", (params) => {
    events.push({
      level: "exception",
      text: params.exceptionDetails?.text || params.exceptionDetails?.exception?.description || "",
      ts: Date.now(),
    });
  });
  client.on("Runtime.consoleAPICalled", (params) => {
    events.push({
      level: params.type,
      text: (params.args || []).map((arg) => arg.value ?? arg.description ?? "").join(" "),
      ts: Date.now(),
    });
  });
  client.on("Log.entryAdded", (params) => {
    events.push({
      level: params.entry?.level || "log",
      text: params.entry?.text || "",
      ts: Date.now(),
    });
  });

  await client.send("Runtime.enable");
  await client.send("Page.enable");
  await client.send("Network.enable");
  await client.send("Network.setCacheDisabled", { cacheDisabled: true });
  await client.send("Log.enable");
  const runUrl = cacheBustUrl(options.url);
  await navigate(client, runUrl);
  await waitForReady(client, options);

  const initial = await pageState(client);
  const ids = options.limit ? initial.examples.slice(0, options.limit) : initial.examples;
  const results = [];

  for (let index = 0; index < ids.length; index += 1) {
    const id = ids[index];
    const eventStart = events.length;
    process.stdout.write(`[${index + 1}/${ids.length}] ${id} ... `);
    try {
      const result = await runExample(client, id, options);
      result.events = events.slice(eventStart);
      results.push(result);
      console.log(result.ok ? `ok ${result.wallMs}ms` : `FAIL ${result.status}`);
      if (!result.ok) {
        await navigate(client, cacheBustUrl(options.url));
        await waitForReady(client, options);
      }
    } catch (error) {
      const result = {
        id,
        ok: false,
        error: error.message,
        events: events.slice(eventStart),
      };
      results.push(result);
      console.log(`ERROR ${error.message}`);
      await navigate(client, cacheBustUrl(options.url));
      await waitForReady(client, options);
    }
  }

  const outFile = options.out ||
    `demos/bugs-studio/browser-smoke-results-${timestamp()}.json`;
  const report = {
    generatedAt: new Date().toISOString(),
    url: runUrl,
    settings: {
      adapt: options.adapt,
      burnin: options.burnin,
      samples: options.samples,
      timeoutMs: options.timeoutMs,
    },
    summary: {
      total: results.length,
      ok: results.filter((result) => result.ok).length,
      failed: results.filter((result) => !result.ok).length,
    },
    results,
  };
  await fs.writeFile(outFile, `${JSON.stringify(report, null, 2)}\n`);
  console.log(`Wrote ${outFile}`);
  console.log(JSON.stringify(report.summary));
  client.close();
}

main().catch((error) => {
  console.error(error.stack || error.message);
  process.exit(1);
});
