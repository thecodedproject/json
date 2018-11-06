#include <json/tree.hpp>

namespace CodedProject
{
namespace Json
{

Tree::Tree() = default;

bool Tree::isArray() const
{
    return is_array_;
}

bool Tree::isDocument() const
{
    return is_document_;
}

bool Tree::isValue() const
{
    return is_value_;
}

Tree::iterator Tree::begin()
{
    return std::begin(document_values_);
}

Tree::const_iterator Tree::begin() const
{
    return std::begin(document_values_);
}

Tree::const_iterator Tree::cbegin() const noexcept
{
    return std::cbegin(document_values_);
}

Tree::iterator Tree::end()
{
    return std::end(document_values_);
}

Tree::const_iterator Tree::end() const
{
    return std::end(document_values_);
}

Tree::const_iterator Tree::cend() const noexcept
{
    return std::cend(document_values_);
}

Tree & Tree::operator[] (size_t index)
{
    if(!isArray())
    {
        throw IncorrectCallForType(
            "array function `operator[] (size_t)`",
            typeAsString());
    }

    return array_values_[index];
}

void Tree::pushBack(Tree subtree)
{
    is_array_ = true;
    array_values_.push_back(subtree);
}

size_t Tree::size() const
{
    if(isArray())
        return array_values_.size();
    else
        return document_values_.size();
}

Tree & Tree::operator[] (std::string const& field)
{
    if(isNotDocument())
    {
        throw IncorrectCallForType(
            "document function `operator[] (std::string)`",
            typeAsString());
    }

    is_document_ = true;
    return document_values_[field];
}

int Tree::count(std::string const& field_name) const
{
    if(isNotDocument())
    {
        throw IncorrectCallForType(
            "document function `count()`",
            typeAsString());
    }

    return document_values_.count(field_name);
}

Value const& Tree::getValue() const
{
    return value_;
}

std::string Tree::asString() const
{
    return value_.asString();
}

int Tree::asInteger() const
{
    return value_.asInteger();
}

float Tree::asFloat() const
{
    return value_.asFloat();
}

bool Tree::asBool() const
{
    return value_.asBool();
}

std::string Tree::typeAsString() const
{
    if(isArray())
        return "array";
    else if(isDocument())
        return "document";
    else
        return "value";
}

bool Tree::isNotDocument() const
{
    return isValue() || isArray();
}

}
}
