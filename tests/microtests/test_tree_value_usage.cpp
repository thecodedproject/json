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
