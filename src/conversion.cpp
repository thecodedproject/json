#include <json/conversion.hpp>

#include <json/conversion_helpers/grammer.hpp>
#include <json/conversion_helpers/lexer.hpp>
#include <json/conversion_helpers/to_json_text.hpp>

namespace CodedProject
{
namespace Json
{

Tree fromString(std::string const& json_string)
{
    using namespace Json::ConversionHelpers;
    auto lexer = Lexer(json_string);
    return Grammer::jsonExpression(lexer);
}

std::string toString(Tree const& tree)
{
    using namespace ConversionHelpers;
    if(tree.isArray())
    {
        auto temp = tree;
        return toJsonText(TokenType::LeftArrayBrace) +
            toString(temp[0]) +
            toJsonText(TokenType::RightArrayBrace);
    }
    else
    {
        return ConversionHelpers::toJsonText(tree.getValue());
    }
}

}
}
