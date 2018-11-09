#include <gmock/gmock.h>

#include <json/tree.hpp>

using namespace CodedProject;
using namespace ::testing;

class TestTreeConstruction : public ::testing::Test
{
};

TEST_F(TestTreeConstruction, defaultConstructAndGetSizeReturnsZero)
{
    auto t = Json::Tree();
    EXPECT_EQ(0, t.size());
}

TEST_F(TestTreeConstruction, defaultConstructAndCallIsValueReturnsFalse)
{
    auto t = Json::Tree();
    EXPECT_FALSE(t.isValue());
}

TEST_F(TestTreeConstruction, defaultConstructAndCallIsArrayReturnsFalse)
{
    auto t = Json::Tree();
    EXPECT_FALSE(t.isArray());
}

TEST_F(TestTreeConstruction, defaultConstructAndCallIsDocumentReturnsFalse)
{
    auto t = Json::Tree();
    EXPECT_FALSE(t.isDocument());
}

