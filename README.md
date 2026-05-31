# JAGS WebAssembly Experiment

> [!WARNING]
> This is an unofficial **100% vibecoded** experiment. 
> This was basically me asking my friendly neighbourhood LLM to 
> "PLease compile JAGS to wasm", and to my surprize it mostly seems to work.
> But! It is not anything close to a production ready,
> not a supported JAGS distribution, and should not be relied on for anything.
> Treat the browser output as a technical demo only.

## Important Attribution And Status

[JAGS](https://mcmc-jags.sourceforge.io/) is Martin Plummer's "Just Another
Gibbs Sampler" project. This repository is not JAGS itself, is not an official
JAGS distribution, and is not affiliated with or endorsed by Martin Plummer.
For the official project, documentation, and releases, use the
[JAGS website](https://mcmc-jags.sourceforge.io/). For general background, see
the [JAGS Wikipedia page](https://en.wikipedia.org/wiki/Just_another_Gibbs_sampler).

This repository is only a quick proof-of-concept compilation of JAGS 4.3.2 to
WebAssembly for browser experiments. It is intentionally named and documented as
an experiment because it should not be treated as a reliable JAGS runtime.

The experiment keeps the upstream JAGS source tree as a drop-in folder, adds a
small WebAssembly wrapper, ships a prebuilt OpenBLAS-backed runtime, and
includes browser demos plus Classic BUGS benchmarks.

If publishing this repository, use a name like `web-jags-experiment` rather than
`web-jags` to make the experimental status visible in URLs and clone commands.

## Layout

- `JAGS-4.3.2/`: original JAGS source. The WebAssembly port does not live inside
  this folder, so this tree can be replaced with a fresh upstream source tree.
- `wasm-port/`: CMake build scaffold, C ABI wrapper, BLAS/LAPACK helper, R V8
  helper, and build/smoke-test tools.
- `dist/openblas/`: prebuilt browser runtime: `jags.js`, `jags.wasm`, and
  `jags-file.js`. The `jags-file.js` variant embeds the wasm binary for
  `file://` demos.
- `demos/minimal-server/`: smallest server-based HTML demo. It loads
  `dist/openblas/jags.js`, runs a tiny model on page load, and prints output.
- `demos/minimal-file/`: smallest double-clickable HTML demo. It loads
  `dist/openblas/jags-file.js` and does not need a local web server.
- `demos/bugs-studio/`: editable Classic BUGS studio with all 47 bundled example
  models and JSON data.
- `benchmarks/classic-bugs/`: R benchmark and generation scripts for comparing
  `rjags` against the WASM runtime via the R `V8` package.
- `classic-bugs/`: Classic BUGS example corpus tuned for JAGS.
- `LICENSES/`: license copies for bundled third-party runtime components.

## Run The Demos

For the server-based demos, serve the repository root:

```sh
cd /path/to/web-jags-experiment
python3 -m http.server 8765 --bind 127.0.0.1
```

Then open:

```text
http://127.0.0.1:8765/demos/minimal-server/
http://127.0.0.1:8765/demos/bugs-studio/
```

The file-based minimal demo can be opened directly in Chrome:

```text
demos/minimal-file/index.html
```

The richer BUGS studio still benefits from a local server because it loads
Plotly from a CDN and uses several local files. The minimal file demo is the
intended no-server example.

## Build The Runtime

Install the moving pieces on macOS with Homebrew:

```sh
brew install emscripten cmake ninja node jags
```

For the R benchmark helpers, also install the R packages:

```r
install.packages(c("V8", "jsonlite", "coda", "rjags"))
```

Build OpenBLAS and the supplemental C-LAPACK subset used by JAGS:

```sh
cd /path/to/web-jags-experiment
env PATH=/opt/homebrew/bin:$PATH wasm-port/tools/build-openblas-wasm.sh
env PATH=/opt/homebrew/bin:$PATH wasm-port/tools/build-lapack-extra-wasm.sh
env PATH=/opt/homebrew/bin:$PATH wasm-port/tools/check-openblas-symbols.sh \
  "$(find wasm-port/third_party/OpenBLAS -maxdepth 1 -name 'libopenblas*.a' | sort | tail -n 1)" \
  wasm-port/build/libjags_lapack_extra.a
env PATH=/opt/homebrew/bin:$PATH wasm-port/tools/run-lapack-extra-smoke.sh
```

Compile JAGS to WebAssembly and refresh `dist/openblas/`:

```sh
cd /path/to/web-jags-experiment
OPENBLAS_LIB="$(find wasm-port/third_party/OpenBLAS -maxdepth 1 -name 'libopenblas*.a' | sort | tail -n 1)"

env PATH=/opt/homebrew/bin:$PATH emcmake cmake -S wasm-port -B build/wasm-openblas -G Ninja \
  -DJAGS_ROOT="$PWD/JAGS-4.3.2" \
  -DJAGS_WASM_NUMERIC_BACKEND=openblas \
  -DJAGS_WASM_OPENBLAS_LIB="$OPENBLAS_LIB" \
  -DJAGS_WASM_LAPACK_EXTRA_LIB="$PWD/wasm-port/build/libjags_lapack_extra.a"
env PATH=/opt/homebrew/bin:$PATH cmake --build build/wasm-openblas -j4

mkdir -p dist/openblas
cp build/wasm-openblas/jags.js dist/openblas/jags.js
cp build/wasm-openblas/jags.wasm dist/openblas/jags.wasm
node wasm-port/tools/bundle-file-runtime.mjs dist/openblas
```

Run the Node smoke test:

```sh
env PATH=/opt/homebrew/bin:$PATH node wasm-port/smoke.js
```

## Benchmarks

The benchmark script runs each Classic BUGS case twice: once with `rjags`, and
once by loading `dist/openblas/jags.js` plus `dist/openblas/jags.wasm` through
the R `V8` package.

```sh
Rscript benchmarks/classic-bugs/benchmark-wasm.R
```

Useful quick smoke variant:

```sh
Rscript benchmarks/classic-bugs/benchmark-wasm.R --max_cases=3 --min_iter=50
```

Regenerate the browser example bundle after changing the Classic BUGS inputs or
after producing a new curated benchmark CSV:

```sh
Rscript benchmarks/classic-bugs/generate-classic-bugs-studio.R /path/to/web-jags-experiment
```

## Design Decisions And Limits

The WebAssembly runtime statically links the JAGS core plus the `base` and
`bugs` modules. It does not currently support dynamic JAGS module loading.

The public experiment ships only the OpenBLAS-backed runtime. The older handwritten
fallback BLAS/LAPACK path remains in `wasm-port/src/lapack_fallback.cc` for
experimentation, but it is not published in `dist/` because it is not a
production numerical backend.

OpenBLAS is built with `NOFORTRAN=1`, which gives a strong BLAS layer but not a
complete LAPACK distribution. The supplemental script compiles the transitive
C-LAPACK routines JAGS needs for the currently linked `base` and `bugs` modules.
That has run the 47 Classic BUGS examples successfully in this proof of concept,
but it should still be treated as a verified JAGS subset rather than a certified
complete LAPACK port.

The browser studio’s automatic monitor selection is demo-layer JavaScript, not a
JAGS core feature. It derives monitor candidates from the visible model/data and
caps displayed parameter series at 30 to avoid huge latent arrays dominating the
UI.

The runtime is single-threaded and uses WebAssembly memory growth. Large models
can still be slow or memory-heavy in a browser tab.

## Licensing

JAGS is GPL-2. OpenBLAS is BSD-licensed. This repository includes license copies
under `LICENSES/`; check those terms before publishing or redistributing builds.
