cmake_minimum_required(VERSION 3.7.1)
project(ti-init C)
set(CMAKE_C_STANDARD 11)

add_executable(ti-init 
    src/main.c
    src/ti_cap.c
    src/ti_shell.c
    src/ti_log.c
)

target_link_libraries(ti-init
    sel4
    muslc
    sel4utils
    sel4runtime
)

DeclareRootserver(ti-init)
