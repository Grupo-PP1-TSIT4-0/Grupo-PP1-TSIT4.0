CMakeLists.txt:
cmake_minimum_required(VERSION 3.10)
project(Sensores_y_Actuadores)

set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_SOURCE_DIR}/path/to/cpputest/include)
link_directories(${CMAKE_SOURCE_DIR}/path/to/cpputest/lib)

add_executable(hello_world_test test/hello_world_test.cpp)
target_link_libraries(hello_world_test cpputest)

test/hello_world_test.cpp:
#include <CppUTest/CommandLineTestRunner.h>

TEST_GROUP(HelloWorld)
{
};

TEST(HelloWorld, Test1)
{
    CHECK_EQUAL(1, 1);
}

int main(int argc, char** argv)
{
    return CommandLineTestRunner::RunAllTests(argc, argv);
}