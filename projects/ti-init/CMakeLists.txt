cmake_minimum_required(VERSION 3.8.2)

project(ti-init C)
set(CMAKE_C_STANDARD 11)

# ti_shell.c buraya eklendi
add_executable(ti-init src/main.c src/bootstrap.c src/ti_log.c src/ti_shell.c)

target_link_libraries(ti-init sel4 muslc sel4runtime)

target_include_directories(ti-init PRIVATE
    "${CMAKE_BINARY_DIR}/libsel4/include"
    "${CMAKE_BINARY_DIR}/libsel4/autoconf"
    "${CMAKE_BINARY_DIR}/kernel/gen_config"
    "${CMAKE_BINARY_DIR}/libsel4/gen_config"
)

include(rootserver)
DeclareRootserver(ti-init)
