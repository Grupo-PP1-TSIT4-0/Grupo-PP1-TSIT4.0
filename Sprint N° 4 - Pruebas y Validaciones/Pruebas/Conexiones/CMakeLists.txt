project(CppUTestExample)

cmake_minimum_required(VERSION 3.10)

include_directories(${CMAKE_SOURCE_DIR}/../cpputest/include)
link_directories(${CMAKE_SOURCE_DIR}/../cpputest/lib)

set(SOURCES
    test/hello_world_test.cpp
)

add_executable(runTests ${SOURCES})
target_link_libraries(runTests cpputest)