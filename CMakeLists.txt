cmake_minimum_required(VERSION 2.6)
project(tests)

set(CMAKE_C_STANDARD 99)
#set(CMAKE_CXX_STANDARD 11)
#set(SMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS "-g -O0 -Wall -Werror -Wpedantic -fprofile-arcs -ftest-coverage")
# -ftest-coverage - Create data files needed by gcov
# -fprofile-arcs - Insert arc-based program profiling code 

set(CMAKE_EXE_LINKER_FLAGS "-lgcov --coverage")

set(LIB_SOURCE_FILE functionality.h functionality.c)

add_library(_all_headers STATIC ${LIB_SOURCE_FILE})

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(tests test.cpp)
add_executable(main main.c)

target_link_libraries(tests ${GTEST_LIBRARIES} gtest_main pthread)
target_link_libraries(tests _all_headers)
target_link_libraries(main _all_headers)
target_link_libraries(tests -fprofile-arcs)

enable_testing()

add_test(NAME tests COMMAND tests)