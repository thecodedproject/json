#pragma once

namespace CodedProject
{
namespace Json
{
namespace ConversionHelpers
{

enum class TokenType
{
    LEFT_ARRAY_BRACE,
    RIGHT_ARRAY_BRACE,
    LEFT_DOCUMENT_BRACE,
    RIGHT_DOCUMENT_BRACE,
    COLON,
    COMMA,
    STRING,
    INTEGER,
    FLOAT,
    BOOL,
    NULL_VALUE
};

struct Token
{
    TokenType type,
    std::string characters;
};

}
}
}
