#include <gtest/gtest.h>
#include <AsyncFileStreamer.hpp>
#include <AsyncFileReader.hpp>

class AsyncFilestreamerTests: public ::testing::Test {
public:
	server::utils::AsyncFileStreamer fs{"../../www"};
};

TEST_F(AsyncFilestreamerTests, TestFileOpen)
{
	auto fileList = fs.getFiles();
	ASSERT_EQ(fileList[0], "/");
}
