#!/usr/bin/env bash
set -euo pipefail

script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
wasm_dir="$(cd "${script_dir}/.." && pwd)"
openblas_dir="${OPENBLAS_DIR:-${wasm_dir}/third_party/OpenBLAS}"
src_dir="${OPENBLAS_LAPACK_SRC:-${openblas_dir}/lapack-netlib/SRC}"
install_src_dir="${OPENBLAS_LAPACK_INSTALL_SRC:-${openblas_dir}/lapack-netlib/INSTALL}"
build_dir="${JAGS_WASM_LAPACK_EXTRA_BUILD_DIR:-${wasm_dir}/build/lapack-extra}"
patched_src_dir="${build_dir}/src"
archive="${JAGS_WASM_LAPACK_EXTRA_LIB:-${wasm_dir}/build/libjags_lapack_extra.a}"
openblas_archive="${JAGS_WASM_OPENBLAS_LIB:-}"
roots="${JAGS_WASM_LAPACK_EXTRA_ROOTS:-dlange dsyev dgesv dsysv dposv dpotrf dpotri dtrtri}"

if ! command -v emcc >/dev/null 2>&1 && [ -d /opt/homebrew/bin ]; then
    export PATH="/opt/homebrew/bin:${PATH}"
fi

for tool in emcc emar emranlib perl; do
    if ! command -v "${tool}" >/dev/null 2>&1; then
        echo "Missing required tool: ${tool}" >&2
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

if [ -z "${openblas_archive}" ]; then
    openblas_archive="$(find "${openblas_dir}" -maxdepth 1 -name 'libopenblas*.a' -print 2>/dev/null | sort | tail -n 1)"
fi

if [ -z "${openblas_archive}" ] || [ ! -f "${openblas_archive}" ]; then
    echo "OpenBLAS archive not found. Run tools/build-openblas-wasm.sh first." >&2
    exit 2
fi

if [ ! -d "${src_dir}" ]; then
    echo "OpenBLAS lapack-netlib/SRC directory not found: ${src_dir}" >&2
    exit 2
fi

mkdir -p "${build_dir}" "${patched_src_dir}" "$(dirname "${archive}")"

contains() {
    local needle="$1"
    shift
    local item
    for item in "$@"; do
        if [ "${item}" = "${needle}" ]; then
            return 0
        fi
    done
    return 1
}

is_allowed_external() {
    case "$1" in
        __stack_pointer|memcpy|memmove|memset|malloc|free|abort)
            return 0
            ;;
        strcmp|strncmp|strncpy|strlen)
            return 0
            ;;
        sqrt|sqrtf|fabs|fabsf|fmax|fmaxf|fmin|fminf|log|logf|exp|expf|pow|powf)
            return 0
            ;;
    esac
    return 1
}

source_for_routine() {
    local routine="$1"
    if [ "${routine}" = "xerbla" ]; then
        printf '%s\n' "${xerbla_src}"
    elif [ -f "${src_dir}/${routine}.c" ]; then
        printf '%s\n' "${src_dir}/${routine}.c"
    elif [ -f "${install_src_dir}/${routine}.c" ]; then
        printf '%s\n' "${install_src_dir}/${routine}.c"
    fi
}

compile_routine() {
    local routine="$1"
    local src
    local patched_src
    local obj="${build_dir}/${routine}.o"

    if contains "${routine}" "${compiled[@]}"; then
        return 0
    fi
    src="$(source_for_routine "${routine}")"
    if [ -z "${src}" ]; then
        echo "No C LAPACK source for routine ${routine}" >&2
        return 1
    fi
    patched_src="${patched_src_dir}/${routine}.c"
    if grep -q '/\* Subroutine \*/ int' "${src}"; then
        convert_returns=1
    else
        convert_returns=0
    fi
    SUBROUTINE_NAMES="${subroutine_names_file}" \
    CONVERT_RETURNS="${convert_returns}" \
        perl -0pe '
            BEGIN {
                open(my $fh, "<", $ENV{"SUBROUTINE_NAMES"}) or die $!;
                local $/ = "\n";
                while (my $name = <$fh>) {
                    chomp($name);
                    $is_subroutine{$name} = 1;
                }
            }
            s@/\* Subroutine \*/ int@/* Subroutine */ void@g;
            s@extern /\* Subroutine \*/ int@extern /* Subroutine */ void@g;
            s@extern int\s+([A-Za-z][A-Za-z0-9_]*_)\s*\(@$is_subroutine{$1} ? "extern void $1(" : $&@ge;
            if ($ENV{"CONVERT_RETURNS"} eq "1") {
                s@return 0;@return;@g;
            }
        ' "${src}" > "${patched_src}"

    emcc -c "${patched_src}" \
        -O2 \
        -std=c99 \
        -w \
        -DC_LAPACK \
        -DNO_LAPACKE \
        -DF_INTERFACE_GFORT \
        -o "${obj}"

    compiled+=("${routine}")
    objects+=("${obj}")
}

defined_file="${build_dir}/defined-symbols.txt"
undefined_file="${build_dir}/undefined-symbols.txt"
subroutine_names_file="${build_dir}/subroutine-names.txt"
xerbla_src="${build_dir}/xerbla_override.c"
queue=()
compiled=()
objects=()

{
    find "${src_dir}" "${install_src_dir}" -maxdepth 1 -name '*.c' -print 2>/dev/null |
        while IFS= read -r candidate; do
            routine="$(basename "${candidate}" .c)"
            if grep -Eq "/\\* Subroutine \\*/ (int|void) ${routine}_" "${candidate}"; then
                printf '%s_\n' "${routine}"
            fi
        done
    printf 'xerbla_\n'
} | sort -u > "${subroutine_names_file}"

cat > "${xerbla_src}" <<'EOF'
#include <stdio.h>

void xerbla_(char *srname, int *info, int srname_len)
{
    (void)srname;
    (void)info;
    (void)srname_len;
}
EOF

for root in ${roots}; do
    queue+=("${root}")
done

while [ "${#queue[@]}" -gt 0 ]; do
    routine="${queue[0]}"
    queue=("${queue[@]:1}")
    compile_routine "${routine}"

    "${nm_tool}" --defined-only "${openblas_archive}" "${objects[@]}" > "${defined_file}" 2>/dev/null
    "${nm_tool}" --undefined-only "${objects[@]}" 2>/dev/null | awk '{ print $NF }' | sort -u > "${undefined_file}"

    while IFS= read -r symbol; do
        if [ -z "${symbol}" ]; then
            continue
        fi
        if is_allowed_external "${symbol}"; then
            continue
        fi
        if [[ "${symbol}" =~ ^[A-Za-z][A-Za-z0-9_]*_$ ]]; then
            dep="${symbol%_}"
            if [ -n "$(source_for_routine "${dep}")" ] &&
               ! contains "${dep}" "${compiled[@]}" &&
               ! contains "${dep}" "${queue[@]}"; then
                queue+=("${dep}")
                continue
            fi
        fi
        if grep -Eq "(^|[[:space:]])${symbol}([[:space:]]|$)" "${defined_file}"; then
            continue
        fi
    done < "${undefined_file}"
done

"${nm_tool}" --defined-only "${openblas_archive}" "${objects[@]}" > "${defined_file}" 2>/dev/null
"${nm_tool}" --undefined-only "${objects[@]}" 2>/dev/null | awk '{ print $NF }' | sort -u > "${undefined_file}"

unresolved=()
while IFS= read -r symbol; do
    if [ -z "${symbol}" ]; then
        continue
    fi
    if grep -Eq "(^|[[:space:]])${symbol}([[:space:]]|$)" "${defined_file}"; then
        continue
    fi
    if is_allowed_external "${symbol}"; then
        continue
    fi
    unresolved+=("${symbol}")
done < "${undefined_file}"

if [ "${#unresolved[@]}" -gt 0 ]; then
    printf 'Unresolved symbols after LAPACK extra build: %s\n' "${unresolved[*]}" >&2
    exit 1
fi

rm -f "${archive}"
emar rcs "${archive}" "${objects[@]}"
emranlib "${archive}"

echo "${archive}"
echo "Compiled LAPACK routines: ${compiled[*]}"
