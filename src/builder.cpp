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

Builder& Builder::openArray()
{
    return setupChildBuilder();
}

Builder& Builder::closeArray()
{
    parent_builder_->pushBack(
        getTree());
    return *parent_builder_;
}

Builder& Builder::openDocument(std::string const& field)
{
    return setupChildBuilder(field);
}

Builder& Builder::closeDocument()
{
    parent_builder_->append(
        parent_field_name_,
        getTree());
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
