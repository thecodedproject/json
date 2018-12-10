#pragma once

#include <json/tree.hpp>

namespace CodedProject
{
namespace Json
{

Tree fromString(std::string const& json_string);

std::string toString(Tree const& tree, bool format=false);

}
}
