#include <gmock/gmock.h>

#include <json/conversion_helpers/to_json_text.hpp>

#include <json/builder.hpp>

using namespace CodedProject::Json;
using namespace CodedProject::Json::ConversionHelpers;

class TestConversionHelpersToJsonTextTreeConversion : public ::testing::Test
{
};

TEST_F(TestConversionHelpersToJsonTextTreeConversion, nullValueTree)
{
    auto t = Tree(Value());
    auto expected = "null";
    auto actual = toJsonText(t);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionHelpersToJsonTextTreeConversion, integerValueTree)
{
    auto t = Tree(1234);
    auto expected = "1234";
    auto actual = toJsonText(t);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionHelpersToJsonTextTreeConversion, stringValueTree)
{
    auto t = Tree("hello world");
    auto expected = "\"hello world\"";
    auto actual = toJsonText(t);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionHelpersToJsonTextTreeConversion, boolTrueValueTree)
{
    auto t = Tree(true);
    auto expected = "true";
    auto actual = toJsonText(t);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionHelpersToJsonTextTreeConversion, boolFalseValueTree)
{
    auto t = Tree(false);
    auto expected = "false";
    auto actual = toJsonText(t);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionHelpersToJsonTextTreeConversion, arrayWithSingleValue)
{
    auto t = Builder()
        .pushBack(234)
        .getTree();
    auto expected = "[234]";
    auto actual = toJsonText(t);
    EXPECT_EQ(expected, actual);
}

