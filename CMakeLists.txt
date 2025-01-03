cmake_minimum_required(VERSION 3.31)
project(dsa-lib)

find_package(GTest REQUIRED)
include_directories(include)

set(file_names
    list
    graph)

set(src_names ${file_names})
list(TRANSFORM src_names PREPEND testing/)
list(TRANSFORM src_names APPEND .cpp)

set(exec_names ${file_names})
list(TRANSFORM exec_names PREPEND test)

foreach(src exec IN ZIP_LISTS src_names exec_names)
    add_executable(${exec} testing/main.cpp ${src})
    target_link_libraries(${exec} PRIVATE gtest::gtest)
endforeach()

add_executable(testall testing/main.cpp ${src_names})
target_link_libraries(testall PRIVATE gtest::gtest)