#include <gmock/gmock.h>

#include <json/builder.hpp>

using namespace CodedProject;
using Json::Builder;

class TestBuilder : public ::testing::Test
{
};

TEST_F(TestBuilder, constructEmptyTree)
{
    auto expected = Json::Tree();
    auto t = Builder().getTree();
    EXPECT_EQ(expected, t);
}

TEST_F(TestBuilder, appendFieldAndStringValueGivesExpectedDocument)
{
    auto expected = Json::Tree();
    expected["string"] = std::string("hello");
    auto t = Builder()
        .append("string", std::string("hello"))
        .getTree();
    EXPECT_EQ(expected, t);
}

TEST_F(TestBuilder, appendFieldAndIntegerValueGivesExpectedDocument)
{
    auto expected = Json::Tree();
    expected["integer"] = 123;
    auto t = Builder()
        .append("integer", 123)
        .getTree();
    EXPECT_EQ(expected, t);
}

TEST_F(TestBuilder, appendFieldAndFloatValueGivesExpectedDocument)
{
    auto expected = Json::Tree();
    expected["floating point"] = 12.3f;
    auto t = Builder()
        .append("floating point", 12.3f)
        .getTree();
    EXPECT_EQ(expected, t);
}

TEST_F(TestBuilder, appendFieldAndBoolValueGivesExpectedDocument)
{
    auto expected = Json::Tree();
    expected["boolean"] = true;
    auto t = Builder()
        .append("boolean", true)
        .getTree();
    EXPECT_EQ(expected, t);
}

TEST_F(TestBuilder, appendFieldAndDocumentSubtreeValueGivesExpectedDocument)
{
    auto subtree = Json::Tree();
    subtree["a"] = std::string("some");
    subtree["b"] = 12.3f;
    auto expected = Json::Tree();
    expected["subtree"] = subtree;
    auto t = Builder()
        .append("subtree", subtree)
        .getTree();
    EXPECT_EQ(expected, t);
}

TEST_F(TestBuilder, appendFieldAndSubarrayGivesExpectedDocument)
{
    auto subarray = Json::Tree();
    subarray.pushBack(true);
    subarray.pushBack(123);
    auto expected = Json::Tree();
    expected["some_field"] = subarray;
    auto t = Builder()
        .append("some_field", subarray)
        .getTree();
    EXPECT_EQ(expected, t);
}

TEST_F(TestBuilder, pushBackSingleIntegerValueGivesExpectedArray)
{
    auto expected = Json::Tree();
    expected.pushBack(123);
    auto t = Builder()
        .pushBack(123)
        .getTree();
    EXPECT_EQ(expected, t);
}

TEST_F(TestBuilder, pushBackSingleStringValueGivesExpectedArray)
{
    auto expected = Json::Tree();
    expected.pushBack(std::string("world"));
    auto t = Builder()
        .pushBack(std::string("world"))
        .getTree();
    EXPECT_EQ(expected, t);
}

TEST_F(TestBuilder, pushBackSingleFloatValueGivesExpectedArray)
{
    auto expected = Json::Tree();
    expected.pushBack(12.5f);
    auto t = Builder()
        .pushBack(12.5f)
        .getTree();
    EXPECT_EQ(expected, t);
}

TEST_F(TestBuilder, pushBackSingleBoolValueGivesExpectedArray)
{
    auto expected = Json::Tree();
    expected.pushBack(true);
    auto t = Builder()
        .pushBack(true)
        .getTree();
    EXPECT_EQ(expected, t);
}

TEST_F(TestBuilder, pushBackSubarrayGivesExpectedArray)
{
    auto subarray = Json::Tree();
    subarray.pushBack(true);
    subarray.pushBack(123);
    auto expected = Json::Tree();
    expected.pushBack(subarray);
    auto t = Builder()
        .pushBack(subarray)
        .getTree();
    EXPECT_EQ(expected, t);
}

TEST_F(TestBuilder, pushBackSubDocumentGivesExpectedArray)
{
    auto subtree = Json::Tree();
    subtree["a"] = std::string("some");
    subtree["b"] = 12.3f;
    auto expected = Json::Tree();
    expected.pushBack(subtree);
    auto t = Builder()
        .pushBack(subtree)
        .getTree();
    EXPECT_EQ(expected, t);
}

TEST_F(TestBuilder, appendMutipleFieldsOfDifferentTypesGivesExpectedDocument)
{
    auto expected = Json::Tree();
    expected["boolean"] = true;
    expected["string"] = std::string("hello");
    expected["integer"] = 123;
    expected["floating point"] = 12.3f;
    expected["other_boolean"] = false;
    auto t = Builder()
        .append("boolean", true)
        .append("string", std::string("hello"))
        .append("integer", 123)
        .append("floating point", 12.3f)
        .append("other_boolean", false)
        .getTree();
    EXPECT_EQ(expected, t);
}

TEST_F(TestBuilder, pushBackMultipleValuesOfDifferentTypesGiveExpectedArray)
{
    auto expected = Json::Tree();
    expected.pushBack(true);
    expected.pushBack(123);
    expected.pushBack(std::string("world"));
    expected.pushBack(12.5f);
    auto t = Builder()
        .pushBack(true)
        .pushBack(123)
        .pushBack(std::string("world"))
        .pushBack(12.5f)
        .getTree();
    EXPECT_EQ(expected, t);
}

TEST_F(TestBuilder, openSubArrayAndAddMultipleFieldsGiveExpectedArray)
{
    auto subarray = Json::Tree();
    subarray.pushBack(true);
    subarray.pushBack(123);
    subarray.pushBack(std::string("hello"));
    auto expected = Json::Tree();
    expected.pushBack(subarray);
    auto t = Builder()
        .openArray()
            .pushBack(true)
            .pushBack(123)
            .pushBack(std::string("hello"))
        .closeArray()
        .getTree();
    EXPECT_EQ(expected, t);
}

TEST_F(TestBuilder, openSubdocumentForFieldAndAddSomeElementsGivesExpectedDocument)
{
    auto subtree = Json::Tree();
    subtree["a"] = std::string("some");
    subtree["b"] = 12.3f;
    auto expected = Json::Tree();
    expected["subtree"] = subtree;
    auto t = Builder()
        .openDocument("subtree")
            .append("a", std::string("some"))
            .append("b", 12.3f)
        .closeDocument()
        .getTree();
    EXPECT_EQ(expected, t);
}

TEST_F(TestBuilder, openMultipleSubdocumentsForFieldAndAddSomeElementsGivesExpectedDocument)
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
    auto t = Builder()
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

