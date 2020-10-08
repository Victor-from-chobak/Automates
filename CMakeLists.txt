cmake_minimum_required(VERSION 2.8.12)

set(CMAKE_CXX_STANDART 17)
add_compile_options(-std=c++1z)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
add_executable(runTests test.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
