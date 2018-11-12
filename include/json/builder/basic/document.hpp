#pragma once

#include <memory>

#include <json/tree.hpp>

namespace CodedProject
{
namespace Json
{
namespace Builder
{
namespace Basic
{

class Document
{
public:
    Document();

    template <typename T>
    Document& append(
        std::string const& field,
        T const& value);

    Document& openDocument(std::string const& field);

    Document& closeDocument();

    Tree getTree();

private:
    Document(
        Document * parent_builder,
        std::string const& parent_field_name);

    Tree tree_ = {};
    std::unique_ptr<Document> child_builder_ = {};
    Document * parent_builder_ = nullptr;
    std::string parent_field_name_ = {};
};

template <typename T>
Document& Document::append(
    std::string const& field,
    T const& value)
{
    tree_[field] = value;
    return *this;
}

}
}
}
}
