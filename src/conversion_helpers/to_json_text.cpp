#include <json/conversion_helpers/to_json_text.hpp>

#include <json/conversion_helpers/token.hpp>
#include <json/value.hpp>

namespace CodedProject
{
namespace Json
{
namespace ConversionHelpers
{

std::string toJsonText(Tree const& t)
{
    return {};
}

std::string toJsonText(Value const& v)
{
    switch(v.type())
    {
        case Value::Type::String:
            return "\"" + v.get<std::string>() + "\"";
        case Value::Type::Integer:
            return std::to_string(v.get<int>());
        case Value::Type::Bool:
            if(v.get<bool>())
                return "true";
            else
                return "false";
        case Value::Type::Float:
            return std::to_string(v.get<float>());
        case Value::Type::Null:
            return "null";
    }
}

std::string toJsonText(Token const& t)
{
    switch(t.type)
    {
        case TokenType::Value:
        case TokenType::StringValue:
            return toJsonText(t.value);
        case TokenType::Eof:
        case TokenType::StartOfFile:
            throw std::runtime_error(
                "ConversionHelpers::toJsonText(Token): Token" +
                toString(t.type) + " is not JSON serialisable.");
        default:
            return toJsonText(t.type);
    }
}

std::string toJsonText(TokenType const& type)
{
    switch(type)
    {
        case TokenType::LeftArrayBrace:
            return "[";
        case TokenType::RightArrayBrace:
            return "]";
        case TokenType::LeftDocumentBrace:
            return "{";
        case TokenType::RightDocumentBrace:
            return "}";
        case TokenType::Colon:
            return ":";
        case TokenType::Comma:
            return ",";
        case TokenType::Value:
        case TokenType::StringValue:
        case TokenType::Eof:
        case TokenType::StartOfFile:
            throw std::runtime_error(
                "ConversionHelpers::toJsonText(TokenType): Token type" +
                toString(type) + " cannot be converted to JSON without value.");
    }
}

}
}
}
