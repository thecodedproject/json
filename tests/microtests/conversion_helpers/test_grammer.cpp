#include <gmock/gmock.h>

#include <json/conversion_helpers/grammer.hpp>

#include <json/builder.hpp>
#include <json/conversion_helpers/lexer.hpp>
#include <json/parse_error.hpp>

using namespace CodedProject::Json;
using namespace CodedProject::Json::ConversionHelpers;
using namespace ::testing;

class TestGrammer : public ::testing::Test
{
};

TEST_F(TestGrammer, jsonExpressionWithStringValue)
{
    auto string_to_parse = "\"hello world\"";
    auto lexer = Lexer(string_to_parse);

    auto expected = Tree("hello world");

    auto actual = Grammer::jsonExpression(lexer);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestGrammer, jsonExpressionWithIntValue)
{
    auto string_to_parse = "3456";
    auto lexer = Lexer(string_to_parse);

    auto expected = Tree(3456);

    auto actual = Grammer::jsonExpression(lexer);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestGrammer, jsonExpressionWithEmptyDocument)
{
    auto string_to_parse = "{}";
    auto lexer = Lexer(string_to_parse);

    auto expected = Tree(Tree::Type::Document);

    auto actual = Grammer::jsonExpression(lexer);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestGrammer, jsonExpressionWithEmptyArray)
{
    auto string_to_parse = "[]";
    auto lexer = Lexer(string_to_parse);

    auto expected = Tree(Tree::Type::Array);

    auto actual = Grammer::jsonExpression(lexer);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestGrammer, jsonExpressionWithDocumentOfSingleValue)
{
    auto string_to_parse = "{\"a\": \"some_value\"}";
    auto lexer = Lexer(string_to_parse);

    auto expected = Builder()
        .append("a", "some_value")
        .getTree();

    auto actual = Grammer::jsonExpression(lexer);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestGrammer, jsonExpressionWithArrayOfSingleValue)
{
    auto string_to_parse = "[false]";
    auto lexer = Lexer(string_to_parse);

    auto expected = Builder()
        .pushBack(false)
    .getTree();

    auto actual = Grammer::jsonExpression(lexer);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestGrammer, jsonExpressionWithNestedArraysAnDocuments)
{
    auto string_to_parse = "["
        "{"
            "\"some_array\": [1, 2, 3],"
            "\"some_string\": \"hello world\""
        "},"
        "[true, 2, {\"a\": 1, \"b\": {\"c\": true}}],"
        "\"hello\""
    "]";
    auto lexer = Lexer(string_to_parse);

    auto expected = Builder()
        .openSubtree()
            .openSubtree("some_array")
                .pushBack(1)
                .pushBack(2)
                .pushBack(3)
            .closeSubtree()
            .append("some_string", "hello world")
        .closeSubtree()
        .openSubtree()
            .pushBack(true)
            .pushBack(2)
            .openSubtree()
                .append("a", 1)
                .openSubtree("b")
                    .append("c", true)
                .closeSubtree()
            .closeSubtree()
        .closeSubtree()
        .pushBack("hello")
    .getTree();

    auto actual = Grammer::jsonExpression(lexer);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestGrammer, documentWithSingleFieldAndStringValue)
{
    auto string_to_parse = "{\"a\": \"some_value\"}";
    auto lexer = Lexer(string_to_parse);

    auto expected = Builder()
        .append("a", "some_value")
        .getTree();

    auto actual = Grammer::document(lexer);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestGrammer, documentWithSingleFieldAndBoolValue)
{
    auto string_to_parse = "{\"some_bool\": true}";
    auto lexer = Lexer(string_to_parse);

    auto expected = Builder()
        .append("some_bool", true)
        .getTree();

    auto actual = Grammer::document(lexer);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestGrammer, documentWithTwoFieldsAndDifferentValues)
{
    auto string_to_parse = "{\"some_bool\": true, \"some_int\": 1234}";
    auto lexer = Lexer(string_to_parse);

    auto expected = Builder()
        .append("some_bool", true)
        .append("some_int", 1234)
        .getTree();

    auto actual = Grammer::document(lexer);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestGrammer, documentWithManyFieldsAndDifferentValues)
{
    auto string_to_parse = "{"
        "\"some_bool\": true,"
        "\"some_string\": \"hello world\","
        "\"some_float\": 12.5,"
        "\"some_int\": 1234"
    "}";
    auto lexer = Lexer(string_to_parse);

    auto expected = Builder()
        .append("some_bool", true)
        .append("some_string", "hello world")
        .append("some_float", 12.5f)
        .append("some_int", 1234)
        .getTree();

    auto actual = Grammer::document(lexer);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestGrammer, documentWithSingleFieldAndDocumentValue)
{
    auto string_to_parse = "{\"some_doc\": { \"some_doc_field\": 12345 }}";
    auto lexer = Lexer(string_to_parse);

    auto expected = Builder()
        .openSubtree("some_doc")
            .append("some_doc_field", 12345)
        .closeSubtree()
    .getTree();

    auto actual = Grammer::document(lexer);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestGrammer, documentWithMultipleNestedDocuments)
{
    auto string_to_parse = "{"
        "\"some_doc1\":{"
            "\"some_doc2\":{"
                "\"some_doc3\":{"
                    "\"some_doc_field\": 12345"
                "}"
            "}"
        "}"
    "}";
    auto lexer = Lexer(string_to_parse);

    auto expected = Builder()
        .openSubtree("some_doc1")
            .openSubtree("some_doc2")
                .openSubtree("some_doc3")
                    .append("some_doc_field", 12345)
                .closeSubtree()
            .closeSubtree()
        .closeSubtree()
    .getTree();

    auto actual = Grammer::document(lexer);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestGrammer, documentThrowsParseErrorIfFirstTokenIsNotLeftDocBrace)
{
    auto string_to_parse = "true \"a\": true}";
    auto lexer = Lexer(string_to_parse);

    EXPECT_THROW({
        try
        {
            auto t = Grammer::document(lexer);
        }
        catch(ParseError & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("Expected"));
            EXPECT_THAT(err_msg, HasSubstr("LeftDocumentBrace"));
            EXPECT_THAT(err_msg, HasSubstr("'true'"));
            EXPECT_THAT(err_msg, HasSubstr("line 1, column 1"));
            throw;
        }
    }, ParseError);
}

TEST_F(TestGrammer, documentThrowsParseErrorIfSecondTokenIsNotStringValue)
{
    auto string_to_parse = "{123: true}";
    auto lexer = Lexer(string_to_parse);

    EXPECT_THROW({
        try
        {
            auto t = Grammer::document(lexer);
        }
        catch(ParseError & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("Expected"));
            EXPECT_THAT(err_msg, HasSubstr("StringValue"));
            EXPECT_THAT(err_msg, HasSubstr("'123'"));
            EXPECT_THAT(err_msg, HasSubstr("line 1, column 2"));
            throw;
        }
    }, ParseError);
}

TEST_F(TestGrammer, documentThrowsParseErrorRightDocBracePreceededByComma)
{
    auto string_to_parse = "{\"123\": true,}";
    auto lexer = Lexer(string_to_parse);

    EXPECT_THROW({
        try
        {
            auto t = Grammer::document(lexer);
        }
        catch(ParseError & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("Expected"));
            EXPECT_THAT(err_msg, HasSubstr("StringValue"));
            EXPECT_THAT(err_msg, HasSubstr("'}'"));
            EXPECT_THAT(err_msg, HasSubstr("line 1, column 14"));
            throw;
        }
    }, ParseError);
}

TEST_F(TestGrammer, documentThrowsParseErrorIfThirdTokenIsNotColon)
{
    auto string_to_parse = "{\"hello\" , true}";
    auto lexer = Lexer(string_to_parse);

    EXPECT_THROW({
        try
        {
            auto t = Grammer::document(lexer);
        }
        catch(ParseError & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("Expected"));
            EXPECT_THAT(err_msg, HasSubstr("Colon"));
            EXPECT_THAT(err_msg, HasSubstr("','"));
            EXPECT_THAT(err_msg, HasSubstr("line 1, column 10"));
            throw;
        }
    }, ParseError);
}

TEST_F(TestGrammer, documentThrowsParseErrorIfFinalTokenIsNotRightDocumentBrace)
{
    auto string_to_parse = "{\"hello\" : true null";
    auto lexer = Lexer(string_to_parse);

    EXPECT_THROW({
        try
        {
            auto t = Grammer::document(lexer);
        }
        catch(ParseError & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("Expected"));
            EXPECT_THAT(err_msg, HasSubstr("RightDocumentBrace"));
            EXPECT_THAT(err_msg, HasSubstr("'null'"));
            EXPECT_THAT(err_msg, HasSubstr("line 1, column 17"));
            throw;
        }
    }, ParseError);
}

TEST_F(TestGrammer, arrayWithSingleStringValue)
{
    auto string_to_parse = "[\"hello\"]";
    auto lexer = Lexer(string_to_parse);

    auto expected = Builder()
        .pushBack("hello")
    .getTree();

    auto actual = Grammer::array(lexer);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestGrammer, arrayWithSingleBoolValue)
{
    auto string_to_parse = "[false]";
    auto lexer = Lexer(string_to_parse);

    auto expected = Builder()
        .pushBack(false)
    .getTree();

    auto actual = Grammer::array(lexer);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestGrammer, arrayWithMultipleValues)
{
    auto string_to_parse = "[false, 234, true, null, \"hello\", 23.5]";
    auto lexer = Lexer(string_to_parse);

    auto expected = Builder()
        .pushBack(false)
        .pushBack(234)
        .pushBack(true)
        .pushBack(::CodedProject::Json::Value())
        .pushBack("hello")
        .pushBack(23.5f)
    .getTree();

    auto actual = Grammer::array(lexer);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestGrammer, arrayWithMultipleDocumentsAndValues)
{
    auto string_to_parse = "[false, {\"a\": 1}, {\"b\": null}, {\"c\": \"hello\"}]";
    auto lexer = Lexer(string_to_parse);

    auto expected = Builder()
        .pushBack(false)
        .openSubtree()
            .append("a", 1)
        .closeSubtree()
        .openSubtree()
            .append("b", ::CodedProject::Json::Value())
        .closeSubtree()
        .openSubtree()
            .append("c", "hello")
        .closeSubtree()
    .getTree();

    auto actual = Grammer::array(lexer);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestGrammer, arrayWithMultipleArrays)
{
    auto string_to_parse = "["
        "[1,2,3],"
        "[4,5,6],"
        "[7,8,9]"
    "]";
    auto lexer = Lexer(string_to_parse);

    auto expected = Builder()
        .openSubtree()
            .pushBack(1)
            .pushBack(2)
            .pushBack(3)
        .closeSubtree()
        .openSubtree()
            .pushBack(4)
            .pushBack(5)
            .pushBack(6)
        .closeSubtree()
        .openSubtree()
            .pushBack(7)
            .pushBack(8)
            .pushBack(9)
        .closeSubtree()
    .getTree();

    auto actual = Grammer::array(lexer);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestGrammer, arrayWithMultipleNestedArrays)
{
    auto string_to_parse = "[[[["
        "[1,2,3],"
        "[4,5,6],"
        "[7,8,9]"
    "]]]]";
    auto lexer = Lexer(string_to_parse);

    auto expected = Builder()
        .openSubtree()
        .openSubtree()
        .openSubtree()
        .openSubtree()
            .pushBack(1)
            .pushBack(2)
            .pushBack(3)
        .closeSubtree()
        .openSubtree()
            .pushBack(4)
            .pushBack(5)
            .pushBack(6)
        .closeSubtree()
        .openSubtree()
            .pushBack(7)
            .pushBack(8)
            .pushBack(9)
        .closeSubtree()
        .closeSubtree()
        .closeSubtree()
        .closeSubtree()
    .getTree();

    auto actual = Grammer::array(lexer);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestGrammer, arrayThrowsParseErrorIfFirstTokenIsNotLeftArrayBrace)
{
    auto string_to_parse = "true true]";
    auto lexer = Lexer(string_to_parse);

    EXPECT_THROW({
        try
        {
            auto t = Grammer::array(lexer);
        }
        catch(ParseError & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("Expected"));
            EXPECT_THAT(err_msg, HasSubstr("LeftArrayBrace"));
            EXPECT_THAT(err_msg, HasSubstr("'true'"));
            EXPECT_THAT(err_msg, HasSubstr("line 1, column 1"));
            throw;
        }
    }, ParseError);
}

TEST_F(TestGrammer, arrayThrowsParseErrorIfSecondTokenIsNotValueOrStringValueOpeneingBrace)
{
    auto string_to_parse = "[ : true]";
    auto lexer = Lexer(string_to_parse);

    EXPECT_THROW({
        try
        {
            auto t = Grammer::array(lexer);
        }
        catch(ParseError & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("Expected"));
            EXPECT_THAT(err_msg, HasSubstr("Value"));
            EXPECT_THAT(err_msg, HasSubstr("':'"));
            EXPECT_THAT(err_msg, HasSubstr("line 1, column 3"));
            throw;
        }
    }, ParseError);
}

TEST_F(TestGrammer, arrayThrowsParseErrorIfThridTokenIsNotCommaOrRightArrayBrace)
{
    auto string_to_parse = "[true } ]";
    auto lexer = Lexer(string_to_parse);

    EXPECT_THROW({
        try
        {
            auto t = Grammer::array(lexer);
        }
        catch(ParseError & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("Expected"));
            EXPECT_THAT(err_msg, HasSubstr("RightArrayBrace"));
            EXPECT_THAT(err_msg, HasSubstr("'}'"));
            EXPECT_THAT(err_msg, HasSubstr("line 1, column 7"));
            throw;
        }
    }, ParseError);
}

TEST_F(TestGrammer, arrayThrowsParseErrorIfRightArrayBraceIsPreceededByComma)
{
    auto string_to_parse = "[true,false,]";
    auto lexer = Lexer(string_to_parse);

    EXPECT_THROW({
        try
        {
            auto t = Grammer::array(lexer);
        }
        catch(ParseError & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("Expected"));
            EXPECT_THAT(err_msg, HasSubstr("Value"));
            EXPECT_THAT(err_msg, HasSubstr("']'"));
            EXPECT_THAT(err_msg, HasSubstr("line 1, column 13"));
            throw;
        }
    }, ParseError);
}

TEST_F(TestGrammer, arrayThrowsParseErrorIfRightArrayBraceIsPreceededByColon)
{
    auto string_to_parse = "[true,false:]";
    auto lexer = Lexer(string_to_parse);

    EXPECT_THROW({
        try
        {
            auto t = Grammer::array(lexer);
        }
        catch(ParseError & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("Expected"));
            EXPECT_THAT(err_msg, HasSubstr("RightArrayBrace"));
            EXPECT_THAT(err_msg, HasSubstr("':'"));
            EXPECT_THAT(err_msg, HasSubstr("line 1, column 12"));
            throw;
        }
    }, ParseError);
}
