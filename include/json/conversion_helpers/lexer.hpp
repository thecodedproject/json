#pragma once

#include <list>
#include <string>

#include <json/conversion_helpers/token.hpp>
#include <json/value.hpp>

namespace CodedProject
{
namespace Json
{

class ParseError : public std::runtime_error
{
public:
    ParseError(
        std::string const& actual_token_string,
        ConversionHelpers::TokenType const expected_token_type,
        int const error_line,
        int const error_column)
    : std::runtime_error(
        "line " + std::to_string(error_line) +
        ", column " + std::to_string(error_column) +
        " " + toString(expected_token_type) +
        " '" + actual_token_string + "'")
    {
    }
};

namespace ConversionHelpers
{

class Lexer
{
public:
    Lexer(std::string const& json_text);

    Token next();

    Token next(TokenType expectedTokenType);

    Token currentToken();

private:

    void skipWhitespace();

    Token handleNextToken();

    Token advanceCurrentCharAndReturnToken(
        std::pair<Token, size_t> const& token_and_length);

    Token handleStringValue();

    Token handleNumberValue();

    std::string tokenAsJsonText(Token const& token) const;

    std::string json_text_ = {};
    std::string::const_iterator current_char_ = {};
    std::string::const_iterator last_token_start_char_ = {};
    Token current_token_ = {TokenType::StartOfFile};
};

}
}
}
