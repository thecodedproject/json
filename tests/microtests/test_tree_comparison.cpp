#include <gmock/gmock.h>

#include <json/tree.hpp>

using namespace CodedProject;
using namespace ::testing;

class TestTreeComparison : public ::testing::Test
{
protected:
    void expectComparesEqual(Json::Tree const& t, Json::Tree const& u)
    {
        EXPECT_TRUE(t == u);
        EXPECT_FALSE(t != u);
    }

    void expectComparesNotEqual(Json::Tree const& t, Json::Tree const& u)
    {
        EXPECT_FALSE(t == u);
        EXPECT_TRUE(t != u);
    }
};

TEST_F(TestTreeComparison, defaultConstructedTreesCompareEqual)
{
    auto t = Json::Tree();
    auto u = Json::Tree();
    expectComparesEqual(t, u);
}

TEST_F(TestTreeComparison, valueTreesWithTheSameValueCompareEqual)
{
    auto t = Json::Tree(10);
    auto u = Json::Tree(10);
    expectComparesEqual(t, u);
}

TEST_F(TestTreeComparison, valueTreesWithDifferentValuesOfSameTypeCompareNotEqual)
{
    auto t = Json::Tree(10);
    auto u = Json::Tree(100);
    expectComparesNotEqual(t, u);
}

TEST_F(TestTreeComparison, valueTreesWithDifferentValuesOfDifferentTypesCompareNotEqual)
{
    auto t = Json::Tree(10);
    auto u = Json::Tree(false);
    expectComparesNotEqual(t, u);
}

TEST_F(TestTreeComparison, documentsWithSameSingleFieldAndValueCompareEqual)
{
    auto t = Json::Tree();
    t["a"] = std::string("hello");
    auto u = Json::Tree();
    u["a"] = std::string("hello");
    expectComparesEqual(t, u);
}

TEST_F(TestTreeComparison, documentsWithSameSingleFieldButDifferentValueOfSameTypeCompareNotEqual)
{
    auto t = Json::Tree();
    t["a"] = std::string("hello");
    auto u = Json::Tree();
    u["a"] = std::string("world");
    expectComparesNotEqual(t, u);
}

TEST_F(TestTreeComparison, documentsWithDifferentSingleFieldsOfSameTypeCompareNotEqual)
{
    auto t = Json::Tree();
    t["a"] = std::string("hello");
    auto u = Json::Tree();
    u["b"] = std::string("hello");
    expectComparesNotEqual(t, u);
}

TEST_F(TestTreeComparison, documentsWithSameSingleFieldAndDifferentValueTypesCompareNotEqual)
{
    auto t = Json::Tree();
    t["a"] = std::string("hello");
    auto u = Json::Tree();
    u["a"] = 10.0f;
    expectComparesNotEqual(t, u);
}

TEST_F(TestTreeComparison, documentsWithDifferentSizesCompareNotEqual)
{
    auto t = Json::Tree();
    t["a"] = std::string("hello");
    auto u = Json::Tree();
    t["a"] = std::string("hello");
    u["b"] = std::string("world");
    expectComparesNotEqual(t, u);
}

TEST_F(TestTreeComparison, documentsWithSameFieldsAndValuesWithMultipleTypesCompareEqual)
{
    auto t = Json::Tree();
    t["a"] = std::string("hello");
    t["b"] = false;
    t["c"] = 100;
    auto u = Json::Tree();
    u["a"] = std::string("hello");
    u["b"] = false;
    u["c"] = 100;
    expectComparesEqual(t, u);
}

TEST_F(TestTreeComparison, documentsWithSameMultipleFieldsAndOneDifferentValueComparesNotEqual)
{
    auto t = Json::Tree();
    t["a"] = std::string("hello");
    t["b"] = false;
    t["c"] = 100;
    auto u = Json::Tree();
    u["a"] = std::string("hello");
    u["b"] = false;
    u["c"] = 101;
    expectComparesNotEqual(t, u);
}

TEST_F(TestTreeComparison, documentsWithSameMultipleFieldsAnDifferentValueTypesComparesNotEqual)
{
    auto t = Json::Tree();
    t["a"] = 10.0f;
    t["b"] = std::string("a");
    t["c"] = true;
    auto u = Json::Tree();
    u["a"] = std::string("hello");
    u["b"] = false;
    u["c"] = 101;
    expectComparesNotEqual(t, u);
}

TEST_F(TestTreeComparison, documentsWithSameMultipleFieldsAndSubtreesCompareEqual)
{
    auto t_subdoc = Json::Tree();
    t_subdoc["a"] = 10;
    t_subdoc["b"] = std::string("word");
    auto t_subarray = Json::Tree();
    t_subarray.pushBack(true);
    t_subarray.pushBack(22);
    auto t = Json::Tree();
    t["a"] = std::string("hello");
    t["b"] = false;
    t["c"] = t_subarray;
    t["d"] = t_subdoc;
    t["e"] = 123;
    auto u_subdoc = Json::Tree();
    u_subdoc["a"] = 10;
    u_subdoc["b"] = std::string("word");
    auto u_subarray = Json::Tree();
    u_subarray.pushBack(true);
    u_subarray.pushBack(22);
    auto u = Json::Tree();
    u["a"] = std::string("hello");
    u["b"] = false;
    u["c"] = u_subarray;
    u["d"] = u_subdoc;
    u["e"] = 123;
    expectComparesEqual(t, u);
}

TEST_F(TestTreeComparison, createIdenticalDocumentsThenEraseSameFieldComparesEqual)
{
    auto t = Json::Tree();
    t["a"] = std::string("hello");
    t["b"] = false;
    t["c"] = 101;
    auto u = Json::Tree();
    u["a"] = std::string("hello");
    u["b"] = false;
    u["c"] = 101;

    t.erase("b");
    u.erase("b");

    expectComparesEqual(t, u);
}

TEST_F(TestTreeComparison, createIdenticalDocumentsThenEraseSameFieldAndInsertAnotherComparesEqual)
{
    auto t = Json::Tree();
    t["a"] = std::string("hello");
    t["b"] = false;
    t["c"] = 101;
    auto u = Json::Tree();
    u["a"] = std::string("hello");
    u["b"] = false;
    u["c"] = 101;

    t.erase("b");
    u.erase("b");

    t["d"] = 123;
    u["d"] = 123;

    expectComparesEqual(t, u);
}

TEST_F(TestTreeComparison, arraysWithSameSingleElementCompareEqual)
{
    auto t = Json::Tree();
    t.pushBack(std::string("hello"));
    auto u = Json::Tree();
    u.pushBack(std::string("hello"));
    expectComparesEqual(t, u);
}

TEST_F(TestTreeComparison, arraysWithDifferentSingleElementCompareNotEqual)
{
    auto t = Json::Tree();
    t.pushBack(std::string("hello"));
    auto u = Json::Tree();
    u.pushBack(std::string("world"));
    expectComparesNotEqual(t, u);
}

TEST_F(TestTreeComparison, arraysWithSameMultipleElementsCompareEqual)
{
    auto t = Json::Tree();
    t.pushBack(10);
    t.pushBack(std::string("hello"));
    t.pushBack(true);
    t.pushBack(233);
    auto u = Json::Tree();
    u.pushBack(10);
    u.pushBack(std::string("hello"));
    u.pushBack(true);
    u.pushBack(233);
    expectComparesEqual(t, u);
}

TEST_F(TestTreeComparison, arraysWithSameMultipleElementsInDifferentOrderCompareNotEqual)
{
    auto t = Json::Tree();
    t.pushBack(10);
    t.pushBack(std::string("hello"));
    t.pushBack(true);
    t.pushBack(233);
    auto u = Json::Tree();
    u.pushBack(10);
    u.pushBack(true);
    u.pushBack(233);
    u.pushBack(std::string("hello"));
    expectComparesNotEqual(t, u);
}

TEST_F(TestTreeComparison, arraysWithSameMultipleElementsAndSubTreesCompareEqual)
{
    auto t_subtree = Json::Tree();
    t_subtree["a"] = 10;
    t_subtree["b"] = true;
    auto t = Json::Tree();
    t.pushBack(10);
    t.pushBack(std::string("hello"));
    t.pushBack(true);
    t.pushBack(t_subtree);
    t.pushBack(233);
    auto u_subtree = Json::Tree();
    u_subtree["a"] = 10;
    u_subtree["b"] = true;
    auto u = Json::Tree();
    u.pushBack(10);
    u.pushBack(std::string("hello"));
    u.pushBack(true);
    u.pushBack(u_subtree);
    u.pushBack(233);
    expectComparesEqual(t, u);
}
