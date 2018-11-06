#pragma once

#include <map>
#include <stdexcept>
#include <vector>

#include <json/value.hpp>

namespace CodedProject
{
namespace Json
{

class Tree
{
public:
    class IncorrectCallForType : public std::runtime_error
    {
    public:
        IncorrectCallForType(
            std::string const& function_description,
            std::string const& tree_type)
        : std::runtime_error(
            "Trying to call " + function_description +
            " on tree of type " + tree_type + ".")
        {
        }
    };

    typedef std::map<std::string, Tree>::iterator iterator;
    typedef std::map<std::string, Tree>::const_iterator const_iterator;

    Tree();

    template <typename T>
    Tree(T const& value);

    bool isArray() const;
    bool isDocument() const;
    bool isValue() const;

    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const noexcept;
    iterator end();
    const_iterator end() const;
    const_iterator cend() const noexcept;

    // ----- Array functions -------
    Tree & operator[] (size_t index);

    void pushBack(Tree subtree);

    size_t size() const;

    // ----- Document functions -------

    Tree & operator[] (std::string const& field);
    // std::map doesn't have a const version of operator[].
    // Not sure why, but it makes me think that this function
    // shouldnt be defined. Certinaly it's stops things
    // compiling as it is - leaving it not defined for now
    // JDC 20181105
    //Value const& operator[] (std::string const& field) const;

    int count(std::string const& field_name) const;

    // ----- Value functions -------
    Value const& getValue() const;
    std::string asString() const;
    int asInteger() const;
    float asFloat() const;
    bool asBool() const;

private:

    std::string typeAsString() const;

    bool isNotDocument() const;

    bool is_array_ = false;
    bool is_document_ = false;
    bool is_value_ = false;

    std::vector<Tree> array_values_ = {};
    std::map<std::string, Tree> document_values_ = {};
    Value value_ = {};
};

template <typename T>
Tree::Tree(T const& value)
: is_value_(true),
  value_(value)
{
}


}
}
