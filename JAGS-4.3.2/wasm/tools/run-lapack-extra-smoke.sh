#!/usr/bin/env bash
set -euo pipefail

script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
wasm_dir="$(cd "${script_dir}/.." && pwd)"
openblas_dir="${OPENBLAS_DIR:-${wasm_dir}/third_party/OpenBLAS}"
openblas_archive="${JAGS_WASM_OPENBLAS_LIB:-}"
lapack_extra_archive="${JAGS_WASM_LAPACK_EXTRA_LIB:-${wasm_dir}/build/libjags_lapack_extra.a}"
build_dir="${JAGS_WASM_SMOKE_BUILD_DIR:-${wasm_dir}/build/lapack-extra-smoke}"

if ! command -v emcc >/dev/null 2>&1 && [ -d /opt/homebrew/bin ]; then
    export PATH="/opt/homebrew/bin:${PATH}"
fi

for tool in emcc node; do
    if ! command -v "${tool}" >/dev/null 2>&1; then
        echo "Missing required tool: ${tool}" >&2
        exit 2
    fi
done

if [ -z "${openblas_archive}" ]; then
    openblas_archive="$(find "${openblas_dir}" -maxdepth 1 -name 'libopenblas*.a' -print 2>/dev/null | sort | tail -n 1)"
fi

if [ -z "${openblas_archive}" ] || [ ! -f "${openblas_archive}" ]; then
    echo "OpenBLAS archive not found. Run tools/build-openblas-wasm.sh first." >&2
    exit 2
fi
if [ ! -f "${lapack_extra_archive}" ]; then
    echo "LAPACK extra archive not found. Run tools/build-lapack-extra-wasm.sh first." >&2
    exit 2
fi

mkdir -p "${build_dir}"

emcc -O2 -msimd128 -sALLOW_MEMORY_GROWTH=1 \
    "${script_dir}/lapack-extra-smoke.c" \
    "${lapack_extra_archive}" \
    "${openblas_archive}" \
    -o "${build_dir}/lapack-extra-smoke.js"

node "${build_dir}/lapack-extra-smoke.js"
