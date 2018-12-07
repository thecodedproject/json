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

TEST_F(TestBuilder, openAndCloseSubtreeInArrayGivesUninitalisedTreeInArray)
{
    using namespace CodedProject::Json;
    auto expected = Tree();
    expected.pushBack(Tree(Tree::Type::Uninitialised));
    auto t = Builder()
        .openSubtree()
        .closeSubtree()
    .getTree();
    EXPECT_EQ(expected, t);
}

TEST_F(TestBuilder, openAndCloseSubtreeInDocumentGivesUninitalisedTreeInDocument)
{
    using namespace CodedProject::Json;
    auto expected = Tree();
    expected["u"] = Tree(Tree::Type::Uninitialised);
    auto t = Builder()
        .openSubtree("u")
        .closeSubtree()
    .getTree();
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

TEST_F(TestBuilder, pushBackMultipleValuesOfDifferentTypesGivesExpectedArray)
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

TEST_F(TestBuilder, openSubtreeInArrayAndPushBackMultipleFieldsGivesExpectedArrayInArray)
{
    auto subarray = Json::Tree();
    subarray.pushBack(true);
    subarray.pushBack(123);
    subarray.pushBack(std::string("hello"));
    auto expected = Json::Tree();
    expected.pushBack(subarray);
    auto t = Builder()
        .openSubtree()
            .pushBack(true)
            .pushBack(123)
            .pushBack(std::string("hello"))
        .closeSubtree()
        .getTree();
    EXPECT_EQ(expected, t);
}

TEST_F(TestBuilder, openSubtreeInArrayAndAppendMultipleFieldsGivesExpectedDocumentInArray)
{
    auto subdoc = Json::Tree();
    subdoc["a"] = true;
    subdoc["b"] = 123;
    subdoc["c"] = std::string("hello");
    auto expected = Json::Tree();
    expected.pushBack(subdoc);
    auto t = Builder()
        .openSubtree()
            .append("a", true)
            .append("b", 123)
            .append("c", std::string("hello"))
        .closeSubtree()
        .getTree();
    EXPECT_EQ(expected, t);
}

TEST_F(TestBuilder, openMultipleSubTreesAndPushBackMultipleFieldsGivesExpectedArray)
{
    auto subarray1 = Json::Tree();
    subarray1.pushBack(true);
    subarray1.pushBack(123);
    subarray1.pushBack(std::string("hello"));

    auto subarray2 = Json::Tree();
    subarray2.pushBack(subarray1);
    subarray2.pushBack(2);

    auto subarray3 = Json::Tree();
    subarray3.pushBack(true);
    subarray3.pushBack(subarray2);

    auto subarray4 = Json::Tree();
    subarray4.pushBack(std::string("four"));
    subarray4.pushBack(subarray3);

    auto expected = Json::Tree();
    expected.pushBack(subarray4);
    expected.pushBack(std::string("top"));
    auto t = Builder()
        .openSubtree()
            .pushBack(std::string("four"))
            .openSubtree()
                .pushBack(true)
                .openSubtree()
                    .openSubtree()
                        .pushBack(true)
                        .pushBack(123)
                        .pushBack(std::string("hello"))
                    .closeSubtree()
                    .pushBack(2)
                .closeSubtree()
            .closeSubtree()
        .closeSubtree()
        .pushBack(std::string("top"))
        .getTree();
    EXPECT_EQ(expected, t);
}

TEST_F(TestBuilder,
    openSubtreeForFieldAndPushBackSomeElementsGivesExpectedSubDocumentInDocument)
{
    auto subtree = Json::Tree();
    subtree["a"] = std::string("some");
    subtree["b"] = 12.3f;
    auto expected = Json::Tree();
    expected["subtree"] = subtree;
    auto t = Builder()
        .openSubtree("subtree")
            .append("a", std::string("some"))
            .append("b", 12.3f)
        .closeSubtree()
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
        .openSubtree("a_subtree")
            .openSubtree("b_subtree")
                .openSubtree("c_subtree")
                    .append("a", std::string("some"))
                    .append("b", 12.3f)
                .closeSubtree()
            .closeSubtree()
        .closeSubtree()
        .getTree();
    EXPECT_EQ(expected, t);
}

TEST_F(TestBuilder, addSubarraysToDocumentGivesExpectedDocument)
{
    auto a1 = Json::Tree();
    a1.pushBack(1);
    a1.pushBack(2);

    auto a2 = Json::Tree();
    a2.pushBack(3.0f);
    a2.pushBack(5.0f);

    auto a3 = Json::Tree();
    a3.pushBack(true);
    a3.pushBack(false);
    a3.pushBack(std::string("six"));

    auto a4 = Json::Tree();
    a4.pushBack(std::string("seven"));
    a4.pushBack(8);

    auto expected = Json::Tree();
    expected["a1"] = a1;
    expected["a2"] = a2;
    expected["a3"] = a3;
    expected["a4"] = a4;

    auto t = Builder()
        .openSubtree("a1")
            .pushBack(1)
            .pushBack(2)
        .closeSubtree()
        .openSubtree("a2")
            .pushBack(3.0f)
            .pushBack(5.0f)
        .closeSubtree()
        .openSubtree("a3")
            .pushBack(true)
            .pushBack(false)
            .pushBack(std::string("six"))
        .closeSubtree()
        .openSubtree("a4")
            .pushBack(std::string("seven"))
            .pushBack(8)
        .closeSubtree()
        .getTree();
    EXPECT_EQ(expected, t);
}

TEST_F(TestBuilder, addSubdocumentsToArrayGiveExpectedArray)
{
    auto d1 = Json::Tree();
    d1["a"] = 1;
    d1["b"] = true;

    auto d2 = Json::Tree();
    d2["a"] = std::string("hello");
    d2["c"] = 123.5f;

    auto d3 = Json::Tree();
    d3["d"] = false;
    d3["e"] = std::string("world");

    auto expected = Json::Tree();
    expected.pushBack(d1);
    expected.pushBack(d2);
    expected.pushBack(d3);

    auto t = Builder()
        .openSubtree()
            .append("a", 1)
            .append("b", true)
        .closeSubtree()
        .openSubtree()
            .append("a", std::string("hello"))
            .append("c", 123.5f)
        .closeSubtree()
        .openSubtree()
            .append("d", false)
            .append("e", std::string("world"))
        .closeSubtree()
        .getTree();
    EXPECT_EQ(expected, t);
}

TEST_F(TestBuilder, addNestedSubArraysAndSubDocumentsToDocumentGivesExpectedDocument)
{
    auto a1 = Json::Tree();
    a1.pushBack(1);
    a1.pushBack(2);

    auto d1 = Json::Tree();
    d1["a"] = 1;
    d1["b"] = a1;

    auto d2 = Json::Tree();
    d2["a"] = std::string("hello");
    d2["c"] = 123.5f;

    auto a2 = Json::Tree();
    a2.pushBack(3.0f);
    a2.pushBack(5.0f);
    a2.pushBack(d2);

    auto d3 = Json::Tree();
    d3["d"] = a2;
    d3["e"] = std::string("world");

    auto a3 = Json::Tree();
    a3.pushBack(true);
    a3.pushBack(false);
    a3.pushBack(std::string("six"));

    auto expected = Json::Tree();
    expected["val"] = 123;
    expected["d1"] = d1;
    expected["d3"] = d3;
    expected["a3"] = a3;

    auto t = Builder()
        .append("val", 123)
        .openSubtree("d1")
            .append("a", 1)
            .openSubtree("b")
                .pushBack(1)
                .pushBack(2)
            .closeSubtree()
        .closeSubtree()
        .openSubtree("d3")
            .openSubtree("d")
                .pushBack(3.0f)
                .pushBack(5.0f)
                .openSubtree()
                    .append("a", std::string("hello"))
                    .append("c", 123.5f)
                .closeSubtree()
            .closeSubtree()
            .append("e", std::string("world"))
        .closeSubtree()
        .openSubtree("a3")
            .pushBack(true)
            .pushBack(false)
            .pushBack(std::string("six"))
        .closeSubtree()
        .getTree();
    EXPECT_EQ(expected, t);
}
