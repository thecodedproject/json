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

class TestTreeErase : public ::testing::Test
{
};

TEST_F(TestTreeErase, eraseFieldThatExistsReturns1)
{
    auto t = Json::Tree();
    t["first"] = 10;
    t["second"] = false;
    t["third"] = std::string("hello");

    ASSERT_TRUE(t.isDocument());
    ASSERT_EQ(3, t.size());

    EXPECT_EQ(1, t.erase("second"));
}

TEST_F(TestTreeErase,
    eraseFieldFromDocumentByFieldNameForFieldThatExistsAndIterateThroughGivesCorrectValues)
{
    auto t = Json::Tree();
    t["first"] = 10;
    t["second"] = false;
    t["third"] = std::string("hello");

    ASSERT_TRUE(t.isDocument());
    ASSERT_EQ(3, t.size());

    t.erase("second");

    ASSERT_EQ(2, t.size());
    auto it = std::begin(t);
    EXPECT_EQ("first", it->first);
    EXPECT_EQ(10, it->second.get<Json::Integer>());
    ++it;
    EXPECT_EQ("third", it->first);
    EXPECT_EQ("hello", it->second.get<Json::String>());
    ++it;
    EXPECT_TRUE(it == std::end(t));
}

TEST_F(TestTreeErase,
    eraseFieldFromDocumentByFieldNameForFieldThatExistsAndGetExistingFieldsByNameGivesCorrectValues)
{
    auto t = Json::Tree();
    t["first"] = 10;
    t["second"] = false;
    t["third"] = std::string("hello");

    ASSERT_TRUE(t.isDocument());
    ASSERT_EQ(3, t.size());

    t.erase("second");

    ASSERT_EQ(2, t.size());
    EXPECT_EQ(10, t["first"].get<Json::Integer>());
    EXPECT_EQ("hello", t["third"].get<Json::String>());
}

TEST_F(TestTreeErase, eraseFieldThatDoesNotExistFromDocumentReturnsZero)
{
    auto t = Json::Tree();
    t["first"] = 10;
    t["second"] = false;
    t["third"] = std::string("hello");

    EXPECT_EQ(0, t.erase("some_field"));
}

TEST_F(TestTreeErase, eraseFieldThatDoesNotExistFromDocumentDoesNotChangeSizeOfDocument)
{
    auto t = Json::Tree();
    t["first"] = 10;
    t["second"] = false;
    t["third"] = std::string("hello");

    ASSERT_EQ(3, t.size());

    t.erase("some_field");

    EXPECT_EQ(3, t.size());
}

TEST_F(TestTreeErase,
    eraseFieldThatDoesNotExistFromDocumentDoesNotChangeExistingValuesWhenAccessedByFieldName)
{
    auto t = Json::Tree();
    t["first"] = 10;
    t["second"] = false;
    t["third"] = std::string("hello");

    ASSERT_TRUE(t.isDocument());
    ASSERT_EQ(3, t.size());

    t.erase("some_field");

    EXPECT_EQ(10, t["first"].get<Json::Integer>());
    EXPECT_FALSE(t["second"].get<Json::Bool>());
    EXPECT_EQ("hello", t["third"].get<Json::String>());
}

TEST_F(TestTreeErase,
    eraseFieldFromDocumentAndInsertTheSameFieldAndAccessAllFieldsByFieldNameGivesorrectValues)
{
    auto t = Json::Tree();
    t["first"] = 10;
    t["second"] = false;
    t["third"] = std::string("hello");

    ASSERT_TRUE(t.isDocument());
    ASSERT_EQ(3, t.size());

    t.erase("second");
    t["second"] = 23.5f;

    EXPECT_EQ(10, t["first"].get<Json::Integer>());

    std::cout << static_cast<int>(t["third"].getValue().type()) << std::endl;

    EXPECT_EQ("hello", t["third"].get<Json::String>());
    EXPECT_FLOAT_EQ(23.5f, t["second"].get<Json::FloatingPoint>());
}

TEST_F(TestTreeErase, tryToEraseFieldFromValueTreeThrowsErrorWithHelpfulMessage)
{
    auto t = Json::Tree(std::string("some_value"));
    ASSERT_TRUE(t.isValue());

    EXPECT_THROW({
        try
        {
            t.erase("some_field");
        }
        catch(std::exception & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("document"));
            EXPECT_THAT(err_msg, HasSubstr("erase(std::string)"));
            EXPECT_THAT(err_msg, HasSubstr("value"));
            throw;
        }
    }, Json::Tree::IncorrectCallForType);
}

TEST_F(TestTreeErase, tryToEraseFieldFromArrayTreeThrowsErrorWithHelpfulMessage)
{
    auto t = Json::Tree();
    t.pushBack(1);
    ASSERT_TRUE(t.isArray());

    EXPECT_THROW({
        try
        {
            t.erase("some_field");
        }
        catch(std::exception & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("document"));
            EXPECT_THAT(err_msg, HasSubstr("erase(std::string)"));
            EXPECT_THAT(err_msg, HasSubstr("array"));
            throw;
        }
    }, Json::Tree::IncorrectCallForType);
}

TEST_F(TestTreeErase, eraseElementFromDocumentTreeWithIteratorReducesSizeByOne)
{
    auto t = Json::Tree();
    t["a"] = 10;
    t["b"] = 12.3f;
    t["c"] = true;

    ASSERT_EQ(3, t.size());

    auto element_to_erase = std::begin(t);
    t.erase(element_to_erase);

    EXPECT_EQ(2, t.size());
}

TEST_F(TestTreeErase, eraseElementFromDocumentTreeWithIteratorAndIterateOverRemainingValuesGivesCorrectValues)
{
    auto t = Json::Tree();
    t["a"] = 10;
    t["b"] = 12.3f;
    t["c"] = true;

    ASSERT_EQ(3, t.size());

    auto element_to_erase = std::begin(t);
    t.erase(element_to_erase);

    ASSERT_EQ(2, t.size());
    auto it = std::begin(t);
    EXPECT_EQ("b", it->first);
    EXPECT_FLOAT_EQ(12.3f, it->second.get<Json::FloatingPoint>());
    ++it;
    EXPECT_EQ("c", it->first);
    EXPECT_TRUE(it->second.get<Json::Bool>());
    ++it;
    EXPECT_TRUE(it == std::end(t));
}

TEST_F(TestTreeErase,
    eraseElementFromDocumentTreeWithIteratorAndGetRemainingValuesByFieldGivesCorrectValues)
{
    auto t = Json::Tree();
    t["a"] = 10;
    t["b"] = 12.3f;
    t["c"] = true;

    ASSERT_EQ(3, t.size());

    auto element_to_erase = std::begin(t);
    t.erase(element_to_erase);

    EXPECT_FLOAT_EQ(12.3f, t["b"].get<Json::FloatingPoint>());
    EXPECT_TRUE(t["c"].get<Json::Bool>());
}
