#include <json/builder/basic/document.hpp>

namespace CodedProject
{
namespace Json
{
namespace Builder
{
namespace Basic
{

Document::Document() = default;

Document::Document(
    Document * parent_builder,
    std::string const& parent_field_name)
: parent_builder_{parent_builder},
  parent_field_name_{parent_field_name}
{
}

Document& Document::openDocument(std::string const& field)
{
    child_builder_ = std::unique_ptr<Document>(
        new Document(this, field));
    return *child_builder_;
}

Document& Document::closeDocument()
{
    parent_builder_->append(
        parent_field_name_,
        getTree());
    return *parent_builder_;
}

Tree Document::getTree()
{
    return tree_;
}

}
}
}
}
