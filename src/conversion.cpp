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

std::string toString(Tree const& tree, bool const format)
{
    using namespace ConversionHelpers;
    return toJsonText(tree, format);
}

}
}
