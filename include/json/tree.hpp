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
    typedef std::vector<std::pair<std::string, Tree>> value_storage_type;
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

    enum class Type
    {
        Array,
        Document,
        Value,
        Uninitialised
    };

    typedef value_storage_type::iterator iterator;
    typedef value_storage_type::const_iterator const_iterator;
    typedef value_storage_type::size_type size_type;

    Tree();

    Tree(Type type);

    template <typename T>
    Tree(T const& value);

    bool operator== (Tree const& rhs) const;
    bool operator!= (Tree const& rhs) const;

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

    void erase(iterator position);

    // ----- Array functions -------
    Tree & operator[] (size_t index);

    Tree & at(size_t index);

    Tree const& at(size_t index) const;

    void pushBack(Tree subtree);

    // ----- Document functions -------

    Tree & operator[] (std::string const& field);
    // std::map doesn't have a const version of operator[].
    // Not sure why, but it makes me think that this function
    // shouldnt be defined. Certinaly it's stops things
    // compiling as it is - leaving it not defined for now
    // JDC 20181105
    //Value const& operator[] (std::string const& field) const;

    Tree & at(std::string const& field);

    Tree const& at(std::string const& field) const;

    int count(std::string const& field_name) const;

    size_type erase(std::string const& field);

    // ----- Value functions -------
    Value const& getValue() const;

    template <typename T>
    T get() const;

private:

    std::string typeAsString() const;

    bool isNotDocument() const;

    void throwIncorrectCallIfNotArray(
        std::string function_signature) const;

    void throwIncorrectCallIfNotDocument(
        std::string function_signature) const;

    void throwIncorrectCallIfPredicate(
        std::string function_signature,
        Type function_allowed_type,
        std::function<bool()> pred) const;

    Type type_ = Type::Uninitialised;

    value_storage_type values_ = {};
    std::map<std::string, size_t> field_indexes_ = {};
    Value value_ = {};
};

template <typename T>
Tree::Tree(T const& value)
: type_(Type::Value),
  value_(value)
{
}

template <typename T>
T Tree::get() const
{
    return value_.get<T>();
}

std::string toString(Tree::Type type);

}
}
