cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(GCC_COVERAGE_COMPILE_FLAGS "-Wno-implicit-function-declaration -O3 -Wno-write-strings")
set(PROJECT_NAME "PRML_Code")

project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES C)

add_subdirectory(
    ${CMAKE_SOURCE_DIR}/hw3
    # ${BASE_DIR}/hw4
)
