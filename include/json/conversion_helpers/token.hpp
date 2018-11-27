#pragma once

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
    StringValue,
    Eof,
    StartOfFile
};

struct Token
{
    TokenType type;
    Value value;

    bool operator==(Token const& rhs) const;
};

std::string toString(TokenType const& type);
std::string toString(Token const& token);

}
}
}
