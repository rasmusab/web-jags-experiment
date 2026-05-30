#!/usr/bin/env bash
set -euo pipefail

script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
wasm_dir="$(cd "${script_dir}/.." && pwd)"
third_party_dir="${JAGS_WASM_THIRD_PARTY:-${wasm_dir}/third_party}"
openblas_dir="${OPENBLAS_DIR:-${third_party_dir}/OpenBLAS}"
openblas_repo="${OPENBLAS_REPO:-https://github.com/OpenMathLib/OpenBLAS.git}"
openblas_ref="${OPENBLAS_REF:-}"
jobs="${JOBS:-4}"
target="${OPENBLAS_TARGET:-WASM128_GENERIC}"

if ! command -v emcc >/dev/null 2>&1 && [ -d /opt/homebrew/bin ]; then
    export PATH="/opt/homebrew/bin:${PATH}"
fi

for tool in git make emcc emar emranlib; do
    if ! command -v "${tool}" >/dev/null 2>&1; then
        echo "Missing required tool: ${tool}" >&2
        exit 2
    fi
done

mkdir -p "${third_party_dir}"

if [ ! -d "${openblas_dir}/.git" ]; then
    git clone --depth 1 "${openblas_repo}" "${openblas_dir}"
    if [ -n "${openblas_ref}" ]; then
        git -C "${openblas_dir}" fetch --depth 1 origin "${openblas_ref}"
        git -C "${openblas_dir}" checkout --detach FETCH_HEAD
    fi
elif [ -n "${openblas_ref}" ]; then
    echo "OPENBLAS_REF is ignored because ${openblas_dir} already exists." >&2
fi

cd "${openblas_dir}"

if [ "${OPENBLAS_CLEAN:-0}" = "1" ]; then
    make clean
fi

make "-j${jobs}" libs \
    TARGET="${target}" \
    CC="${CC:-emcc}" \
    HOSTCC="${HOSTCC:-cc}" \
    AR="${AR:-emar}" \
    RANLIB="${RANLIB:-emranlib}" \
    NOFORTRAN=1 \
    NO_LAPACKE=1 \
    USE_THREAD=0 \
    NUM_THREADS=1 \
    DYNAMIC_ARCH=0

archive="$(find "${openblas_dir}" -maxdepth 1 -name 'libopenblas*.a' -print | sort | tail -n 1)"
if [ -z "${archive}" ]; then
    echo "OpenBLAS build completed, but no libopenblas archive was found." >&2
    exit 1
fi

echo "${archive}"
