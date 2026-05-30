# BLAS/LAPACK options for JAGS WASM

This note records the current state of the BLAS/LAPACK issue for the JAGS
browser proof of concept.

## Current dependency surface

The current WASM build links the JAGS core plus `basemod` and `bugs`. In that
configuration, JAGS needs a Fortran-style BLAS/LAPACK ABI with underscore
symbols such as `dgemm_` and `dsyev_`.

The active base+bugs surface is small:

- BLAS level 1: `ddot`, `dcopy`, `dscal`, `daxpy`
- BLAS level 2/3: `dgemv`, `dgemm`, `dsyr`, `dsymm`, `dsyrk`, `dtrmm`
- LAPACK: `dsyev`, `dgesv`, `dsysv`, `dposv`, `dpotrf`, `dpotri`, `dtrtri`
- Utility: `dlange`

There are dormant or module-specific references to `dgeev`, `dgeqrf`, and
`dgeqp3`, but they are not active in the current base+bugs build.

The current local `lapack_fallback.cc` implements this subset directly. That is
enough for the classic BUGS benchmark, but it is not the same as linking a
maintained LAPACK implementation.

## Options researched

### 1. OpenBLAS built for WebAssembly

OpenBLAS is now the strongest candidate. Its upstream README lists a WASM target
and describes `WASM128_GENERIC` as portable WebAssembly for browser use:

https://github.com/OpenMathLib/OpenBLAS

The same README says OpenBLAS requires a Fortran compiler for LAPACK, but can
compile an older machine-translated C LAPACK when Fortran is not available.
That is important because Emscripten does not provide a normal Fortran compiler.

There is also prior art from Pyodide/OpenBLAS: an OpenBLAS issue describes an
Emscripten WebAssembly build used via SciPy and gives this example command:

```sh
make libs shared CC=emcc HOSTCC=gcc TARGET=RISCV64_GENERIC NOFORTRAN=1 NO_LAPACKE=1 USE_THREAD=0 -O2
```

https://github.com/OpenMathLib/OpenBLAS/issues/4023

This validates that OpenBLAS can be built for WASM, but that example explicitly
uses `NOFORTRAN=1` and `NO_LAPACKE=1`; for JAGS we must verify exactly which
LAPACK symbols are present in the resulting archive.

### 2. CLAPACK / f2c-translated LAPACK

CLAPACK is the historical C translation of the Fortran 77 LAPACK sources. Netlib
describes it as LAPACK translated with `f2c`, with the goal of supporting users
without a Fortran compiler:

https://www.netlib.org/clapack/faq.html

This is likely the safest route for complete LAPACK symbol coverage under
Emscripten if OpenBLAS' `NOFORTRAN=1` build does not export the needed routines.
The downsides are age, build-system cleanup, and code size. The upside is ABI
fit: JAGS already calls the Fortran routines directly.

### 3. LFortran building Netlib BLAS/LAPACK to WASM

LFortran is promising but not the most pragmatic first choice. Its site says it
supports WebAssembly and has a February 2026 milestone for compiling LAPACK, but
also says LFortran is alpha and third-party codes may fail:

https://lfortran.org/

This is worth tracking, and possibly worth a spike, but it is not the lowest
risk dependency for a browser-facing JAGS runtime today.

### 4. Eigen-backed ABI shim

Eigen is header-only and compiles cleanly with Emscripten. Eigen itself documents
that it can use external BLAS/LAPACK, but here the interesting direction would be
the reverse: implement JAGS' Fortran ABI symbols by forwarding to Eigen
algorithms.

https://libeigen.gitlab.io/eigen/docs-nightly/TopicUsingBlasLapack.html

This would be cleaner than the current hand-written fallback, especially for
`dsyev`, Cholesky, inverse, and LU. It would still not be "complete LAPACK"; it
would be a maintained C++ implementation for the specific ABI subset JAGS uses.

### 5. Emscripten-forge / packaged scientific stack

Emscripten-forge provides WebAssembly packages used by JupyterLite/Xeus. It is a
good signal that the scientific-WASM ecosystem is maturing:

https://emscripten-forge.org/usage/jupyterlite/

For this project, it is more useful as prior art than as an immediate dependency
source. Pulling a package-built OpenBLAS into our standalone Emscripten CMake
build may be more complicated than vendoring/building the library directly.

## Recommendation

The most credible production path is:

1. Keep `lapack_fallback.cc` as a tiny internal fallback and test oracle.
2. Add a build option `JAGS_WASM_BLAS=openblas`.
3. Vendor or fetch OpenBLAS into `JAGS-4.3.2/wasm/third_party/openblas`.
4. Build OpenBLAS with Emscripten, single-threaded, no dynamic architecture, no
   host CPU detection.
5. Inspect the generated archive with `llvm-nm`/`emar t` to verify these exact
   symbols: `dsyev_`, `dgesv_`, `dposv_`, `dpotrf_`, `dpotri_`, `dtrtri_`,
   `dtrmm_`, `dsyrk_`, `dgemm_`, `dgemv_`, `ddot_`, `daxpy_`, `dcopy_`,
   `dscal_`, `dsyr_`, `dsymm_`, `dsysv_`, `dlange_`.
6. If OpenBLAS does not provide all LAPACK symbols under `NOFORTRAN=1`, add
   CLAPACK only for the missing LAPACK routines and use OpenBLAS for BLAS.
7. Run three layers of tests:
   - direct BLAS/LAPACK numeric tests against native R/LAPACK tolerances;
   - classic BUGS 47-case benchmark;
   - synthetic stress models with larger `dmnorm`, `dwish`, `inverse`, and
     `matmult` dimensions.

This gives much higher confidence than extending the local fallback one routine
at a time, while keeping the build browser-compatible.

## Executed spike

The OpenBLAS WASM spike was executed locally with:

```sh
TARGET=WASM128_GENERIC CC=emcc HOSTCC=cc AR=emar RANLIB=emranlib \
  NOFORTRAN=1 NO_LAPACKE=1 USE_THREAD=0 NUM_THREADS=1 DYNAMIC_ARCH=0
```

Result: OpenBLAS alone is not sufficient for JAGS base+bugs. Its WASM archive
exports 13 of the 18 active symbols:

```text
present: ddot_ dcopy_ dscal_ daxpy_ dgemv_ dgemm_ dsyr_ dsymm_
         dsyrk_ dtrmm_ dgesv_ dpotrf_ dtrtri_
missing: dlange_ dsyev_ dsysv_ dposv_ dpotri_
```

The workable solution is OpenBLAS for BLAS plus a generated supplemental
C-LAPACK archive for the transitive JAGS LAPACK subset. The supplemental archive
is built by `tools/build-lapack-extra-wasm.sh` from OpenBLAS'
`lapack-netlib/SRC` and `lapack-netlib/INSTALL` C sources.

Important WebAssembly-specific issue: the f2c/OpenBLAS C sources mix `int` and
`void` signatures for translated Fortran subroutines. Native linking tolerates
this, but WebAssembly function types are strict and the mismatch caused runtime
`unreachable` traps in `dpotri_`. The supplement builder now patches copied
sources so translated subroutines use the `void` ABI expected by JAGS.

Verification performed:

- `tools/check-openblas-symbols.sh` reports 18/18 required symbols when run on
  the OpenBLAS archive plus `wasm/build/libjags_lapack_extra.a`.
- `tools/lapack-extra-smoke.c` calls `dpotrf_`, `dpotri_`, `dsyev_`, and
  `dgesv_` directly through a small Emscripten program; it passes.
- The OpenBLAS-backed JAGS build passes `wasm/smoke.js`.
- The scaled classic BUGS benchmark passes execution coverage with
  `rjags_ok=47/47` and `wasm_ok=47/47`
  (`classic-bugs-benchmark-20260530-223948.csv`).
- At the short benchmark scale, 42/47 cases are comparable at `max_abs_z <= 2`.
  A longer targeted rerun of the five outliers improved three of them; the
  remaining `epil` cases are also outliers with the old fallback and are more
  likely short-chain Monte Carlo comparison noise than BLAS/LAPACK failures.

The only remaining linker warning is `xerbla_`: OpenBLAS' BLAS error path uses
an `int` signature, while the supplemental LAPACK archive provides a `void`
Fortran-subroutine signature. This should not affect valid BLAS calls, but it is
worth eliminating before treating the OpenBLAS backend as release quality.

## Risk notes

- Complete LAPACK is probably unnecessary for JAGS base+bugs. A verified
  complete subset is a better target than linking the whole LAPACK universe.
- Optional `glm` support is a separate project. JAGS' `glm` module includes
  SuiteSparse/CHOLMOD code paths that call additional BLAS routines such as
  `dtrsv`, `dtrsm`, `dger`, complex BLAS, and `zpotrf`. That should be handled
  after base+bugs has a proper backend.
- Browser threads/SIMD can improve performance, but they complicate deployment
  because threaded WASM needs cross-origin isolation headers. Start
  single-threaded.
- The OpenBLAS WASM target improves BLAS coverage and performance, but it does
  not automatically prove LAPACK coverage. The archive symbol check is mandatory.
