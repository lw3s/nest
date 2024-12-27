cmake_minimum_required(VERSION 3.31)
project(dsa-lib)

find_package(GTest REQUIRED)

set(SOURCES
    main.cpp)
list(TRANSFORM SOURCES PREPEND tests/)

add_executable(test ${SOURCES})
target_link_libraries(test PRIVATE gtest::gtest)
target_include_directories(test PRIVATE include)