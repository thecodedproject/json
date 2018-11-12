#include <gmock/gmock.h>

#include <json/builder/basic/document.hpp>

using namespace CodedProject;
using Json::Builder::Basic::Document;

class TestBuilderBasicDocument : public ::testing::Test
{
};

TEST_F(TestBuilderBasicDocument, constructEmptyTree)
{
    auto expected = Json::Tree();
    auto t = Document().getTree();
    EXPECT_EQ(expected, t);
}

TEST_F(TestBuilderBasicDocument, appendFieldAndStringValue)
{
    auto expected = Json::Tree();
    expected["string"] = std::string("hello");
    auto t = Document()
        .append("string", std::string("hello"))
        .getTree();
    EXPECT_EQ(expected, t);
}

TEST_F(TestBuilderBasicDocument, appendFieldAndIntegerValue)
{
    auto expected = Json::Tree();
    expected["integer"] = 123;
    auto t = Document()
        .append("integer", 123)
        .getTree();
    EXPECT_EQ(expected, t);
}

TEST_F(TestBuilderBasicDocument, appendFieldAndFloatValue)
{
    auto expected = Json::Tree();
    expected["floating point"] = 12.3f;
    auto t = Document()
        .append("floating point", 12.3f)
        .getTree();
    EXPECT_EQ(expected, t);
}

TEST_F(TestBuilderBasicDocument, appendFieldAndBoolValue)
{
    auto expected = Json::Tree();
    expected["boolean"] = true;
    auto t = Document()
        .append("boolean", true)
        .getTree();
    EXPECT_EQ(expected, t);
}

TEST_F(TestBuilderBasicDocument, appendFieldAndDocumentSubtreeValue)
{
    auto subtree = Json::Tree();
    subtree["a"] = std::string("some");
    subtree["b"] = 12.3f;
    auto expected = Json::Tree();
    expected["subtree"] = subtree;
    auto t = Document()
        .append("subtree", subtree)
        .getTree();
    EXPECT_EQ(expected, t);
}

TEST_F(TestBuilderBasicDocument, appendFieldAndSubarray)
{
    auto subarray = Json::Tree();
    subarray.pushBack(true);
    subarray.pushBack(123);
    auto expected = Json::Tree();
    expected["some_field"] = subarray;
    auto t = Document()
        .append("some_field", subarray)
        .getTree();
    EXPECT_EQ(expected, t);
}

TEST_F(TestBuilderBasicDocument, appendMutipleFieldsOfDifferentTypes)
{
    auto expected = Json::Tree();
    expected["boolean"] = true;
    expected["string"] = std::string("hello");
    expected["integer"] = 123;
    expected["floating point"] = 12.3f;
    expected["other_boolean"] = false;
    auto t = Document()
        .append("boolean", true)
        .append("string", std::string("hello"))
        .append("integer", 123)
        .append("floating point", 12.3f)
        .append("other_boolean", false)
        .getTree();
    EXPECT_EQ(expected, t);
}


TEST_F(TestBuilderBasicDocument, openSubdocumentForFieldAndAddSomeElements)
{
    auto subtree = Json::Tree();
    subtree["a"] = std::string("some");
    subtree["b"] = 12.3f;
    auto expected = Json::Tree();
    expected["subtree"] = subtree;
    auto t = Document()
        .openDocument("subtree")
            .append("a", std::string("some"))
            .append("b", 12.3f)
        .closeDocument()
        .getTree();
    EXPECT_EQ(expected, t);
}

TEST_F(TestBuilderBasicDocument, openMultipleSubdocumentsForFieldAndAddSomeElements)
{
    auto c_subtree = Json::Tree();
    c_subtree["a"] = std::string("some");
    c_subtree["b"] = 12.3f;
    auto b_subtree = Json::Tree();
    b_subtree["c_subtree"] = c_subtree;
    auto a_subtree = Json::Tree();
    a_subtree["b_subtree"] = b_subtree;
    auto expected = Json::Tree();
    expected["a_subtree"] = a_subtree;
    auto t = Document()
        .openDocument("a_subtree")
            .openDocument("b_subtree")
                .openDocument("c_subtree")
                    .append("a", std::string("some"))
                    .append("b", 12.3f)
                .closeDocument()
            .closeDocument()
        .closeDocument()
        .getTree();
    EXPECT_EQ(expected, t);
}

/* Implment Basic::Array first...
TEST_F(TestBuilderBasicDocument, openSubarrayFromFieldAndAddSomeElements)
{
    auto subtree = Json::Tree();
    subtree.pushBack(std::string("some"));
    subtree.pushBack(12.3f);
    subtree.pushBack(true);
    auto expected = Json::Tree();
    expected["subtree"] = subtree;
    auto t = Document()
        .openArray("subtree")
            .append(std::string("some"))
            .append(12.3f)
            .append(true)
        .closeArray()
        .getTree();
    EXPECT_EQ(expected, t);
}
*/
