cmake_minimum_required(VERSION 3.20)

project(jags_wasm LANGUAGES C CXX)

set(JAGS_ROOT "${CMAKE_CURRENT_LIST_DIR}/..")

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

function(append_sources output)
    foreach(dir IN LISTS ARGN)
	file(GLOB dir_sources CONFIGURE_DEPENDS
	    "${dir}/*.c"
	    "${dir}/*.cc")
	list(APPEND sources ${dir_sources})
    endforeach()
    set(${output} ${${output}} ${sources} PARENT_SCOPE)
endfunction()

set(JAGS_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/jags_wasm.cc"
    "${CMAKE_CURRENT_LIST_DIR}/lapack_fallback.cc"
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
