cmake_minimum_required(VERSION 3.14)
project(PrimeProject)



find_package(GTest REQUIRED)
add_library(task_lib src/n6func.cpp)

add_executable(test_lib tests/tests.cpp)

target_link_libraries(test_lib task_lib GTest::gtest_main)

add_test(NAME PrimeTest COMMAND tests)