cmake_minimum_required(VERSION 3.0.0)
project(web_sockets_cpp_test VERSION 0.1.0 LANGUAGES C CXX)

enable_testing()

add_executable(web_sockets_cpp_test main.cpp)

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
