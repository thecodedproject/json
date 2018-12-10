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

TEST_F(TestConversionHelpersToJsonTextTreeConversion, arrayWithSingleSubDocument)
{
    auto t = Builder()
        .openSubtree()
            .append("a", 234)
        .closeSubtree()
    .getTree();
    auto expected = "[{\"a\":234}]";
    auto actual = toJsonText(t);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionHelpersToJsonTextTreeConversion, arrayWithMultipleSubDocumentasAndValues)
{
    auto t = Builder()
        .openSubtree()
            .append("a", 234)
        .closeSubtree()
        .pushBack(false)
        .openSubtree()
            .append("b", true)
        .closeSubtree()
    .getTree();
    auto expected = "[{\"a\":234},false,{\"b\":true}]";
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

TEST_F(TestConversionHelpersToJsonTextTreeConversion, documentWithSingleSubArray)
{
    auto t = Builder()
        .openSubtree("subdoc")
            .pushBack(1)
            .pushBack(true)
            .pushBack("c")
        .closeSubtree()
    .getTree();
    auto expected = "{\"subdoc\":[1,true,\"c\"]}";
    auto actual = toJsonText(t);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionHelpersToJsonTextTreeConversion, documentWithMultipleSubArraysAndValues)
{
    auto t = Builder()
        .openSubtree("subdoc")
            .pushBack(1)
            .pushBack(true)
            .pushBack("c")
        .closeSubtree()
        .append("a", 45)
        .openSubtree("other")
            .pushBack(true)
            .pushBack(2)
        .closeSubtree()
        .openSubtree("other2")
            .pushBack(false)
            .pushBack(3)
        .closeSubtree()
    .getTree();
    auto expected =
        "{\"subdoc\":[1,true,\"c\"],\"a\":45,\"other\":[true,2],\"other2\":[false,3]}";
    auto actual = toJsonText(t);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionHelpersToJsonTextTreeConversion, documentWithheavilyNestedArraysAndDocuments)
{
    auto t = Builder()
        .openSubtree("a")
            .openSubtree()
                .openSubtree("b")
                    .openSubtree()
                        .append("1", true)
                        .append("2", "c")
                    .closeSubtree()
                .closeSubtree()
            .closeSubtree()
        .closeSubtree()
        .append("b", 45)
        .openSubtree("c")
            .openSubtree("x")
                .openSubtree("y")
                    .openSubtree()
                        .openSubtree("z")
                            .pushBack(true)
                            .pushBack(2)
                        .closeSubtree()
                    .closeSubtree()
                .closeSubtree()
            .closeSubtree()
        .closeSubtree()
    .getTree();
    auto expected = "{"
        "\"a\":[{\"b\":[{\"1\":true,\"2\":\"c\"}]}],"
        "\"b\":45,"
        "\"c\":{\"x\":{\"y\":[{\"z\":[true,2]}]}}"
    "}";
    auto actual = toJsonText(t);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionHelpersToJsonTextTreeConversion, formattedDocumentWithSingleField)
{
    auto t = Builder()
        .append("a", true)
    .getTree();
    auto expected = "{\n    \"a\": true\n}";
    auto actual = toJsonText(t, true);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionHelpersToJsonTextTreeConversion, formattedDocumentWithmultipleFields)
{
    auto t = Builder()
        .append("a", true)
        .append("b", false)
        .append("c", 1)
    .getTree();
    auto expected = "{\n"
        "    \"a\": true,\n"
        "    \"b\": false,\n"
        "    \"c\": 1\n"
    "}";
    auto actual = toJsonText(t, true);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionHelpersToJsonTextTreeConversion, formattedArrayWithMultipleFields)
{
    auto t = Builder()
        .pushBack(true)
        .pushBack(123)
        .pushBack("hello")
    .getTree();
    auto expected = "[\n"
        "    true,\n"
        "    123,\n"
        "    \"hello\"\n"
    "]";
    auto actual = toJsonText(t, true);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionHelpersToJsonTextTreeConversion, formattedDocumentWithNestedDocument)
{
    auto t = Builder()
        .append("a", true)
        .openSubtree("b")
            .append("1", 1)
            .append("2", false)
        .closeSubtree()
    .getTree();
    auto expected =
        "{\n"
        "    \"a\": true,\n"
        "    \"b\": {\n"
        "        \"1\": 1,\n"
        "        \"2\": false\n"
        "    }\n"
        "}";
    auto actual = toJsonText(t, true);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionHelpersToJsonTextTreeConversion, formattedDocumentWithNestedArray)
{
    auto t = Builder()
        .append("a", true)
        .openSubtree("b")
            .pushBack(1)
            .pushBack(false)
        .closeSubtree()
    .getTree();
    auto expected =
        "{\n"
        "    \"a\": true,\n"
        "    \"b\": [\n"
        "        1,\n"
        "        false\n"
        "    ]\n"
        "}";
    auto actual = toJsonText(t, true);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionHelpersToJsonTextTreeConversion, formattedDocumentWithMultipleNestedArraysAndDocuments)
{
    auto t = Builder()
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
        .openSubtree("c")
            .openSubtree("1")
                .pushBack(true)
                .pushBack(6)
            .closeSubtree()
        .closeSubtree()
    .getTree();
    auto expected =
        "{\n"
        "    \"a\": true,\n"
        "    \"b\": [\n"
        "        1,\n"
        "        {\n"
        "            \"1\": [\n"
        "                5\n"
        "            ],\n"
        "            \"2\": {\n"
        "                \"a\": true\n"
        "            }\n"
        "        }\n"
        "    ],\n"
        "    \"c\": {\n"
        "        \"1\": [\n"
        "            true,\n"
        "            6\n"
        "        ]\n"
        "    }\n"
        "}";
    auto actual = toJsonText(t, true);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionHelpersToJsonTextTreeConversion, formattedArrayWithNestedArray)
{
    auto t = Builder()
        .pushBack(123)
        .openSubtree()
            .pushBack(true)
            .pushBack(345)
        .closeSubtree()
    .getTree();
    auto expected =
        "[\n"
        "    123,\n"
        "    [\n"
        "        true,\n"
        "        345\n"
        "    ]\n"
        "]";
    auto actual = toJsonText(t, true);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionHelpersToJsonTextTreeConversion, formattedArrayWithNestedDocument)
{
    auto t = Builder()
        .pushBack(123)
        .openSubtree()
            .append("a", true)
            .append("b", 345)
        .closeSubtree()
    .getTree();
    auto expected =
        "[\n"
        "    123,\n"
        "    {\n"
        "        \"a\": true,\n"
        "        \"b\": 345\n"
        "    }\n"
        "]";
    auto actual = toJsonText(t, true);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionHelpersToJsonTextTreeConversion, formattedArrayWithMultipleNestedDocumentsAndArrays)
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
    auto actual = toJsonText(t, true);
    EXPECT_EQ(expected, actual);
}
