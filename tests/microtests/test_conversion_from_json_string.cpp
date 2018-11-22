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

TEST_F(TestConversionFromJsonString, convertDocumentWithSingleBoolFieldAndNoSpaces)
{
    auto json_string = "{\"b\":true}";

    auto expected = Json::Builder()
        .append("b", true)
        .getTree();

    auto actual = Json::fromString(json_string);

    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionFromJsonString, convertDocumentWithSingleFloatFieldAndNoSpaces)
{
    auto json_string = "{\"f\":12.5}";

    auto expected = Json::Builder()
        .append("f", 12.5f)
        .getTree();

    auto actual = Json::fromString(json_string);

    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionFromJsonString, convertDocumentWithSingleStringFieldWithSpaces)
{
    auto json_string = " { \"s\" :  \"hello world\" } ";

    auto expected = Json::Builder()
        .append("s", "hello world")
        .getTree();

    auto actual = Json::fromString(json_string);

    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionFromJsonString, convertDocumentWithSingleArrayWithSingleElement)
{
    auto json_string = "{\"array\": [10]}";

    auto expected = Json::Builder()
        .openSubtree("array")
            .pushBack(10)
        .closeSubtree()
        .getTree();

    auto actual = Json::fromString(json_string);

    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionFromJsonString, convertDocumentWithSingleArrayWithMultipleElements)
{
    auto json_string = "{\"array\": [10, true, \"hello\", \"world\"]}";

    auto expected = Json::Builder()
        .openSubtree("array")
            .pushBack(10)
            .pushBack(true)
            .pushBack("hello")
            .pushBack("world")
        .closeSubtree()
        .getTree();

    auto actual = Json::fromString(json_string);

    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionFromJsonString, convertDocumentWithMultipleValuesOfDifferentTypes)
{
    auto json_string = R"({
        "s": "hello world",
        "i": 10,
        "negative": -10,
        "b": true,
        "f": 12.5
    })";

    auto expected = Json::Builder()
        .append("s", "hello world")
        .append("i", 10)
        .append("negative", -10)
        .append("b", true)
        .append("f", 12.5f)
        .getTree();

    auto actual = Json::fromString(json_string);

    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionFromJsonString, convertDocumentWithMultipleArraysAndValues)
{
    auto json_string = R"({
        "s": "hello world",
        "i": 10,
        "a1": [true, false, 10, "hello"],
        "negative": -10,
        "a2": [false, -210, "world"]
    })";

    auto expected = Json::Builder()
        .append("s", "hello world")
        .append("i", 10)
        .openSubtree("a1")
            .pushBack(true)
            .pushBack(false)
            .pushBack(10)
            .pushBack("hello")
        .closeSubtree()
        .append("negative", -10)
        .openSubtree("a2")
            .pushBack(false)
            .pushBack(-210)
            .pushBack("world")
        .closeSubtree()
        .getTree();

    auto actual = Json::fromString(json_string);

    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionFromJsonString, convertDocumentWithSingleSubdocument)
{
    auto json_string = R"({
        "d": {
            "s": "hello world",
            "i": 10,
            "negative": -10
        }
    })";

    auto expected = Json::Builder()
        .openSubtree("d")
            .append("s", "hello world")
            .append("i", 10)
            .append("negative", -10)
        .closeSubtree()
        .getTree();

    auto actual = Json::fromString(json_string);

    EXPECT_EQ(expected, actual);
}
