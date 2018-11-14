#include <json/builder.hpp>

namespace CodedProject
{
namespace Json
{

Builder::Builder() = default;

Builder::Builder(
    Builder * parent_builder,
    std::string const& parent_field_name)
: parent_builder_{parent_builder},
  parent_field_name_{parent_field_name}
{
}

Builder& Builder::openSubtree()
{
    return setupChildBuilder();
}

Builder& Builder::openSubtree(std::string const& field)
{
    return setupChildBuilder(field);
}

Builder& Builder::closeSubtree()
{
    if(parent_field_name_.empty())
    {
        parent_builder_->pushBack(
            getTree());
    }
    else
    {
        parent_builder_->append(parent_field_name_, getTree());
    }
    return *parent_builder_;
}

Tree Builder::getTree()
{
    return tree_;
}

Builder& Builder::setupChildBuilder(std::string const& field)
{
    child_builder_ = std::unique_ptr<Builder>(
        new Builder(this, field));
    return *child_builder_;
}

}
}
