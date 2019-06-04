cmake_minimum_required(VERSION 3.5)
project (DLlist VERSION 1.0.0 LANGUAGES CXX )

#=== Version control ===
set (CMAKE_CXX_STANDARD 11)

#=== Tags ===
set( GCC_COMPILE_FLAGS "-Wall" )

#=== Driver target ===
add_executable( run_tests "../src/driver_list.cpp" )