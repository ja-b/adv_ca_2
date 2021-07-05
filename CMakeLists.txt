cmake_minimum_required(VERSION 3.13)
project(advanced_ca_2 C CXX)

set(CMAKE_C_FLAGS_RELEASE "-O2 -funroll-loops")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

find_package(PAPI)

if (CMAKE_C_COMPILER_ID STREQUAL GNU)
    add_compile_options(-mavx -fopt-info-vec -fopt-info-loop)
elseif (CMAKE_C_COMPILER_ID STREQUAL Clang)
    add_compile_options(-Rpass=.*loop.*)
elseif (CMAKE_C_COMPILER_ID STREQUAL AppleClang)
    add_compile_options(-Rpass=.*loop.*)
elseif (CMAKE_C_COMPILER_ID STREQUAL Intel)
    add_compile_options(-xAVX -qopt-report-stdout)
endif ()

add_executable(hi_flop hi_flop.c)

#target_include_directories(hi_flop PUBLIC papi/)
target_include_directories(hi_flop PUBLIC ${PAPI_INCLUDE_DIRS})
target_link_libraries(hi_flop PUBLIC ${PAPI_LIBRARIES})
