cmake_minimum_required(VERSION 3.20)

project(FoodFlow VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(foodflow
    src/main.cpp
)

target_include_directories(foodflow PRIVATE src)

add_executable(test_foodflow
    tests/test_foodflow.cpp
)

target_include_directories(test_foodflow PRIVATE src)

enable_testing()
add_test(NAME FoodFlowTests COMMAND test_foodflow)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(foodflow PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(test_foodflow PRIVATE -Wall -Wextra -Wpedantic)
endif()
