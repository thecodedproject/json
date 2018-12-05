#include <json/tree.hpp>

#include <algorithm>

#include <iostream>

namespace CodedProject
{
namespace Json
{

Tree::Tree() = default;

Tree::Tree(Type type)
: type_(type)
{

}

bool Tree::operator== (Tree const& rhs) const
{
    if(type_ != rhs.type_)
        return false;

    if(isDocument() || isArray())
    {
        return values_ == rhs.values_;
    }

    return value_ == rhs.value_;
}

bool Tree::operator!= (Tree const& rhs) const
{
    return !operator==(rhs);
}

bool Tree::isArray() const
{
    return type_==Type::Array;
}

bool Tree::isDocument() const
{
    return type_==Type::Document;
}

bool Tree::isValue() const
{
    return type_==Type::Value;
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

void Tree::erase(iterator position)
{
    auto field_to_remove = position->first;
    erase(field_to_remove);
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

Tree & Tree::at(size_t index)
{
    return operator[](index);
}

Tree const& Tree::at(size_t index) const
{
    return const_cast<Tree*>(this)->operator[](index);
}

void Tree::pushBack(Tree subtree)
{
    type_ = Type::Array;
    values_.push_back({"",subtree});
}

Tree & Tree::operator[] (std::string const& field)
{
    throwIncorrectCallIfNotDocument("operator[] (std::string)");

    type_ = Type::Document;
    if(!count(field))
    {
        field_indexes_[field] = values_.size();
        values_.push_back({field, {}});
    }
    auto field_index = field_indexes_[field];
    return values_[field_index].second;
}

Tree & Tree::at(std::string const& field)
{
    return operator[](field);
}

Tree const& Tree::at(std::string const& field) const
{
    return const_cast<Tree*>(this)->operator[](field);
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
    if(isValue())
        return value_;
    else
        throw IncorrectCallForType(
            "value function `getValue()`",
            typeAsString());

}

std::string Tree::typeAsString() const
{
    return toString(type_);
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

std::string toString(Tree::Type type)
{
    switch(type)
    {
        case Tree::Type::Array:
            return "array";
        case Tree::Type::Document:
            return "document";
        case Tree::Type::Value:
            return "value";
        case Tree::Type::Uninitialised:
            return "uninitialised";
    }
}

}
}
