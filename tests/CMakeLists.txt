include(FetchContent)

set (WEBSOCK_DIR ${CMAKE_SOURCE_DIR}/third-party/uWebSockets)
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.cpp)
add_executable(websocket_tests ${TEST_SOURCES} )
set_property(TARGET websocket_tests PROPERTY CXX_STANDARD 20)

include_directories(websocket_tests PRIVATE ${CMAKE_SOURCE_DIR}/server/utils)
include_directories(websocket_tests PUBLIC ${WEBSOCK_DIR}/src)
include_directories(websocket_tests PRIVATE ${WEBSOCK_DIR}/uSockets/src)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.13.0
)
FetchContent_MakeAvailable(googletest)

add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)
target_link_libraries(websocket_tests
 PRIVATE
 GTest::GTest
 ${WEBSOCK_DIR}/uSockets/uSockets.a)

add_test(websocket_tests websocket_tests)
