cmake_minimum_required(VERSION 3.0.0)
project(web_sockets_cpp_test VERSION 0.1.0 LANGUAGES C CXX)

enable_testing()
add_executable(web_sockets_cpp_test main.cpp)

set(SUBMODULE_DIR ${CMAKE_SOURCE_DIR}/third-party)
set(UWEBSOCKETS_DIR ${SUBMODULE_DIR}/uWebSockets)

include(ExternalProject)
message(${UWEBSOCKETS_DIR})
ExternalProject_Add(
    uWebSockets
    SOURCE_DIR ${UWEBSOCKETS_DIR}
    BUILD_COMMAND make -j8
    CONFIGURE_COMMAND ""
    INSTALL_COMMAND ""
    BUILD_IN_SOURCE 1
)

set (WEBSOCK_INCL ${UWEBSOCKETS_DIR}/src)
set (WEBSOCK_LIB ${UWEBSOCKETS_DIR}/uSockets/uSockets.a)
set (USOCK_INCL ${UWEBSOCKETS_DIR}/uSockets/src)

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Werror-Wpedantic)
endif()

target_include_directories(web_sockets_cpp_test PRIVATE  ${WEBSOCK_INCL})
target_include_directories(web_sockets_cpp_test PRIVATE  ${USOCK_INCL})
target_link_libraries(web_sockets_cpp_test ${WEBSOCK_LIB})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
