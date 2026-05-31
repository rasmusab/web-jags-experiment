cmake_minimum_required(VERSION 3.20)

project(jags_wasm LANGUAGES C CXX)

set(JAGS_ROOT "${CMAKE_CURRENT_LIST_DIR}/../JAGS-4.3.2" CACHE PATH
    "Path to the JAGS source tree")
get_filename_component(JAGS_ROOT "${JAGS_ROOT}" ABSOLUTE)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(JAGS_WASM_NUMERIC_BACKEND "fallback" CACHE STRING
    "Numerical backend to use: fallback or openblas")
set_property(CACHE JAGS_WASM_NUMERIC_BACKEND PROPERTY STRINGS fallback openblas)
set(JAGS_WASM_OPENBLAS_LIB "" CACHE FILEPATH
    "Path to an Emscripten-built OpenBLAS static archive")
set(JAGS_WASM_LAPACK_EXTRA_LIB "" CACHE FILEPATH
    "Path to the supplemental C-LAPACK archive for OpenBLAS WASM builds")

function(append_sources output)
    foreach(dir IN LISTS ARGN)
	file(GLOB dir_sources CONFIGURE_DEPENDS
	    "${dir}/*.c"
	    "${dir}/*.cc")
	list(APPEND sources ${dir_sources})
    endforeach()
    set(${output} ${${output}} ${sources} PARENT_SCOPE)
endfunction()

set(JAGS_WASM_NUMERIC_SOURCES)
if(JAGS_WASM_NUMERIC_BACKEND STREQUAL "fallback")
    list(APPEND JAGS_WASM_NUMERIC_SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/src/lapack_fallback.cc")
elseif(JAGS_WASM_NUMERIC_BACKEND STREQUAL "openblas")
    if(NOT JAGS_WASM_OPENBLAS_LIB OR NOT EXISTS "${JAGS_WASM_OPENBLAS_LIB}")
        message(FATAL_ERROR
            "JAGS_WASM_NUMERIC_BACKEND=openblas requires JAGS_WASM_OPENBLAS_LIB")
    endif()
    if(NOT JAGS_WASM_LAPACK_EXTRA_LIB OR NOT EXISTS "${JAGS_WASM_LAPACK_EXTRA_LIB}")
        message(FATAL_ERROR
            "JAGS_WASM_NUMERIC_BACKEND=openblas requires JAGS_WASM_LAPACK_EXTRA_LIB")
    endif()
else()
    message(FATAL_ERROR
        "Unknown JAGS_WASM_NUMERIC_BACKEND: ${JAGS_WASM_NUMERIC_BACKEND}")
endif()

set(JAGS_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/src/jags_wasm.cc"
    ${JAGS_WASM_NUMERIC_SOURCES}
    "${JAGS_ROOT}/src/lib/Console.cc"
    "${JAGS_ROOT}/src/lib/version.cc")

append_sources(JAGS_SOURCES
    "${JAGS_ROOT}/src/lib/util"
    "${JAGS_ROOT}/src/lib/sarray"
    "${JAGS_ROOT}/src/lib/distribution"
    "${JAGS_ROOT}/src/lib/function"
    "${JAGS_ROOT}/src/lib/sampler"
    "${JAGS_ROOT}/src/lib/graph"
    "${JAGS_ROOT}/src/lib/model"
    "${JAGS_ROOT}/src/lib/compiler"
    "${JAGS_ROOT}/src/lib/rng"
    "${JAGS_ROOT}/src/lib/module"
    "${JAGS_ROOT}/src/jrmath"
    "${JAGS_ROOT}/src/modules/base"
    "${JAGS_ROOT}/src/modules/base/functions"
    "${JAGS_ROOT}/src/modules/base/monitors"
    "${JAGS_ROOT}/src/modules/base/rngs"
    "${JAGS_ROOT}/src/modules/base/samplers"
    "${JAGS_ROOT}/src/modules/bugs"
    "${JAGS_ROOT}/src/modules/bugs/distributions"
    "${JAGS_ROOT}/src/modules/bugs/functions"
    "${JAGS_ROOT}/src/modules/bugs/matrix"
    "${JAGS_ROOT}/src/modules/bugs/samplers")

list(FILTER JAGS_SOURCES EXCLUDE REGEX "/test[^/]*\\.(c|cc)$")
list(REMOVE_DUPLICATES JAGS_SOURCES)

add_executable(jags_wasm ${JAGS_SOURCES})

target_include_directories(jags_wasm PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}"
    "${CMAKE_CURRENT_LIST_DIR}/src"
    "${JAGS_ROOT}/src/include"
    "${JAGS_ROOT}/src/lib"
    "${JAGS_ROOT}/src/modules/base"
    "${JAGS_ROOT}/src/modules/bugs"
    "${JAGS_ROOT}/src/modules/bugs/distributions"
    "${JAGS_ROOT}/src/modules/bugs/functions"
    "${JAGS_ROOT}/src/modules/bugs/matrix"
    "${JAGS_ROOT}/src/modules/bugs/samplers"
    "${JAGS_ROOT}/src/jrmath")

target_compile_definitions(jags_wasm PRIVATE
    HAVE_CONFIG_H
    MATHLIB_STANDALONE)

target_compile_options(jags_wasm PRIVATE
    $<$<COMPILE_LANGUAGE:C>:-std=c99>
    $<$<COMPILE_LANGUAGE:CXX>:-fexceptions>)

if(JAGS_WASM_NUMERIC_BACKEND STREQUAL "openblas")
    target_compile_options(jags_wasm PRIVATE -msimd128)
    target_link_options(jags_wasm PRIVATE -msimd128)
    target_link_libraries(jags_wasm PRIVATE
        "${JAGS_WASM_LAPACK_EXTRA_LIB}"
        "${JAGS_WASM_OPENBLAS_LIB}")
endif()

target_link_options(jags_wasm PRIVATE
    -fexceptions
    "SHELL:-sDISABLE_EXCEPTION_CATCHING=0"
    "SHELL:-sALLOW_MEMORY_GROWTH=1"
    "SHELL:-sMODULARIZE=1"
    "SHELL:-sEXPORT_NAME=createJagsModule"
    "SHELL:-sENVIRONMENT=web,worker,node"
    "SHELL:-sNO_EXIT_RUNTIME=1"
    "SHELL:-sEXPORTED_RUNTIME_METHODS=['ccall','cwrap','UTF8ToString','HEAPU32','HEAPF64']"
    "SHELL:-sEXPORTED_FUNCTIONS=['_malloc','_free','_jags_create','_jags_destroy','_jags_last_error','_jags_set_seed','_jags_check_model','_jags_clear_data','_jags_set_data','_jags_set_parameter','_jags_compile','_jags_initialize','_jags_adapt_off','_jags_update','_jags_set_monitor','_jags_dump_monitors','_jags_parameter_names','_jags_iteration']")

set_target_properties(jags_wasm PROPERTIES
    OUTPUT_NAME "jags")
