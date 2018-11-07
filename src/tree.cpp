#include <json/tree.hpp>

#include <algorithm>

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
    return std::begin(values_);
}

Tree::const_iterator Tree::begin() const
{
    return std::begin(values_);
}

Tree::const_iterator Tree::cbegin() const noexcept
{
    return std::cbegin(values_);
}

Tree::iterator Tree::end()
{
    return std::end(values_);
}

Tree::const_iterator Tree::end() const
{
    return std::end(values_);
}

Tree::const_iterator Tree::cend() const noexcept
{
    return std::cend(values_);
}

size_t Tree::size() const
{
    return values_.size();
}

Tree & Tree::operator[] (size_t index)
{
    if(!isArray())
    {
        throw IncorrectCallForType(
            "array function `operator[] (size_t)`",
            typeAsString());
    }

    return values_[index].second;
}

void Tree::pushBack(Tree subtree)
{
    is_array_ = true;
    values_.push_back({"",subtree});
}

Tree & Tree::operator[] (std::string const& field)
{
    throwIncorrectCallIfNotDocument("operator[] (std::string)");

    is_document_ = true;
    if(!count(field))
    {
        field_indexes_[field] = values_.size();
        values_.push_back({field, {}});
    }
    auto field_index = field_indexes_[field];
    return values_[field_index].second;
}

int Tree::count(std::string const& field_name) const
{
    throwIncorrectCallIfNotDocument("count()");
    return field_indexes_.count(field_name);
}

Tree::size_type Tree::erase(std::string const& field_name)
{
    throwIncorrectCallIfNotDocument("erase(std::string)");

    if(!count(field_name))
        return 0;

    auto index_to_remove = field_indexes_[field_name];

    auto element_to_erase = std::begin(values_);
    std::advance(element_to_erase, index_to_remove);

    values_.erase(element_to_erase);

    for(auto & kv : field_indexes_)
    {
        if(kv.second>index_to_remove)
            --kv.second;
    }

    field_indexes_.erase(field_name);

    return 1;
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
    else if(isValue())
        return "value";
    else
        return "uninitalised Tree";
}

bool Tree::isNotDocument() const
{
    return isValue() || isArray();
}

void Tree::throwIncorrectCallIfNotDocument(std::string function_signature) const
{
    if(isNotDocument())
    {
        throw IncorrectCallForType(
            "document function `" + function_signature + "`",
            typeAsString());
    }
}

}
}
