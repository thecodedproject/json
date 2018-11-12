#pragma once

#include <memory>

#include <json/tree.hpp>

namespace CodedProject
{
namespace Json
{

class Builder
{
public:
    Builder();

    template <typename T>
    Builder& append(
        std::string const& field,
        T const& value);

    template <typename T>
    Builder& pushBack(
        T const& value);

    Builder& openArray();
    Builder& closeArray();

    Builder& openDocument(std::string const& field);
    Builder& closeDocument();

    Tree getTree();

private:
    Builder(
        Builder * parent_builder,
        std::string const& parent_field_name);

    Builder& setupChildBuilder(std::string const& field="");

    Tree tree_ = {};
    std::unique_ptr<Builder> child_builder_ = {};
    Builder * parent_builder_ = nullptr;
    std::string parent_field_name_ = {};
};

template <typename T>
Builder& Builder::append(
    std::string const& field,
    T const& value)
{
    tree_[field] = value;
    return *this;
}

template <typename T>
Builder& Builder::pushBack(T const& value)
{
    tree_.pushBack(value);
    return *this;
}

}
}
