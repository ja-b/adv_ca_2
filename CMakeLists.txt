cmake_minimum_required(VERSION 3.13)
project(advanced_ca_1 C CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

find_package(PAPI)

add_executable(hi_flop hi_flop.c)

target_include_directories(hi_flop PUBLIC papi/)
target_link_libraries(hi_flop PUBLIC PAPI_LIBRARIES)
