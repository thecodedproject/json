#pragma once

#include <string>

#include <json/fwd.hpp>

namespace CodedProject
{
namespace Json
{
namespace ConversionHelpers
{

std::string toJsonText(Tree const& t);

std::string toJsonText(Value const& v);

std::string toJsonText(Token const& t);

std::string toJsonText(TokenType const& type);

}
}
}
