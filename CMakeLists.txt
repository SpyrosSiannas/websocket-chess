cmake_minimum_required(VERSION 3.0.0)
project(web_sockets_cpp_test VERSION 0.1.0 LANGUAGES C CXX)

enable_testing()
add_executable(web_sockets_cpp_test main.cpp)

set(SUBMODULE_DIR ${CMAKE_SOURCE_DIR}/third-party)

add_subdirectory(${SUBMODULE_DIR}/websocketpp)
include_directories(${SUBMODULE_DIR}/websocketpp)

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
