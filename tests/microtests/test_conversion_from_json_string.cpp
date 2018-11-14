#include <gmock/gmock.h>

#include <json/conversion.hpp>

#include <json/builder.hpp>

using namespace CodedProject;

class TestConversionFromJsonString : public ::testing::Test
{
};

TEST_F(TestConversionFromJsonString, convertDocumentWithSingleIntegerFieldAndNoSpaces)
{
    auto json_string = "{\"i\":1}";

    auto expected = Json::Builder()
        .append("i", 1)
        .getTree();

    auto actual = Json::fromString(json_string);

    EXPECT_EQ(expected, actual);
}

// Waiting to implement this until there are some conversion helpers in place JDC 20181114
TEST_F(TestConversionFromJsonString, DISABLED_convertDocumentWithSingleBoolFieldAndNoSpaces)
{
    auto json_string = "{\"b\":true}";

    auto expected = Json::Builder()
        .append("b", true)
        .getTree();

    auto actual = Json::fromString(json_string);

    EXPECT_EQ(expected, actual);
}
