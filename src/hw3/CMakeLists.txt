cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_COMPILER "C:/MinGW/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/MinGW/bin/g++.exe")
set(BASE_DIR "E:/GitHub/PRML_Code/src")
set(PROJECT_BASE_DIR "${BASE_DIR}/hw3")
set(PROJECT_SHARED_LIB_DIR "${BASE_DIR}/libc")
set(PROJECT_PRIVATE_LIB_DIR "${PROJECT_BASE_DIR}/lib")
set(PROJECT_NAME "main")

project(
    ${PROJECT_NAME} VERSION 1.0
)
add_executable(
    ${PROJECT_NAME} 
    ${PROJECT_BASE_DIR}/main.c
    ${PROJECT_PRIVATE_LIB_DIR}/data_proc.c
    ${PROJECT_SHARED_LIB_DIR}/output_format.c
)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SHARED_LIB_DIR} ${PROJECT_PRIVATE_LIB_DIR})
