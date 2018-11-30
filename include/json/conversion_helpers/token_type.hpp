#pragma once

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

}
}
}
