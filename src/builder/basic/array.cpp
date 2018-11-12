#include <json/builder/basic/array.hpp>

namespace CodedProject
{
namespace Json
{
namespace Builder
{
namespace Basic
{

Array& Array::openArray()
{
    return *this;
}

Array& Array::closeArray()
{
    return *this;
}

Tree Array::getTree() const
{
    return tree_;
}

}
}
}
}
