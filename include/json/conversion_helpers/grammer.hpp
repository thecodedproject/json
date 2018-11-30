#pragma once

#include <json/fwd.hpp>
#include <json/tree.hpp>

namespace CodedProject
{
namespace Json
{
namespace ConversionHelpers
{
namespace Grammer
{

Tree jsonExpression(Lexer & lexer);

Tree document(Lexer & lexer);

Tree array(Lexer & lexer);

}
}
}
}
