#include <gmock/gmock.h>

#include <json/conversion.hpp>

#include <json/builder.hpp>

using namespace CodedProject::Json;

class TestConversionToJsonString : public ::testing::Test
{
};

TEST_F(TestConversionToJsonString, nullValueTree)
{
    auto t = Tree(Value());
    auto expected = "null";
    auto actual = toString(t);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionToJsonString, integerValueTree)
{
    auto t = Tree(1234);
    auto expected = "1234";
    auto actual = toString(t);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionToJsonString, stringValueTree)
{
    auto t = Tree("hello world");
    auto expected = "\"hello world\"";
    auto actual = toString(t);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionToJsonString, boolTrueValueTree)
{
    auto t = Tree(true);
    auto expected = "true";
    auto actual = toString(t);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionToJsonString, boolFalseValueTree)
{
    auto t = Tree(false);
    auto expected = "false";
    auto actual = toString(t);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionToJsonString, arrayWithSingleValue)
{
    auto t = Builder()
        .pushBack(234)
        .getTree();
    auto expected = "[234]";
    auto actual = toString(t);
    EXPECT_EQ(expected, actual);
}
