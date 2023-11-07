set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(LIBC_DIR "${CMAKE_SOURCE_DIR}/libc")
set(BINARY_DIR "${CMAKE_SOURCE_DIR}/bin")
set(PROJECT_NAME "hw3")

project(
    ${PROJECT_NAME} VERSION 1.0
)

add_executable(
    ${PROJECT_NAME} 
    main.c
    ${LIB_DIR}/data_proc.c
    ${LIB_DIR}/read_csv.c
    ${LIBC_DIR}/output_format.c
    ${LIBC_DIR}/common_macro.c
)

target_include_directories(
    ${PROJECT_NAME} PUBLIC 
    ${PROJECT_SHARED_LIB_DIR}
    ${PROJECT_PRIVATE_LIB_DIR}
)

install(
    TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${BINARY_DIR}
)
