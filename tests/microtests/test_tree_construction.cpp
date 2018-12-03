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

TEST_F(TestTreeConstruction, constructAsArrayTypeGivesCorrectType)
{
    auto t = Json::Tree(Json::Tree::Type::Array);
    EXPECT_TRUE(t.isArray());
    EXPECT_FALSE(t.isValue());
    EXPECT_FALSE(t.isDocument());
}

TEST_F(TestTreeConstruction, constructAsArrayTypeGivesSizeZero)
{
    auto t = Json::Tree(Json::Tree::Type::Array);
    EXPECT_EQ(0, t.size());
}

TEST_F(TestTreeConstruction, constructAsDocumentTypeGivesCorrectType)
{
    auto t = Json::Tree(Json::Tree::Type::Document);
    EXPECT_FALSE(t.isArray());
    EXPECT_FALSE(t.isValue());
    EXPECT_TRUE(t.isDocument());
}

TEST_F(TestTreeConstruction, constructAsDocumentTypeGivesSizeZero)
{
    auto t = Json::Tree(Json::Tree::Type::Document);
    EXPECT_EQ(0, t.size());
}

TEST_F(TestTreeConstruction, constructAsValueTypesGivesCorrectType)
{
    auto t = Json::Tree(Json::Tree::Type::Value);
    EXPECT_TRUE(t.isValue());
    EXPECT_FALSE(t.isArray());
    EXPECT_FALSE(t.isDocument());
}

TEST_F(TestTreeConstruction, constructAsValueTypeGivesSizeZero)
{
    auto t = Json::Tree(Json::Tree::Type::Value);
    EXPECT_EQ(0, t.size());
}

TEST_F(TestTreeConstruction, constructAsValueAndGetValueGiveNullValue)
{
    auto t = Json::Tree(Json::Tree::Type::Value);
    EXPECT_EQ(Json::Value(), t.getValue());
}

TEST_F(TestTreeConstruction, constructAsArrayAndGetValueThrowsWithHelpfulMessage)
{
    auto t = Json::Tree(Json::Tree::Type::Array);
    ASSERT_TRUE(t.isArray());

    EXPECT_THROW({
        try
        {
            t.getValue();
        }
        catch(std::exception & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("value"));
            EXPECT_THAT(err_msg, HasSubstr("getValue()"));
            EXPECT_THAT(err_msg, HasSubstr("array"));
            throw;
        }
    }, Json::Tree::IncorrectCallForType);
}

TEST_F(TestTreeConstruction, constructAsDocumentAndGetValueThrowsWithHelpfulMessage)
{
    auto t = Json::Tree(Json::Tree::Type::Document);
    ASSERT_TRUE(t.isDocument());

    EXPECT_THROW({
        try
        {
            t.getValue();
        }
        catch(std::exception & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("value"));
            EXPECT_THAT(err_msg, HasSubstr("getValue()"));
            EXPECT_THAT(err_msg, HasSubstr("document"));
            throw;
        }
    }, Json::Tree::IncorrectCallForType);
}

TEST_F(TestTreeConstruction, consturctAsDocumentAndGetValueAtArrayIndexThrowsError)
{
    auto t = Json::Tree(Json::Tree::Type::Document);
    EXPECT_THROW({
        try
        {
            auto a = t[0];
        }
        catch(std::exception & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("array"));
            EXPECT_THAT(err_msg, HasSubstr("operator[] (size_t)"));
            EXPECT_THAT(err_msg, HasSubstr("document"));
            throw;
        }
    }, Json::Tree::IncorrectCallForType);
}
