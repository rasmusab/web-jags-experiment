#!/usr/bin/env bash
set -euo pipefail

script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
wasm_dir="$(cd "${script_dir}/.." && pwd)"

if [ $# -gt 0 ]; then
    archives=("$@")
else
    archive="$(find "${wasm_dir}/third_party" -name 'libopenblas*.a' -print 2>/dev/null | sort | tail -n 1)"
    archives=("${archive}")
fi

if [ "${#archives[@]}" -eq 0 ] || [ -z "${archives[0]:-}" ]; then
    echo "Usage: $0 /path/to/libopenblas.a [/path/to/libjags_lapack_extra.a]" >&2
    echo "No OpenBLAS archive found under ${wasm_dir}/third_party." >&2
    exit 2
fi
for archive in "${archives[@]}"; do
    if [ ! -f "${archive}" ]; then
        echo "Archive not found: ${archive}" >&2
        exit 2
    fi
done

if [ -x /opt/homebrew/opt/llvm/bin/llvm-nm ]; then
    nm_tool="/opt/homebrew/opt/llvm/bin/llvm-nm"
elif command -v llvm-nm >/dev/null 2>&1; then
    nm_tool="llvm-nm"
elif command -v emnm >/dev/null 2>&1; then
    nm_tool="emnm"
else
    echo "Missing llvm-nm or emnm." >&2
    exit 2
fi

required=(
    ddot_
    dcopy_
    dscal_
    daxpy_
    dgemv_
    dgemm_
    dsyr_
    dsymm_
    dsyrk_
    dlange_
    dtrmm_
    dsyev_
    dgesv_
    dsysv_
    dposv_
    dpotrf_
    dpotri_
    dtrtri_
)

symbols="$(mktemp)"
trap 'rm -f "${symbols}"' EXIT

"${nm_tool}" --defined-only "${archives[@]}" > "${symbols}"

present=()
missing=()
for symbol in "${required[@]}"; do
    if grep -Eq "(^|[[:space:]])${symbol}([[:space:]]|$)" "${symbols}"; then
        present+=("${symbol}")
    else
        missing+=("${symbol}")
    fi
done

printf 'Archive: %s\n' "${archives[@]}"
echo "Defined required symbols: ${#present[@]}/${#required[@]}"
if [ "${#present[@]}" -gt 0 ]; then
    printf 'Present: %s\n' "${present[*]}"
fi
if [ "${#missing[@]}" -gt 0 ]; then
    printf 'Missing: %s\n' "${missing[*]}"
    exit 1
fi
