#pragma once

#include <list>
#include <string>

#include <json/value.hpp>

namespace CodedProject
{
namespace Json
{
namespace ConversionHelpers
{

enum class TokenType
{
    LeftArrayBrace,
    RightArrayBrace,
    LeftDocumentBrace,
    RightDocumentBrace,
    Colon,
    Comma,
    Value,
    Eof
};

namespace {
std::string toString(TokenType const& type)
{
    switch(type)
    {
        case TokenType::LeftArrayBrace:
            return "TokenType::LeftArrayBrace";
        case TokenType::RightArrayBrace:
            return "TokenType::RightArrayBrace";
        case TokenType::LeftDocumentBrace:
            return "TokenType::LeftDocumentBrace";
        case TokenType::RightDocumentBrace:
            return "TokenType::RightDocumentBrace";
        case TokenType::Colon:
            return "TokenType::Colon";
        case TokenType::Comma:
            return "TokenType::Comma";
        case TokenType::Value:
            return "TokenType::Value";
        case TokenType::Eof:
            return "TokenType::Eof";
        default:
            return "TokenType::Unknown";
    }
}
}

struct Token
{
    TokenType type;
    Value value;

    bool operator==(Token const& rhs) const
    {
        return type == rhs.type &&
            value == rhs.value;
    }
};

namespace {
std::string toString(Token const& token)
{
    if(token.type == TokenType::Value)
    {
        return "Token("
            + toString(token.type)
            + ", "
            + toString(token.value)
            + ")";
    }
    else
    {
        return "Token("
            + toString(token.type)
            + ")";

    }
}
}

class Lexer
{
public:
    Lexer(std::string const& json_text);

    Token next();

private:

    void skipWhitespace();

    Token handleNextToken();

    Token advanceCurrentCharAndReturnToken(
        std::pair<Token, size_t> const& token_and_length);

    Token handleStringValue();

    Token handleNumberValue();

    std::string json_text_ = {};
    std::string::const_iterator current_char_ = {};
    bool first_call_ = true;
};

}
}
}
