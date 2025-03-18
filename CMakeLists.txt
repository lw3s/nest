cmake_minimum_required(VERSION 3.31)
project(dsa-lib)
set(CMAKE_CXX_STANDARD 23)

include(FetchContent)

FetchContent_Declare(
    gtest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(gtest)

include_directories(include)

file(GLOB src_names RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} CONFIGURE_DEPENDS testing/*)  # eliminate need to enforce naming conventions by having CMake fully automate
list(REMOVE_ITEM src_names testing/main.cpp)
set(exec_names ${src_names})
list(TRANSFORM exec_names REPLACE "^testing/" "test")
list(TRANSFORM exec_names REPLACE ".cpp$" "")

foreach(src exec IN ZIP_LISTS src_names exec_names)
    add_executable(${exec} testing/main.cpp ${src})
    target_link_libraries(${exec} PRIVATE gtest)
endforeach()

add_executable(testall testing/main.cpp ${src_names})
target_link_libraries(testall PRIVATE gtest)
