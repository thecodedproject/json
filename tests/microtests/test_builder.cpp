#include <gmock/gmock.h>

#include <json/builder.hpp>

using namespace CodedProject;

class TestBuilder : public ::testing::Test
{
};

TEST_F(TestBuilder, constructEmptyTree)
{
    auto expected = Json::Tree();
    auto t = Json::Builder().getTree();
    EXPECT_EQ(expected, t);
}

TEST_F(TestBuilder, appendFieldAndStringValue)
{
    auto expected = Json::Tree();
    expected["a"] = std::string("hello");
    auto t = Json::Builder().getTree()
}
