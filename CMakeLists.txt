cmake_minimum_required(VERSION 3.0.0)
project(web_sockets_cpp_test VERSION 0.1.0 LANGUAGES C CXX)

enable_testing()

# include(ExternalProject)
# ExternalProject_Add(uWebSockets
#   GIT_REPOSITORY https://github.com/uNetworking/uWebSockets.git
#   EXCLUDE_FROM_ALL TRUE
#   BUILD_COMMAND $(MAKE) -j8
#   STEP_TARGETS build)

# set(uWebSockets_BINARY_DIR "${CMAKE_BINARY_DIR}/fmtlib-prefix/src/fmtlib-build")
# set(uWebSockets_SOURCE_DIR "${CMAKE_BINARY_DIR}/fmtlib-prefix/src/fmtlib/include")
# add_executable(fmttest fmttest.cpp)
# add_dependencies(fmttest fmtlib-build)
# target_link_libraries(fmttest ${fmtlib_BINARY_DIR}/libfmt.a)
# target_include_directories(fmttest PUBLIC ${fmtlib_SOURCE_DIR})
add_executable(web_sockets_cpp_test main.cpp)

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
