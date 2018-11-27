#include <json/conversion_helpers/token.hpp>

namespace CodedProject
{
namespace Json
{
namespace ConversionHelpers
{

bool Token::operator==(Token const& rhs) const
{
    return type == rhs.type &&
        value == rhs.value;
}

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
        case TokenType::StringValue:
            return "TokenType::StringValue";
        case TokenType::Eof:
            return "TokenType::Eof";
        case TokenType::StartOfFile:
            return "TokenType::StartOfFile";
    }
}

std::string toString(Token const& token)
{
    if(token.type == TokenType::Value ||
        token.type == TokenType::StringValue)
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
}
}
