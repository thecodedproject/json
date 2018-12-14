/* Copyright (c) 2018, Coded Project
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * * Neither the name of the Coded Project nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \"AS IS\"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
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

TEST_F(TestTreeComparison, emptyDocumentTreesCompareEqual)
{
    auto t = Json::Tree(Json::Tree::Type::Document);
    auto u = Json::Tree(Json::Tree::Type::Document);
    expectComparesEqual(t, u);
}

TEST_F(TestTreeComparison, emptyArrayTreesCompareEqual)
{
    auto t = Json::Tree(Json::Tree::Type::Array);
    auto u = Json::Tree(Json::Tree::Type::Array);
    expectComparesEqual(t, u);
}

TEST_F(TestTreeComparison, emptyValuetTreesCompareEqual)
{
    auto t = Json::Tree(Json::Tree::Type::Value);
    auto u = Json::Tree(Json::Tree::Type::Value);
    expectComparesEqual(t, u);
}

TEST_F(TestTreeComparison, emptyDocumentAndArrayTreesCompareNotEqual)
{
    auto t = Json::Tree(Json::Tree::Type::Document);
    auto u = Json::Tree(Json::Tree::Type::Array);
    expectComparesNotEqual(t, u);
}

TEST_F(TestTreeComparison, emptyValueAndArrayTreesCompareNotEqual)
{
    auto t = Json::Tree(Json::Tree::Type::Value);
    auto u = Json::Tree(Json::Tree::Type::Array);
    expectComparesNotEqual(t, u);
}

TEST_F(TestTreeComparison, emptyDocumentAndValueTreesCompareNotEqual)
{
    auto t = Json::Tree(Json::Tree::Type::Document);
    auto u = Json::Tree(Json::Tree::Type::Value);
    expectComparesNotEqual(t, u);
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
