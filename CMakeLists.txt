cmake_minimum_required(VERSION 3.31)
project(dsa-lib)

include(FetchContent)
FetchContent_Declare(
    gtest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(gtest)
include_directories(include)

set(file_names
    list
    misc
    graph
    sort
    search)

set(src_names ${file_names})
list(TRANSFORM src_names PREPEND testing/)
list(TRANSFORM src_names APPEND .cpp)

set(exec_names ${file_names})
list(TRANSFORM exec_names PREPEND test)

foreach(src exec IN ZIP_LISTS src_names exec_names)
    add_executable(${exec} testing/main.cpp ${src})
    target_link_libraries(${exec} PRIVATE gtest)
endforeach()

add_executable(testall testing/main.cpp ${src_names})
target_link_libraries(testall PRIVATE gtest)