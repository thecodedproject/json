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
            " on Json::Tree of type " + tree_type + ".")
        {
        }
    };

    typedef std::vector<std::pair<std::string, Tree>>::iterator iterator;
    typedef std::vector<std::pair<std::string, Tree>>::const_iterator const_iterator;
    typedef std::vector<std::pair<std::string, Tree>>::size_type size_type;

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

    size_t size() const;

    // ----- Array functions -------
    Tree & operator[] (size_t index);

    void pushBack(Tree subtree);

    // ----- Document functions -------

    Tree & operator[] (std::string const& field);
    // std::map doesn't have a const version of operator[].
    // Not sure why, but it makes me think that this function
    // shouldnt be defined. Certinaly it's stops things
    // compiling as it is - leaving it not defined for now
    // JDC 20181105
    //Value const& operator[] (std::string const& field) const;

    int count(std::string const& field_name) const;

    size_type erase(std::string const& field);

    // ----- Value functions -------
    Value const& getValue() const;
    std::string asString() const;
    int asInteger() const;
    float asFloat() const;
    bool asBool() const;

private:

    std::string typeAsString() const;

    bool isNotDocument() const;

    void throwIncorrectCallIfNotDocument(std::string function_signature) const;

    bool is_array_ = false;
    bool is_document_ = false;
    bool is_value_ = false;

    std::vector<std::pair<std::string, Tree>> values_ = {};
    std::map<std::string, size_t> field_indexes_ = {};
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
