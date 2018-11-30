#pragma once

#include <string>

#include <json/conversion_helpers/token_type.hpp>
#include <json/value.hpp>

namespace CodedProject
{
namespace Json
{
namespace ConversionHelpers
{

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
