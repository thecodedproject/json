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

class TestTreeArrayUsage : public ::testing::Test
{
};

TEST_F(TestTreeArrayUsage, pushBackStringIntoArrayAndGetValueWithArrayIndexReturnsSameValue)
{
    auto t = Json::Tree();
    t.pushBack(std::string("some_value"));
    EXPECT_EQ("some_value", t[0].get<Json::String>());
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
    EXPECT_EQ(false, t[0].get<Json::Bool>());
    EXPECT_EQ("some_value", t[1].get<Json::String>());
    EXPECT_EQ(43, t[2].get<Json::Integer>());
    EXPECT_FLOAT_EQ(23.5f, t[3].get<Json::FloatingPoint>());
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

    EXPECT_EQ(14, t[0]["some_int_field"].get<Json::Integer>());
    EXPECT_EQ("hello world", t[0]["some_string_field"].get<Json::String>());
    EXPECT_EQ(43, t[1].get<Json::Integer>());
    EXPECT_FLOAT_EQ(13.5f, t[2]["some_float_field"].get<Json::FloatingPoint>());
    EXPECT_EQ(true, t[2]["some_bool_field"].get<Json::Bool>());
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

TEST_F(TestTreeArrayUsage, constructFromValueAndPushBackThrowsErrorWithHelpfulMessage)
{
    auto t = Json::Tree(23.1f);
    EXPECT_THROW({
        try
        {
            t.pushBack(2);
        }
        catch(std::exception & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("array"));
            EXPECT_THAT(err_msg, HasSubstr("pushBack(Tree)"));
            EXPECT_THAT(err_msg, HasSubstr("value"));
            throw;
        }
    }, Json::Tree::IncorrectCallForType);
}

TEST_F(TestTreeArrayUsage, constructFromDocumentAndPushBackThrowsErrorWithHelpfulMessage)
{
    auto t = Json::Tree();
    t["a"] = 234;
    EXPECT_THROW({
        try
        {
            t.pushBack(2);
        }
        catch(std::exception & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("array"));
            EXPECT_THAT(err_msg, HasSubstr("pushBack(Tree)"));
            EXPECT_THAT(err_msg, HasSubstr("document"));
            throw;
        }
    }, Json::Tree::IncorrectCallForType);
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
    EXPECT_EQ(123, t[0].get<Json::Integer>());
}

TEST_F(TestTreeArrayUsage, pushBackStringIntoArrayAndGetValueWithAtReturnsSameValue)
{
    auto t = Json::Tree();
    t.pushBack(std::string("some_value"));
    EXPECT_EQ("some_value", t.at(0).get<Json::String>());
}

TEST_F(TestTreeArrayUsage, getMultipleValuesWithAtAccessorReturnsCorrectValues)
{
    auto t = Json::Tree();
    t.pushBack(std::string("some_value"));
    t.pushBack(true);
    t.pushBack(234);
    t.pushBack(23.5f);
    EXPECT_EQ("some_value", t.at(0).get<Json::String>());
    EXPECT_TRUE(t.at(1).get<Json::Bool>());
    EXPECT_EQ(234, t.at(2).get<Json::Integer>());
    EXPECT_FLOAT_EQ(23.5f, t.at(3).get<Json::FloatingPoint>());
}

TEST_F(TestTreeArrayUsage, assignUsingAtAccessorAndGetValuesReturnsCorrectValue)
{
    auto t = Json::Tree();
    t.pushBack(std::string("some_value"));
    t.at(0) = 345;
    EXPECT_EQ(345, t.at(0).get<Json::Integer>());
}

TEST_F(TestTreeArrayUsage, getUsingAtAccessorOnConstTreeReturnsCorrectValue)
{
    auto t = Json::Tree();
    t.pushBack(345);
    auto const& t_const = t;
    EXPECT_EQ(345, t_const.at(0).get<Json::Integer>());
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
            EXPECT_THAT(err_msg, HasSubstr("at(size_t)"));
            EXPECT_THAT(err_msg, HasSubstr("array"));
            EXPECT_THAT(err_msg, HasSubstr("document"));
            throw;
        }
    }, Json::Tree::IncorrectCallForType);
}


TEST_F(TestTreeArrayUsage, accessElementWithAtWhichIsGreaterThanSizeThrowsOutOfRangeError)
{
    auto t = Json::Tree();
    t.pushBack(345);
    t.pushBack(345);
    t.pushBack(345);
    EXPECT_THROW({
        try
        {
            auto a = t.at(5);
        }
        catch(std::exception & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("at(size_t)"));
            EXPECT_THAT(err_msg, HasSubstr("index 5"));
            EXPECT_THAT(err_msg, HasSubstr("size 3"));
            throw;
        }
    }, std::out_of_range);
}

TEST_F(TestTreeArrayUsage, accessElementOnConstTreeWithAtWhichIsGreaterThanSizeThrowsOutOfRangeError)
{
    auto t = Json::Tree();
    t.pushBack(345);
    t.pushBack(345);
    t.pushBack(345);
    auto const& t_const = t;
    EXPECT_THROW({
        try
        {
            auto a = t_const.at(5);
        }
        catch(std::exception & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("at(size_t)"));
            EXPECT_THAT(err_msg, HasSubstr("index 5"));
            EXPECT_THAT(err_msg, HasSubstr("size 3"));
            throw;
        }
    }, std::out_of_range);
}
