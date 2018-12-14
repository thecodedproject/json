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

