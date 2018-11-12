#include <gmock/gmock.h>

#include <json/builder/basic/array.hpp>

using namespace CodedProject;
using Json::Builder::Basic::Array;

class TestBuilderBasicArray : public ::testing::Test
{
};

TEST_F(TestBuilderBasicArray, constructEmptyTree)
{
    auto expected = Json::Tree();
    auto t = Array().getTree();
    EXPECT_EQ(expected, t);
}

TEST_F(TestBuilderBasicArray, appendSingleIntegerValue)
{
    auto expected = Json::Tree();
    expected.pushBack(123);
    auto t = Array()
        .append(123)
        .getTree();
    EXPECT_EQ(expected, t);
}

TEST_F(TestBuilderBasicArray, appendSingleStringValue)
{
    auto expected = Json::Tree();
    expected.pushBack(std::string("world"));
    auto t = Array()
        .append(std::string("world"))
        .getTree();
    EXPECT_EQ(expected, t);
}

TEST_F(TestBuilderBasicArray, appendSingleFloatValue)
{
    auto expected = Json::Tree();
    expected.pushBack(12.5f);
    auto t = Array()
        .append(12.5f)
        .getTree();
    EXPECT_EQ(expected, t);
}

TEST_F(TestBuilderBasicArray, appendSingleBoolValue)
{
    auto expected = Json::Tree();
    expected.pushBack(true);
    auto t = Array()
        .append(true)
        .getTree();
    EXPECT_EQ(expected, t);
}

TEST_F(TestBuilderBasicArray, appendSubarray)
{
    auto subarray = Json::Tree();
    subarray.pushBack(true);
    subarray.pushBack(123);
    auto expected = Json::Tree();
    expected.pushBack(subarray);
    auto t = Array()
        .append(subarray)
        .getTree();
    EXPECT_EQ(expected, t);
}

TEST_F(TestBuilderBasicArray, appendSubDocument)
{
    auto subtree = Json::Tree();
    subtree["a"] = std::string("some");
    subtree["b"] = 12.3f;
    auto expected = Json::Tree();
    expected.pushBack(subtree);
    auto t = Array()
        .append(subtree)
        .getTree();
    EXPECT_EQ(expected, t);
}

TEST_F(TestBuilderBasicArray, appendMultipleValuesOfDifferentTypes)
{
    auto expected = Json::Tree();
    expected.pushBack(true);
    expected.pushBack(123);
    expected.pushBack(std::string("world"));
    expected.pushBack(12.5f);
    auto t = Array()
        .append(true)
        .append(123)
        .append(std::string("world"))
        .append(12.5f)
        .getTree();
    EXPECT_EQ(expected, t);
}

TEST_F(TestBuilderBasicArray, openSubArrayAndAddMultipleFields)
{
    auto subarray = Json::Tree();
    subarray.pushBack(true);
    subarray.pushBack(123);
    subarray.pushBack(std::string("hello"));
    auto expected = Json::Tree();
    expected.pushBack(subarray);
    auto t = Array()
        .openArray()
            .append(true)
            .append(123)
            .append(std::string("hello"))
        .closeArray()
        .getTree();
    EXPECT_EQ(expected, t);
}
