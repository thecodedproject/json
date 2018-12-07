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

TEST_F(TestConversionHelpersToJsonTextTreeConversion, uninitalisedTree)
{
    auto t = Tree(Tree::Type::Uninitialised);
    auto expected = "null";
    auto actual = toJsonText(t);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionHelpersToJsonTextTreeConversion, emptyArray)
{
    auto t = Tree(Tree::Type::Array);
    auto expected = "[]";
    auto actual = toJsonText(t);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionHelpersToJsonTextTreeConversion, arrayWithMultipleValues)
{
    auto t = Builder()
        .pushBack(234)
        .pushBack(true)
        .pushBack("hello")
        .pushBack(false)
        .getTree();
    auto expected = "[234,true,\"hello\",false]";
    auto actual = toJsonText(t);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionHelpersToJsonTextTreeConversion, arrayWithSingleSubArray)
{
    auto t = Builder()
        .openSubtree()
            .pushBack(234)
            .pushBack(true)
            .pushBack("hello")
            .pushBack(false)
        .closeSubtree()
    .getTree();
    auto expected = "[[234,true,\"hello\",false]]";
    auto actual = toJsonText(t);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionHelpersToJsonTextTreeConversion, arrayWithSingleNestedSubArray)
{
    auto t = Builder()
        .openSubtree()
        .openSubtree()
        .openSubtree()
            .pushBack(234)
            .pushBack(true)
            .pushBack("hello")
            .pushBack(false)
        .closeSubtree()
        .closeSubtree()
        .closeSubtree()
    .getTree();
    auto expected = "[[[[234,true,\"hello\",false]]]]";
    auto actual = toJsonText(t);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionHelpersToJsonTextTreeConversion, arrayWithMixOfValuesAndNestedSubArrays)
{
    auto t = Builder()
        .pushBack(2)
        .openSubtree()
            .openSubtree()
                .pushBack(234)
                .pushBack(true)
                .pushBack("hello")
                .pushBack(false)
            .closeSubtree()
            .pushBack(true)
        .closeSubtree()
        .openSubtree()
            .pushBack(3)
            .pushBack(false)
            .pushBack(4)
        .closeSubtree()
        .openSubtree()
            .openSubtree()
                .openSubtree()
                    .pushBack(1)
                    .pushBack(false)
                .closeSubtree()
            .closeSubtree()
        .closeSubtree()
    .getTree();
    auto expected =
        "[2,[[234,true,\"hello\",false],true],[3,false,4],[[[1,false]]]]";
    auto actual = toJsonText(t);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionHelpersToJsonTextTreeConversion, documentWithSingleKeyValue)
{
    auto t = Builder()
        .append("a", 123)
    .getTree();
    auto expected = "{\"a\":123}";
    auto actual = toJsonText(t);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionHelpersToJsonTextTreeConversion, documentWithMultipleKeyValues)
{
    auto t = Builder()
        .append("a", 123)
        .append("b", false)
        .append("c", 45)
        .append("d", "world")
    .getTree();
    auto expected = "{\"a\":123,\"b\":false,\"c\":45,\"d\":\"world\"}";
    auto actual = toJsonText(t);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionHelpersToJsonTextTreeConversion, documentWithSingleSubDocument)
{
    auto t = Builder()
        .openSubtree("subdoc")
            .append("a", 123)
        .closeSubtree()
    .getTree();
    auto expected = "{\"subdoc\":{\"a\":123}}";
    auto actual = toJsonText(t);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionHelpersToJsonTextTreeConversion, documentWithMultipleNestedSubdocuments)
{
    auto t = Builder()
        .openSubtree("1")
            .openSubtree("2")
                .openSubtree("3")
                    .append("a", 123)
                .closeSubtree()
            .closeSubtree()
        .closeSubtree()
        .openSubtree("4")
            .openSubtree("5")
                .append("b", false)
            .closeSubtree()
        .closeSubtree()
    .getTree();
    auto expected =
        "{\"1\":{\"2\":{\"3\":{\"a\":123}}},\"4\":{\"5\":{\"b\":false}}}";
    auto actual = toJsonText(t);
    EXPECT_EQ(expected, actual);
}
