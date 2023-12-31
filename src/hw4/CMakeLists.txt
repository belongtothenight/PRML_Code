set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(LIBC_DIR "${CMAKE_SOURCE_DIR}/libc")
set(BINARY_DIR "${CMAKE_SOURCE_DIR}/bin")
set(PROJECT_NAME "hw4")

project(
    ${PROJECT_NAME} VERSION 1.0
)

add_executable(
    ${PROJECT_NAME} 
    main.c
    ${LIB_DIR}/config_read.c
    ${LIB_DIR}/iter.c
    ${LIB_DIR}/plot_iter.c
    ${LIB_DIR}/plot_cost.c
    ${LIBC_DIR}/signal_handler.c
    ${LIBC_DIR}/output_format.c
    ${LIBC_DIR}/common_macro.c
    ${LIBC_DIR}/distance.c
    ${LIBC_DIR}/intersection.c
    ${LIBC_DIR}/random.c
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
