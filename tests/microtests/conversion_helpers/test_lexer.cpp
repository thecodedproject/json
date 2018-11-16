#include <gmock/gmock.h>

#include <json/conversion_helpers/lexer.hpp>

using namespace CodedProject;
using namespace CodedProject::Json::ConversionHelpers;

class TestConversionHelpersLexer : public ::testing::Test
{
protected:
    void expectNextTokenEq(Token const& expectedToken, Lexer & lexer)
    {
        auto actual = lexer.next();
        EXPECT_EQ(expectedToken, actual) <<
            "Expected: " << toString(expectedToken) <<
            "\nActual: " << toString(actual);
    }

    void expectEndOfFile(Lexer & lexer)
    {
        expectNextTokenEq(Token{TokenType::Eof, {}}, lexer);
    }
};

TEST_F(TestConversionHelpersLexer, givesCorrectTokenForStringAndStripsDoubleQuotes)
{
    auto json_text = "\"hello\"";

    auto lexer = Lexer(json_text);
    expectNextTokenEq({TokenType::Value, "hello"}, lexer);
    expectEndOfFile(lexer);
}

TEST_F(TestConversionHelpersLexer, givesCorrectTokenForDiffertStringAndStripsDoubleQuotes)
{
    auto json_text = "\"world\"";

    auto lexer = Lexer(json_text);
    expectNextTokenEq({TokenType::Value, "world"}, lexer);
    expectEndOfFile(lexer);
}

TEST_F(TestConversionHelpersLexer, givesCorrectTokenForInt)
{
    auto json_text = "1234";

    auto lexer = Lexer(json_text);
    expectNextTokenEq({TokenType::Value, 1234}, lexer);
    expectEndOfFile(lexer);
}

TEST_F(TestConversionHelpersLexer, givesCorrectTokenForNegativeInt)
{
    auto json_text = "-1234";

    auto lexer = Lexer(json_text);
    expectNextTokenEq({TokenType::Value, -1234}, lexer);
    expectEndOfFile(lexer);
}

TEST_F(TestConversionHelpersLexer, givesCorrectTokenForFloat)
{
    auto json_text = "123.4";

    auto lexer = Lexer(json_text);
    expectNextTokenEq({TokenType::Value, 123.4f}, lexer);
    expectEndOfFile(lexer);
}

TEST_F(TestConversionHelpersLexer, givesCorrectTokenForNegativeFloat)
{
    auto json_text = "-123.4";

    auto lexer = Lexer(json_text);
    expectNextTokenEq({TokenType::Value, -123.4f}, lexer);
    expectEndOfFile(lexer);
}

TEST_F(TestConversionHelpersLexer, givesCorrectTokenForTrueValue)
{
    auto json_text = "true";

    auto lexer = Lexer(json_text);
    expectNextTokenEq({TokenType::Value, true}, lexer);
    expectEndOfFile(lexer);
}

TEST_F(TestConversionHelpersLexer, givesCorrectTokenForFalseValue)
{
    auto json_text = "false";

    auto lexer = Lexer(json_text);
    expectNextTokenEq({TokenType::Value, false}, lexer);
    expectEndOfFile(lexer);
}

TEST_F(TestConversionHelpersLexer, givesCorrectTokenForNullValue)
{
    auto json_text = "null";

    auto lexer = Lexer(json_text);
    expectNextTokenEq({TokenType::Value, Json::Value()}, lexer);
    expectEndOfFile(lexer);
}

TEST_F(TestConversionHelpersLexer, givesCorrectTokensForArrayWithSingleIntWithOneDigit)
{
    auto json_text = "[1]";

    auto lexer = Lexer(json_text);

    expectNextTokenEq({TokenType::LeftArrayBrace}, lexer);
    expectNextTokenEq({TokenType::Value, 1}, lexer);
    expectNextTokenEq({TokenType::RightArrayBrace}, lexer);
    expectEndOfFile(lexer);
}

TEST_F(TestConversionHelpersLexer, givesCorrectTokensForArrayWithSingleIntWithManyDigit)
{
    auto json_text = "[123456]";

    auto lexer = Lexer(json_text);

    expectNextTokenEq({TokenType::LeftArrayBrace}, lexer);
    expectNextTokenEq({TokenType::Value, 123456}, lexer);
    expectNextTokenEq({TokenType::RightArrayBrace}, lexer);
    expectEndOfFile(lexer);
}

TEST_F(TestConversionHelpersLexer, givesCorrectTokensForArrayWithSingleFloatWithManyDigits)
{
    auto json_text = "[12345.50]";

    auto lexer = Lexer(json_text);

    expectNextTokenEq({TokenType::LeftArrayBrace}, lexer);
    expectNextTokenEq({TokenType::Value, 12345.50f}, lexer);
    expectNextTokenEq({TokenType::RightArrayBrace}, lexer);
    expectEndOfFile(lexer);
}

TEST_F(TestConversionHelpersLexer, givesCorrectTokensForArrayWithSingleString)
{
    auto json_text = "[\"hello\"]";

    auto lexer = Lexer(json_text);

    expectNextTokenEq({TokenType::LeftArrayBrace}, lexer);
    expectNextTokenEq({TokenType::Value, "hello"}, lexer);
    expectNextTokenEq({TokenType::RightArrayBrace}, lexer);
    expectEndOfFile(lexer);
}

TEST_F(TestConversionHelpersLexer, givesCorrectTokensForArrayWithSingleBool)
{
    auto json_text = "[true]";

    auto lexer = Lexer(json_text);

    expectNextTokenEq({TokenType::LeftArrayBrace}, lexer);
    expectNextTokenEq({TokenType::Value, true}, lexer);
    expectNextTokenEq({TokenType::RightArrayBrace}, lexer);
    expectEndOfFile(lexer);
}

TEST_F(TestConversionHelpersLexer, givesCorrectTokensForArrayWithSingleNullValue)
{
    auto json_text = "[null]";

    auto lexer = Lexer(json_text);

    expectNextTokenEq({TokenType::LeftArrayBrace}, lexer);
    expectNextTokenEq({TokenType::Value, {}}, lexer);
    expectNextTokenEq({TokenType::RightArrayBrace}, lexer);
    expectEndOfFile(lexer);
}

TEST_F(TestConversionHelpersLexer, givesCorrectTokensForArrayWithMultipleValuesOfDifferentTypes)
{
    auto json_text = "[null,1234,\"hello world\",23.5,true,false,-45,-11.5]";

    auto lexer = Lexer(json_text);

    expectNextTokenEq({TokenType::LeftArrayBrace}, lexer);
    expectNextTokenEq({TokenType::Value, {}}, lexer);
    expectNextTokenEq({TokenType::Comma}, lexer);
    expectNextTokenEq({TokenType::Value, 1234}, lexer);
    expectNextTokenEq({TokenType::Comma}, lexer);
    expectNextTokenEq({TokenType::Value, "hello world"}, lexer);
    expectNextTokenEq({TokenType::Comma}, lexer);
    expectNextTokenEq({TokenType::Value, 23.5f}, lexer);
    expectNextTokenEq({TokenType::Comma}, lexer);
    expectNextTokenEq({TokenType::Value, true}, lexer);
    expectNextTokenEq({TokenType::Comma}, lexer);
    expectNextTokenEq({TokenType::Value, false}, lexer);
    expectNextTokenEq({TokenType::Comma}, lexer);
    expectNextTokenEq({TokenType::Value, -45}, lexer);
    expectNextTokenEq({TokenType::Comma}, lexer);
    expectNextTokenEq({TokenType::Value, -11.5f}, lexer);
    expectNextTokenEq({TokenType::RightArrayBrace}, lexer);
    expectEndOfFile(lexer);
}

TEST_F(TestConversionHelpersLexer,
    givesCorrectTokensForArrayWithMultipleValuesAndWhitespaceOfSpaces)
{
    auto json_text = " [ null ,   1234 ,   \"hello world\" ,23.5,  true  , false  ] ";

    auto lexer = Lexer(json_text);

    expectNextTokenEq({TokenType::LeftArrayBrace}, lexer);
    expectNextTokenEq({TokenType::Value, {}}, lexer);
    expectNextTokenEq({TokenType::Comma}, lexer);
    expectNextTokenEq({TokenType::Value, 1234}, lexer);
    expectNextTokenEq({TokenType::Comma}, lexer);
    expectNextTokenEq({TokenType::Value, "hello world"}, lexer);
    expectNextTokenEq({TokenType::Comma}, lexer);
    expectNextTokenEq({TokenType::Value, 23.5f}, lexer);
    expectNextTokenEq({TokenType::Comma}, lexer);
    expectNextTokenEq({TokenType::Value, true}, lexer);
    expectNextTokenEq({TokenType::Comma}, lexer);
    expectNextTokenEq({TokenType::Value, false}, lexer);
    expectNextTokenEq({TokenType::RightArrayBrace}, lexer);
    expectEndOfFile(lexer);
}

TEST_F(TestConversionHelpersLexer,
    givesCorrectTokensForArrayWithMultipleValuesAndNewLineCharacters)
{
    auto json_text = "\n[null\n,\n1234,\n\"hello world\"\n,23.5,\ntrue,\n\n\nfalse\n\n]\n";

    auto lexer = Lexer(json_text);

    expectNextTokenEq({TokenType::LeftArrayBrace}, lexer);
    expectNextTokenEq({TokenType::Value, {}}, lexer);
    expectNextTokenEq({TokenType::Comma}, lexer);
    expectNextTokenEq({TokenType::Value, 1234}, lexer);
    expectNextTokenEq({TokenType::Comma}, lexer);
    expectNextTokenEq({TokenType::Value, "hello world"}, lexer);
    expectNextTokenEq({TokenType::Comma}, lexer);
    expectNextTokenEq({TokenType::Value, 23.5f}, lexer);
    expectNextTokenEq({TokenType::Comma}, lexer);
    expectNextTokenEq({TokenType::Value, true}, lexer);
    expectNextTokenEq({TokenType::Comma}, lexer);
    expectNextTokenEq({TokenType::Value, false}, lexer);
    expectNextTokenEq({TokenType::RightArrayBrace}, lexer);
    expectEndOfFile(lexer);
}

TEST_F(TestConversionHelpersLexer,
    givesCorrectTokensForDictionaryWithMultipleKeyValuesOfDifferentTypes)
{
    auto json_text =
        "{\"a\":null,\"b\":1234,\"c\":\"hello world\",\"d\":23.5,\"e\":true,\"f\":false}";

    auto lexer = Lexer(json_text);

    expectNextTokenEq({TokenType::LeftDocumentBrace}, lexer);
    expectNextTokenEq({TokenType::Value, "a"}, lexer);
    expectNextTokenEq({TokenType::Colon}, lexer);
    expectNextTokenEq({TokenType::Value, {}}, lexer);
    expectNextTokenEq({TokenType::Comma}, lexer);
    expectNextTokenEq({TokenType::Value, "b"}, lexer);
    expectNextTokenEq({TokenType::Colon}, lexer);
    expectNextTokenEq({TokenType::Value, 1234}, lexer);
    expectNextTokenEq({TokenType::Comma}, lexer);
    expectNextTokenEq({TokenType::Value, "c"}, lexer);
    expectNextTokenEq({TokenType::Colon}, lexer);
    expectNextTokenEq({TokenType::Value, "hello world"}, lexer);
    expectNextTokenEq({TokenType::Comma}, lexer);
    expectNextTokenEq({TokenType::Value, "d"}, lexer);
    expectNextTokenEq({TokenType::Colon}, lexer);
    expectNextTokenEq({TokenType::Value, 23.5f}, lexer);
    expectNextTokenEq({TokenType::Comma}, lexer);
    expectNextTokenEq({TokenType::Value, "e"}, lexer);
    expectNextTokenEq({TokenType::Colon}, lexer);
    expectNextTokenEq({TokenType::Value, true}, lexer);
    expectNextTokenEq({TokenType::Comma}, lexer);
    expectNextTokenEq({TokenType::Value, "f"}, lexer);
    expectNextTokenEq({TokenType::Colon}, lexer);
    expectNextTokenEq({TokenType::Value, false}, lexer);
    expectNextTokenEq({TokenType::RightDocumentBrace}, lexer);
    expectEndOfFile(lexer);
}
