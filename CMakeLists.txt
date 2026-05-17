cmake_minimum_required(VERSION 3.8.2)
project(ti-core C CXX ASM)

# Kullanıcı kütüphanelerinin nerede olduğunu söyleyelim (hata vermesin diye geri koyuyoruz)
set(CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/projects/seL4_libs/libsel4utils/cmake
    ${CMAKE_CURRENT_SOURCE_DIR}/projects/seL4_libs/libsel4/cmake
    ${CMAKE_MODULE_PATH}
)

# default-CMakeLists ZATEN "projects/" klasöründeki her şeyi ekliyor
# add_subdirectory filan yazmıyoruz
include(tools/seL4/cmake-tool/default-CMakeLists.txt)
