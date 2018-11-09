#include <gmock/gmock.h>

#include <json/tree.hpp>

using namespace CodedProject;
using namespace ::testing;

class TestTreeValueUsage : public ::testing::Test
{
};

TEST_F(TestTreeValueUsage, constructValueAndGetSizeReturnsZero)
{
    auto t = Json::Tree(12);
    EXPECT_EQ(0, t.size());
}

TEST_F(TestTreeValueUsage, consturctFromValueAndCallIsValueReturnsTrue)
{
    auto t = Json::Tree(Json::Value(23.0f));
    EXPECT_TRUE(t.isValue());
}

TEST_F(TestTreeValueUsage, consturctFromStringAndGetValueAsString)
{
    auto t = Json::Tree(std::string("something"));
    EXPECT_EQ("something", t.get<std::string>());
}

TEST_F(TestTreeValueUsage, consturctFromFloatAndGetValueAsFloat)
{
    auto t = Json::Tree(10.5f);
    EXPECT_FLOAT_EQ(10.5f, t.get<float>());
}

TEST_F(TestTreeValueUsage, constructFromIntandGetAsInt)
{
    auto t = Json::Tree(12);
    EXPECT_EQ(12, t.get<int>());
}

TEST_F(TestTreeValueUsage, constructFromBoolAndGetBool)
{
    auto t = Json::Tree(true);
    EXPECT_TRUE(t.get<bool>());
}

TEST_F(TestTreeValueUsage, consturctFromValueAndCallIsArrayReturnsFalse)
{
    auto t = Json::Tree(Json::Value(23.0f));
    EXPECT_FALSE(t.isArray());
}

TEST_F(TestTreeValueUsage, consturctFromValueAndCallIsDocumentReturnsFalse)
{
    auto t = Json::Tree(Json::Value(23.0f));
    EXPECT_FALSE(t.isDocument());
}

TEST_F(TestTreeValueUsage, consturctFromValueAndGetValue)
{
    auto v = Json::Value(23.0f);
    auto t = Json::Tree(v);
    EXPECT_EQ(v, t.getValue());
}
