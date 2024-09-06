cmake_minimum_required(VERSION 3.0.0)
project(ws_server VERSION 0.1.0 LANGUAGES C CXX)

enable_testing()
add_subdirectory(tests)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)

file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/server/*.cpp")

add_executable(ws_server ${SOURCES} main.cpp)
set_property(TARGET ws_server PROPERTY CXX_STANDARD 20)

set(SUBMODULE_DIR ${CMAKE_SOURCE_DIR}/third-party)
set(UWEBSOCKETS_DIR ${SUBMODULE_DIR}/uWebSockets)

include(ExternalProject)
ExternalProject_Add(
    uSockets
    SOURCE_DIR ${UWEBSOCKETS_DIR}
    BUILD_COMMAND make -j8
    CONFIGURE_COMMAND ""
    INSTALL_COMMAND ""
    BUILD_IN_SOURCE 1
)
add_dependencies(ws_server uSockets)

set (WEBSOCK_INCL ${UWEBSOCKETS_DIR}/src)
set (SERVER_INCL ${CMAKE_SOURCE_DIR}/server)
set (WEBSOCK_LIB ${UWEBSOCKETS_DIR}/uSockets/uSockets.a)
set (USOCK_INCL ${UWEBSOCKETS_DIR}/uSockets/src)

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Werror-Wpedantic)
endif()

target_include_directories(ws_server PRIVATE  ${WEBSOCK_INCL})
target_include_directories(ws_server PRIVATE  ${SERVER_INCL})
target_include_directories(ws_server PRIVATE  ${USOCK_INCL})
target_include_directories(ws_server PRIVATE  ${CMAKE_SOURCE_DIR})

target_link_libraries(ws_server z)
target_link_libraries(ws_server ${WEBSOCK_LIB})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
