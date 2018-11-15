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

TEST_F(TestConversionHelpersLexer, givesCorrectTokenForFloat)
{
    auto json_text = "123.4";

    auto lexer = Lexer(json_text);
    expectNextTokenEq({TokenType::Value, 123.4f}, lexer);
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
