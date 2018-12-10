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

TEST_F(TestConversionToJsonString, arrayWithMultipleNestedDocumentsAndArraysWithFormatting)
{
    auto t = Builder()
        .pushBack(123)
        .openSubtree()
            .append("a", true)
            .openSubtree("b")
                .pushBack(1)
                .openSubtree()
                    .openSubtree("1")
                        .pushBack(5)
                    .closeSubtree()
                    .openSubtree("2")
                        .append("a", true)
                    .closeSubtree()
                .closeSubtree()
            .closeSubtree()
        .closeSubtree()
        .openSubtree()
            .pushBack(true)
            .pushBack(6)
            .openSubtree()
                .pushBack(987)
                .pushBack(true)
            .closeSubtree()
        .closeSubtree()
    .getTree();

    auto expected =
        "[\n"
        "    123,\n"
        "    {\n"
        "        \"a\": true,\n"
        "        \"b\": [\n"
        "            1,\n"
        "            {\n"
        "                \"1\": [\n"
        "                    5\n"
        "                ],\n"
        "                \"2\": {\n"
        "                    \"a\": true\n"
        "                }\n"
        "            }\n"
        "        ]\n"
        "    },\n"
        "    [\n"
        "        true,\n"
        "        6,\n"
        "        [\n"
        "            987,\n"
        "            true\n"
        "        ]\n"
        "    ]\n"
        "]";
    auto actual = toString(t, true);
    EXPECT_EQ(expected, actual);
}
