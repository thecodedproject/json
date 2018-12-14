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
