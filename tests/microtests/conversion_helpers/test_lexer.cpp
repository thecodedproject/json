#include <gmock/gmock.h>

#include <json/conversion_helpers/lexer.hpp>

using namespace CodedProject;
using namespace CodedProject::Json::ConversionHelpers;
using namespace ::testing;

class TestConversionHelpersLexer : public ::testing::Test
{
protected:

    void expectEq(Token const& expectedToken, Token const& actualToken)
    {
        EXPECT_EQ(expectedToken, actualToken) <<
            "Expected: " << toString(expectedToken) <<
            "\nActual: " << toString(actualToken);
    }

    void expectNextTokenEq(Token const& expectedToken, Lexer & lexer)
    {
        auto actual = lexer.next();
        expectEq(expectedToken, actual);
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
    expectNextTokenEq({TokenType::StringValue, "hello"}, lexer);
    expectEndOfFile(lexer);
}

TEST_F(TestConversionHelpersLexer, givesCorrectTokenForDiffertStringAndStripsDoubleQuotes)
{
    auto json_text = "\"world\"";

    auto lexer = Lexer(json_text);
    expectNextTokenEq({TokenType::StringValue, "world"}, lexer);
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
    expectNextTokenEq({TokenType::StringValue, "hello"}, lexer);
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
    expectNextTokenEq({TokenType::StringValue, "hello world"}, lexer);
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
    expectNextTokenEq({TokenType::StringValue, "hello world"}, lexer);
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
    expectNextTokenEq({TokenType::StringValue, "hello world"}, lexer);
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
    expectNextTokenEq({TokenType::StringValue, "a"}, lexer);
    expectNextTokenEq({TokenType::Colon}, lexer);
    expectNextTokenEq({TokenType::Value, {}}, lexer);
    expectNextTokenEq({TokenType::Comma}, lexer);
    expectNextTokenEq({TokenType::StringValue, "b"}, lexer);
    expectNextTokenEq({TokenType::Colon}, lexer);
    expectNextTokenEq({TokenType::Value, 1234}, lexer);
    expectNextTokenEq({TokenType::Comma}, lexer);
    expectNextTokenEq({TokenType::StringValue, "c"}, lexer);
    expectNextTokenEq({TokenType::Colon}, lexer);
    expectNextTokenEq({TokenType::StringValue, "hello world"}, lexer);
    expectNextTokenEq({TokenType::Comma}, lexer);
    expectNextTokenEq({TokenType::StringValue, "d"}, lexer);
    expectNextTokenEq({TokenType::Colon}, lexer);
    expectNextTokenEq({TokenType::Value, 23.5f}, lexer);
    expectNextTokenEq({TokenType::Comma}, lexer);
    expectNextTokenEq({TokenType::StringValue, "e"}, lexer);
    expectNextTokenEq({TokenType::Colon}, lexer);
    expectNextTokenEq({TokenType::Value, true}, lexer);
    expectNextTokenEq({TokenType::Comma}, lexer);
    expectNextTokenEq({TokenType::StringValue, "f"}, lexer);
    expectNextTokenEq({TokenType::Colon}, lexer);
    expectNextTokenEq({TokenType::Value, false}, lexer);
    expectNextTokenEq({TokenType::RightDocumentBrace}, lexer);
    expectEndOfFile(lexer);
}

TEST_F(TestConversionHelpersLexer, DISABLED_givesCorrectTokensForJsonWithWindowsLineEndings)
{
    // Cant be bothered to implement this right now... JDC 20181116
}

TEST_F(TestConversionHelpersLexer, getCurrentTokenBeforeNextHasBeenCalledReturnsStartOfFile)
{
    auto json_text = "\"hello\"";

    auto lexer = Lexer(json_text);
    expectEq({TokenType::StartOfFile}, lexer.currentToken());
}

TEST_F(TestConversionHelpersLexer, getsCorrectCurrentTokenEachTimeAfterNextIsCalled)
{
    auto json_text = "[null,1234,\"hello world\",23.5,true,false,-45,-11.5]";

    auto lexer = Lexer(json_text);

    lexer.next();
    expectEq({TokenType::LeftArrayBrace}, lexer.currentToken());
    lexer.next();
    expectEq({TokenType::Value, {}}, lexer.currentToken());
    lexer.next();
    expectEq({TokenType::Comma}, lexer.currentToken());
    lexer.next();
    expectEq({TokenType::Value, 1234}, lexer.currentToken());
    lexer.next();
    expectEq({TokenType::Comma}, lexer.currentToken());
    lexer.next();
    expectEq({TokenType::StringValue, "hello world"}, lexer.currentToken());
    lexer.next();
    expectEq({TokenType::Comma}, lexer.currentToken());
    lexer.next();
    expectEq({TokenType::Value, 23.5f}, lexer.currentToken());
    lexer.next();
    expectEq({TokenType::Comma}, lexer.currentToken());
    lexer.next();
    expectEq({TokenType::Value, true}, lexer.currentToken());
    lexer.next();
    expectEq({TokenType::Comma}, lexer.currentToken());
    lexer.next();
    expectEq({TokenType::Value, false}, lexer.currentToken());
    lexer.next();
    expectEq({TokenType::Comma}, lexer.currentToken());
    lexer.next();
    expectEq({TokenType::Value, -45}, lexer.currentToken());
    lexer.next();
    expectEq({TokenType::Comma}, lexer.currentToken());
    lexer.next();
    expectEq({TokenType::Value, -11.5f}, lexer.currentToken());
    lexer.next();
    expectEq({TokenType::RightArrayBrace}, lexer.currentToken());
    lexer.next();
    expectEq({TokenType::Eof}, lexer.currentToken());
}

TEST_F(TestConversionHelpersLexer,
    getNextTokenWithCorrentExpectedTokenTypeForStringValueDoesNotThrow)
{
    auto json_text = "\"hello\"";

    auto lexer = Lexer(json_text);
    lexer.next(TokenType::StringValue);
}

TEST_F(TestConversionHelpersLexer,
    getNextTokenForStringValueWhenExpectingRightDocBraceThrowsWithHelpfulMessage)
{
    auto json_text = "\"hello\"";
    auto expected_token = TokenType::RightDocumentBrace;
    auto lexer = Lexer(json_text);
    EXPECT_THROW({
        try
        {
            lexer.next(expected_token);
        }
        catch(Json::ParseError & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("line 1, column 1"));
            EXPECT_THAT(err_msg, HasSubstr(toString(expected_token)));
            EXPECT_THAT(err_msg, HasSubstr("'\"hello\"'"));
            throw;
        }
    }, Json::ParseError);
}

TEST_F(TestConversionHelpersLexer,
    getNextTokenForIntValueWhenExpectingRightArrayBraceThrowsWithHelpfulMessage)
{
    auto json_text = "1245";
    auto expected_token = TokenType::RightArrayBrace;
    auto lexer = Lexer(json_text);
    EXPECT_THROW({
        try
        {
            lexer.next(expected_token);
        }
        catch(Json::ParseError & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("line 1, column 1"));
            EXPECT_THAT(err_msg, HasSubstr(toString(expected_token)));
            EXPECT_THAT(err_msg, HasSubstr("'1245'"));
            throw;
        }
    }, Json::ParseError);
}

TEST_F(TestConversionHelpersLexer,
    getNextTokenForIntValueWithWhitespaceWhenExpectingRightArrayBraceThrowsWithHelpfulMessage)
{
    auto json_text = "   1245";
    auto expected_token = TokenType::RightArrayBrace;
    auto lexer = Lexer(json_text);
    EXPECT_THROW({
        try
        {
            lexer.next(expected_token);
        }
        catch(Json::ParseError & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("line 1, column 4"));
            EXPECT_THAT(err_msg, HasSubstr(toString(expected_token)));
            EXPECT_THAT(err_msg, HasSubstr("'1245'"));
            throw;
        }
    }, Json::ParseError);
}

TEST_F(TestConversionHelpersLexer,
    getNextTokenForIntValueWithWhitspaceAndNewLineWhenExpectingRightArrayBraceThrowsWithHelpfulMessage)
{
    auto json_text = " \n \n \n     1245";
    auto expected_token = TokenType::RightArrayBrace;
    auto lexer = Lexer(json_text);
    EXPECT_THROW({
        try
        {
            lexer.next(expected_token);
        }
        catch(Json::ParseError & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("line 4, column 6"));
            EXPECT_THAT(err_msg, HasSubstr(toString(expected_token)));
            EXPECT_THAT(err_msg, HasSubstr("'1245'"));
            throw;
        }
    }, Json::ParseError);
}

TEST_F(TestConversionHelpersLexer,
    getNextTokenForIntValueInArrayWithWhenExpectingLeftArrayBraceThrowsWithHelpfulMessage)
{
    auto json_text = "[1, 2, 3, 4,";
    auto expected_token = TokenType::RightArrayBrace;
    auto lexer = Lexer(json_text);
    for(auto i=0; i<8; ++i)
        lexer.next();
    EXPECT_THROW({
        try
        {
            lexer.next(expected_token);
        }
        catch(Json::ParseError & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("line 1, column 12"));
            EXPECT_THAT(err_msg, HasSubstr(toString(expected_token)));
            EXPECT_THAT(err_msg, HasSubstr("','"));
            throw;
        }
    }, Json::ParseError);
}
