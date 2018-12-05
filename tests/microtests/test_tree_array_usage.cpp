#include <gmock/gmock.h>

#include <json/tree.hpp>

using namespace CodedProject;
using namespace ::testing;

class TestTreeArrayUsage : public ::testing::Test
{
};

TEST_F(TestTreeArrayUsage, pushBackStringIntoArrayAndGetValueWithArrayIndexReturnsSameValue)
{
    auto t = Json::Tree();
    t.pushBack(std::string("some_value"));
    EXPECT_EQ("some_value", t[0].get<std::string>());
}

TEST_F(TestTreeArrayUsage, defaultConstructAndPushBackElementMakesIsArrayReturnTrue)
{
    auto t = Json::Tree();
    t.pushBack(std::string("some_value"));
    EXPECT_TRUE(t.isArray());
}

TEST_F(TestTreeArrayUsage, pushBackSeveralValuesIntoArrayAndGetWithArrayIndexReturnsSameValue)
{
    auto t = Json::Tree();
    t.pushBack(false);
    t.pushBack(std::string("some_value"));
    t.pushBack(43);
    t.pushBack(23.5f);
    EXPECT_EQ(false, t[0].get<bool>());
    EXPECT_EQ("some_value", t[1].get<std::string>());
    EXPECT_EQ(43, t[2].get<int>());
    EXPECT_FLOAT_EQ(23.5f, t[3].get<float>());
}

TEST_F(TestTreeArrayUsage, tryToAccessArrayIndexOnEmptyTreeThrowsHelpfulError)
{
    auto t = Json::Tree();

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
            EXPECT_THAT(err_msg, HasSubstr("uninitialised"));
            throw;
        }
    }, Json::Tree::IncorrectCallForType);
}

TEST_F(TestTreeArrayUsage, pushBackSeveralValuesIntoArrayAndGetSize)
{
    auto subtree_1 = Json::Tree();
    subtree_1["some_int_field"] = 14;
    subtree_1["some_string_field"] = std::string("hello world");
    auto subtree_2 = Json::Tree();
    subtree_2["some_bool_field"] = true;
    subtree_2["some_float_field"] = 13.5f;

    auto t = Json::Tree();
    t.pushBack(subtree_1);
    t.pushBack(43);
    t.pushBack(subtree_2);

    EXPECT_EQ(14, t[0]["some_int_field"].get<int>());
    EXPECT_EQ("hello world", t[0]["some_string_field"].get<std::string>());
    EXPECT_EQ(43, t[1].get<int>());
    EXPECT_FLOAT_EQ(13.5f, t[2]["some_float_field"].get<float>());
    EXPECT_EQ(true, t[2]["some_bool_field"].get<bool>());
}

TEST_F(TestTreeArrayUsage, pushBackSeveralValuesIncludingSubtreesIntoArrayAndGetSize)
{
    auto t = Json::Tree();
    t.pushBack(false);
    t.pushBack(std::string("some_value"));
    t.pushBack(43);
    t.pushBack(23.5f);
    EXPECT_EQ(4, t.size());
}

TEST_F(TestTreeArrayUsage, constructFromValueAndTryToGetArrayElementThrowsErrorWithHelpfulMessage)
{
    auto t = Json::Tree(23.1f);
    EXPECT_THROW({
        try
        {
            t[0] = 10;
        }
        catch(std::exception & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("array"));
            EXPECT_THAT(err_msg, HasSubstr("operator[] (size_t)"));
            EXPECT_THAT(err_msg, HasSubstr("value"));
            throw;
        }
    }, Json::Tree::IncorrectCallForType);
}

TEST_F(TestTreeArrayUsage, constructDocumentAndTryToGetArrayElementThrowsErrorWithHelpfulMessage)
{
    auto t = Json::Tree();
    t["some_field"] = 10;
    ASSERT_TRUE(t.isDocument());
    EXPECT_THROW({
        try
        {
            t[0] = 10;
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

TEST_F(TestTreeArrayUsage, assignUsingAccessOperatorAndGetValueGivesCorrectValue)
{
    auto t = Json::Tree();
    t.pushBack(std::string("some_value"));
    t[0] = 123;
    EXPECT_EQ(123, t[0].get<int>());
}

TEST_F(TestTreeArrayUsage, pushBackStringIntoArrayAndGetValueWithAtReturnsSameValue)
{
    auto t = Json::Tree();
    t.pushBack(std::string("some_value"));
    EXPECT_EQ("some_value", t.at(0).get<std::string>());
}

TEST_F(TestTreeArrayUsage, getMultipleValuesWithAtAccessorReturnsCorrectValues)
{
    auto t = Json::Tree();
    t.pushBack(std::string("some_value"));
    t.pushBack(true);
    t.pushBack(234);
    t.pushBack(23.5f);
    EXPECT_EQ("some_value", t.at(0).get<std::string>());
    EXPECT_TRUE(t.at(1).get<bool>());
    EXPECT_EQ(234, t.at(2).get<int>());
    EXPECT_FLOAT_EQ(23.5f, t.at(3).get<float>());
}

TEST_F(TestTreeArrayUsage, assignUsingAtAccessorAndGetValuesReturnsCorrectValue)
{
    auto t = Json::Tree();
    t.pushBack(std::string("some_value"));
    t.at(0) = 345;
    EXPECT_EQ(345, t.at(0).get<int>());
}

TEST_F(TestTreeArrayUsage, getUsingAtAccessorOnConstTreeReturnsCorrectValue)
{
    auto t = Json::Tree();
    t.pushBack(345);
    auto const& t_const = t;
    EXPECT_EQ(345, t_const.at(0).get<int>());
}

TEST_F(TestTreeArrayUsage, constructDocumentAndTryToGetArrayElementWithAtThrowsErrorWithHelpfulMessage)
{
    auto t = Json::Tree();
    t["some_field"] = 10;
    ASSERT_TRUE(t.isDocument());
    EXPECT_THROW({
        try
        {
            auto a = t.at(0);
        }
        catch(std::exception & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("array"));
            EXPECT_THAT(err_msg, HasSubstr("document"));
            throw;
        }
    }, Json::Tree::IncorrectCallForType);
}

TEST_F(TestTreeArrayUsage, createDocumentAndAccessValueWithAtAccessor)
{
    auto t = Json::Tree();
    t["some_field"] = std::string("some_value");
    EXPECT_EQ("some_value", t.at("some_field").get<std::string>());
}

TEST_F(TestTreeArrayUsage, createDocumentAndAccessManyValuesWithAtAccessor)
{
    auto t = Json::Tree();
    t["a"] = std::string("some_value");
    t["b"] = 23;
    t["c"] = false;
    t["d"] = 34.5f;

    EXPECT_EQ("some_value", t.at("a").get<std::string>());
    EXPECT_EQ(23, t.at("b").get<int>());
    EXPECT_FALSE(t.at("c").get<bool>());
    EXPECT_FLOAT_EQ(34.5f, t.at("d").get<float>());
}

TEST_F(TestTreeArrayUsage, createConstDocumentAndAccessValueWithAtAccessor)
{
    auto t = Json::Tree();
    t["some_field"] = std::string("some_value");
    auto const& t_const = t;
    EXPECT_EQ("some_value", t_const.at("some_field").get<std::string>());
}
