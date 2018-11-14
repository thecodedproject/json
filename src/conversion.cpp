#include <json/conversion.hpp>

#include <json/builder.hpp>

namespace CodedProject
{
namespace Json
{

Tree fromString(std::string const& json_string)
{
    return Json::Builder()
        .append("i", 1)
        .getTree();
}

}
}
