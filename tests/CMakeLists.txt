include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.13.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(async_filereader_test async_filereader_test.cpp)
target_include_directories(async_filereader_test PRIVATE ${CMAKE_SOURCE_DIR}/server/utils)

target_link_libraries(async_filereader_test
 PRIVATE
 GTest::GTest)

add_test(async_filereader_test async_filereader_test)
