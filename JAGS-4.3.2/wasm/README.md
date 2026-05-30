# JAGS WASM proof of concept

This directory contains a browser-oriented build scaffold for the JAGS core
library plus the statically linked `basemod` and `bugs` modules. It bypasses the
native terminal frontend and exposes a small C ABI from `jags_wasm.cc`.

## Build

On macOS with Homebrew Emscripten:

```sh
cd /Users/rasmus.b/Desktop/web-jags/JAGS-4.3.2
env PATH=/opt/homebrew/bin:$PATH emcmake cmake -S wasm -B wasm/build -G Ninja
env PATH=/opt/homebrew/bin:$PATH cmake --build wasm/build -j4
```

If Emscripten needs to populate its Homebrew cache for the first time, the build
must be allowed to write under `/opt/homebrew`.

## Smoke Test

```sh
cd /Users/rasmus.b/Desktop/web-jags/JAGS-4.3.2
env PATH=/opt/homebrew/bin:$PATH node wasm/smoke.js
```

The smoke test compiles a small normal model, runs 100 iterations, and prints a
JSON summary of the monitor output.

## Browser Example

```sh
cd /Users/rasmus.b/Desktop/web-jags/JAGS-4.3.2
python3 -m http.server 8765 --bind 127.0.0.1
```

Then open:

```text
http://127.0.0.1:8765/wasm/example/
```

The example page loads `wasm/build/jags.js`, runs the preloaded regression model,
and visualizes posterior traces, histograms, and the fitted regression line with
Plotly.

The fuller spreadsheet app is available at:

```text
http://127.0.0.1:8765/wasm/studio/
```

It uses a ragged spreadsheet-style data table. The first row names variables,
blank cells are ignored, and unobserved stochastic parameters are discovered from
the initialized model and monitored automatically.

## Numerical Backend

`bugs` is linked with `wasm/lapack_fallback.cc`. The BLAS subset covers simple
vector and matrix operations, and the fallback now includes small dense
implementations for the LAPACK calls needed by the classic BUGS multivariate
normal, Wishart, matrix inverse, and log-determinant examples.

This is still a proof-of-concept backend. For larger models, better numerical
coverage, and stronger performance, replace the fallback with a maintained WASM
BLAS/LAPACK build.
