#include <gmock/gmock.h>

#include <json/conversion_helpers/tokenize.hpp>

using namespace CodedProject::Json::ConversionHelpers;

class TestConversionHelpersTokenize : public ::testing::Test
{
};

TEST_F(TestConversionHelpersTokenize, givesCorrectTokenForString)
{
    auto json_text = "\"hello\"";

    auto expected_tokens = std::list<Token>{
        {TokenType, "\"hello\""}
    };

    auto actual_tokens = tokenize(json_text);
    EXPECT_EQ(expected_tokens, actual_tokens);
}
