#include <gtest/gtest.h>
#include <string>
#include <AsyncFileReader.hpp>

class AsyncFilereaderTests: public ::testing::Test {
public:
   std::string_view test_html = "<h1 style=\"background-color: red\">Helo, Chess World!</h1>\n";
   server::utils::AsyncFileReader fr{"../../tests/test_data/test.html"};
};

TEST_F(AsyncFilereaderTests, TestFileOpen)
{
	ASSERT_TRUE(fr.isStreamOpen());
}

TEST_F(AsyncFilereaderTests, TestChunk)
{
	fr.request(0, [this](auto chunk){
		ASSERT_EQ(chunk ,test_html);
	});
}

int main(int argc, char** argv){
	::testing::InitGoogleTest(&argc, argv);
	 return RUN_ALL_TESTS();
}
