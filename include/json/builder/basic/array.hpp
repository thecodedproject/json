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

class Array
{
public:

    template <typename T>
    Array& append(T const& value);

    Array& openArray();

    Array& closeArray();

    Tree getTree() const;

private:

    Tree tree_;
};

template <typename T>
Array& Array::append(T const& value)
{
    tree_.pushBack(value);
    return *this;
}

}
}
}
}
