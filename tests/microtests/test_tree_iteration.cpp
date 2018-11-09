#include <gmock/gmock.h>

#include <json/tree.hpp>

using namespace CodedProject;
using namespace ::testing;

class TestTreeIteration : public ::testing::Test
{
};

TEST_F(TestTreeIteration, iterateOverDocumentOfValuesGetCorrectFieldsAndValuesAsPairs)
{
    auto t = Json::Tree();
    t["first_field"] = 10;
    t["second_field"] = true;
    t["thrid_field"] = std::string("hello");

    auto it = std::begin(t);

    EXPECT_EQ("first_field", it->first);
    EXPECT_EQ(10, it->second.get<int>());
    ++it;
    EXPECT_EQ("second_field", it->first);
    EXPECT_TRUE(it->second.get<bool>());
    ++it;
    EXPECT_EQ("thrid_field", it->first);
    EXPECT_EQ("hello", it->second.get<std::string>());
    ++it;
    EXPECT_TRUE(it == std::end(t));
}

TEST_F(TestTreeIteration, iterateOverConstDocumentOfValuesGetCorrectFieldsAndValuesAsPairs)
{
    auto t = Json::Tree();
    t["first_field"] = 10;
    t["second_field"] = true;
    t["thrid_field"] = std::string("hello");

    auto const t_const = t;

    auto it = std::begin(t_const);

    EXPECT_EQ("first_field", it->first);
    EXPECT_EQ(10, it->second.get<int>());
    ++it;
    EXPECT_EQ("second_field", it->first);
    EXPECT_TRUE(it->second.get<bool>());
    ++it;
    EXPECT_EQ("thrid_field", it->first);
    EXPECT_EQ("hello", it->second.get<std::string>());
    ++it;
    EXPECT_TRUE(it == std::end(t_const));
}

TEST_F(TestTreeIteration,
    iterateOverDocumentOfValuesWithConstIteratorsAndGetCorrectFieldsAndValuesAsPairs)
{
    auto t = Json::Tree();
    t["first_field"] = 10;
    t["second_field"] = true;
    t["thrid_field"] = std::string("hello");

    auto it = std::cbegin(t);

    EXPECT_EQ("first_field", it->first);
    EXPECT_EQ(10, it->second.get<int>());
    ++it;
    EXPECT_EQ("second_field", it->first);
    EXPECT_TRUE(it->second.get<bool>());
    ++it;
    EXPECT_EQ("thrid_field", it->first);
    EXPECT_EQ("hello", it->second.get<std::string>());
    ++it;
    EXPECT_TRUE(it == std::cend(t));
}

TEST_F(TestTreeIteration, iterateOverArrayGivesaCorrectValuesInOrderWithEmptyStringsForKeys)
{
    auto t = Json::Tree();
    t.pushBack(10);
    t.pushBack(false);
    t.pushBack(std::string("hello"));

    ASSERT_TRUE(t.isArray());
    ASSERT_EQ(3, t.size());

    auto it = std::begin(t);

    EXPECT_TRUE(it->first.empty());
    EXPECT_EQ(10, it->second.get<int>());
    ++it;
    EXPECT_TRUE(it->first.empty());
    EXPECT_FALSE(it->second.get<bool>());
    ++it;
    EXPECT_TRUE(it->first.empty());
    EXPECT_EQ("hello", it->second.get<std::string>());
    ++it;
    EXPECT_TRUE(it == std::end(t));
}

TEST_F(TestTreeIteration, iterateOverConstArrayGivesaCorrectValuesInOrderWithEmptyStringsForKeys)
{
    auto t = Json::Tree();
    t.pushBack(10);
    t.pushBack(false);
    t.pushBack(std::string("hello"));

    auto const t_const = t;

    ASSERT_TRUE(t_const.isArray());
    ASSERT_EQ(3, t_const.size());

    auto it = std::begin(t_const);

    EXPECT_TRUE(it->first.empty());
    EXPECT_EQ(10, it->second.get<int>());
    ++it;
    EXPECT_TRUE(it->first.empty());
    EXPECT_FALSE(it->second.get<bool>());
    ++it;
    EXPECT_TRUE(it->first.empty());
    EXPECT_EQ("hello", it->second.get<std::string>());
    ++it;
    EXPECT_TRUE(it == std::end(t_const));
}

TEST_F(TestTreeIteration,
    iterateOverArrayWithConstIteratorsGivesaCorrectValuesInOrderWithEmptyStringsForKeys)
{
    auto t = Json::Tree();
    t.pushBack(10);
    t.pushBack(false);
    t.pushBack(std::string("hello"));

    auto const t_const = t;

    ASSERT_TRUE(t_const.isArray());
    ASSERT_EQ(3, t_const.size());

    auto it = std::cbegin(t_const);

    EXPECT_TRUE(it->first.empty());
    EXPECT_EQ(10, it->second.get<int>());
    ++it;
    EXPECT_TRUE(it->first.empty());
    EXPECT_FALSE(it->second.get<bool>());
    ++it;
    EXPECT_TRUE(it->first.empty());
    EXPECT_EQ("hello", it->second.get<std::string>());
    ++it;
    EXPECT_TRUE(it == std::cend(t_const));
}

TEST_F(TestTreeIteration, callingBeginOnValueGivesEndIterator)
{
    auto t = Json::Tree("some_value");

    ASSERT_TRUE(t.isValue());

    auto it = std::begin(t);
    EXPECT_TRUE(it == std::end(t));
}

