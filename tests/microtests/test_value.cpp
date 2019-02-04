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

#include <json/value.hpp>

using namespace CodedProject;
using namespace ::testing;

class TestValue : public Test
{
};

TEST_F(TestValue, defaultConstructAndGetTypeGivesNullType)
{
    auto v = Json::Value();
    EXPECT_EQ(Json::Value::Type::Null, v.type());
}

TEST_F(TestValue, constructFromStringAndGetType)
{
    auto v = Json::Value(std::string("some_string"));
    EXPECT_EQ(Json::Value::Type::String, v.type());
}

TEST_F(TestValue, constructFromIntAndGetType)
{
    auto v = Json::Value(10);
    EXPECT_EQ(Json::Value::Type::Integer, v.type());
}

TEST_F(TestValue, constructFromLongLongAndGetValueGivesInteger)
{
    Json::Value v{50ll};
    EXPECT_EQ(Json::Value::Type::Integer, v.type());
}

TEST_F(TestValue, constructFromShortIntAndGetValueGivesInteger)
{
    int8_t short_int{10};
    Json::Value v{short_int};
    EXPECT_EQ(Json::Value::Type::Integer, v.type());
}

TEST_F(TestValue, constructFromFloatAndGetType)
{
    auto v = Json::Value(2.0f);
    EXPECT_EQ(Json::Value::Type::FloatingPoint, v.type());
}

TEST_F(TestValue, constructFromDoubleAndGetType)
{
    Json::Value v{2.0};
    EXPECT_EQ(Json::Value::Type::FloatingPoint, v.type());
}

TEST_F(TestValue, constructFromBoolAndGetType)
{
    auto v = Json::Value(true);
    EXPECT_EQ(Json::Value::Type::Bool, v.type());
}

TEST_F(TestValue, constructFromStringAndGetValueAsString)
{
    auto value = std::string("some_value");
    auto v = Json::Value(value);
    EXPECT_EQ(value, v.get<Json::String>());
}

TEST_F(TestValue, constructFromCharArrayAndGetValueAsString)
{
    auto value = "some_value_2";
    auto v = Json::Value(value);
    EXPECT_EQ(value, v.get<Json::String>());
}

TEST_F(TestValue, defaultConstructAndGetValueAsStringThrowsWithHelpfulMessage)
{
    auto v = Json::Value();
    EXPECT_THROW({
        try
        {
            v.get<Json::String>();
        }
        catch(Json::Value::IncorrectTypeConversion & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("Null"));
            EXPECT_THAT(err_msg, HasSubstr("String"));
            throw;
        }
    },Json::Value::IncorrectTypeConversion);
}

TEST_F(TestValue, constructFromIntAndGetValueAsStringThrowsWithHelpfulMessage)
{
    auto v = Json::Value(10);
    EXPECT_THROW({
        try
        {
            v.get<Json::String>();
        }
        catch(Json::Value::IncorrectTypeConversion & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("10"));
            EXPECT_THAT(err_msg, HasSubstr("Integer"));
            EXPECT_THAT(err_msg, HasSubstr("String"));
            throw;
        }
    },Json::Value::IncorrectTypeConversion);
}

TEST_F(TestValue, constructFromTrueBoolAndGetValueAsStringThrowsWithHelpfulMessage)
{
    auto v = Json::Value(true);
    EXPECT_THROW({
        try
        {
            v.get<Json::String>();
        }
        catch(Json::Value::IncorrectTypeConversion & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("true"));
            EXPECT_THAT(err_msg, HasSubstr("Bool"));
            EXPECT_THAT(err_msg, HasSubstr("String"));
            throw;
        }
    },Json::Value::IncorrectTypeConversion);
}

TEST_F(TestValue, constructFromFalseBoolAndGetValueAsStringThrowsWithHelpfulMessage)
{
    auto v = Json::Value(false);
    EXPECT_THROW({
        try
        {
            v.get<Json::String>();
        }
        catch(Json::Value::IncorrectTypeConversion & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("false"));
            EXPECT_THAT(err_msg, HasSubstr("Bool"));
            EXPECT_THAT(err_msg, HasSubstr("String"));
            throw;
        }
    },Json::Value::IncorrectTypeConversion);
}

TEST_F(TestValue, constructFromFloatAndGetValueAsStringThrowsWithHelpfulMessage)
{
    auto v = Json::Value(2.5f);
    EXPECT_THROW({
        try
        {
            v.get<Json::String>();
        }
        catch(Json::Value::IncorrectTypeConversion & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("2.50"));
            EXPECT_THAT(err_msg, HasSubstr("FloatingPoint"));
            EXPECT_THAT(err_msg, HasSubstr("String"));
            throw;
        }
    },Json::Value::IncorrectTypeConversion);
}

TEST_F(TestValue, constructFromIntAndGetValueAsInteger)
{
    auto value = 23;
    auto v = Json::Value(value);
    EXPECT_EQ(value, v.get<Json::Integer>());
}

TEST_F(TestValue, constructFromNegativeIntAndGetValueAsInteger)
{
    auto value = -23;
    auto v = Json::Value(value);
    EXPECT_EQ(value, v.get<Json::Integer>());
}

TEST_F(TestValue, constructFromLongIntAndGetValueAsInteger)
{
    auto value = 25ll;
    auto v = Json::Value(value);
    EXPECT_EQ(value, v.get<Json::Integer>());
}

TEST_F(TestValue, constructFromNegativeLongIntAndGetValueAsInteger)
{
    auto value = -25ll;
    auto v = Json::Value(value);
    EXPECT_EQ(value, v.get<Json::Integer>());
}

TEST_F(TestValue, constructFromShortIntAndGetValueAsInteger)
{
    int8_t value{20};
    auto v = Json::Value(value);
    EXPECT_EQ(value, v.get<Json::Integer>());
}

TEST_F(TestValue, constructFromNegativeShortIntAndGetValueAsInteger)
{
    int8_t value{-20};
    auto v = Json::Value(value);
    EXPECT_EQ(value, v.get<Json::Integer>());
}

TEST_F(TestValue, defaultConstructAndGetValueAsIntThrowsWithHelpfulMessage)
{
    auto v = Json::Value();
    EXPECT_THROW({
        try
        {
            v.get<Json::Integer>();
        }
        catch(Json::Value::IncorrectTypeConversion & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("Null"));
            EXPECT_THAT(err_msg, HasSubstr("Integer"));
            throw;
        }
    },Json::Value::IncorrectTypeConversion);
}

TEST_F(TestValue, constructFromStringAndGetValueAsIntegerThrowsWithHelpfulMessage)
{
    auto v = Json::Value(std::string("hello"));
    EXPECT_THROW({
        try
        {
            v.get<Json::Integer>();
        }
        catch(Json::Value::IncorrectTypeConversion & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("hello"));
            EXPECT_THAT(err_msg, HasSubstr("String"));
            EXPECT_THAT(err_msg, HasSubstr("Integer"));
            throw;
        }
    },Json::Value::IncorrectTypeConversion);
}

TEST_F(TestValue, constructFromFloatAndGetValueAsIntegerThrowsWithHelpfulMessage)
{
    auto v = Json::Value(4.5f);
    EXPECT_THROW({
        try
        {
            v.get<Json::Integer>();
        }
        catch(Json::Value::IncorrectTypeConversion & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("4.50"));
            EXPECT_THAT(err_msg, HasSubstr("FloatingPoint"));
            EXPECT_THAT(err_msg, HasSubstr("Integer"));
            throw;
        }
    },Json::Value::IncorrectTypeConversion);
}

TEST_F(TestValue, constructFromBoolAndGetValueAsIntegerThrowsWithHelpfulMessage)
{
    auto v = Json::Value(true);
    EXPECT_THROW({
        try
        {
            v.get<Json::Integer>();
        }
        catch(Json::Value::IncorrectTypeConversion & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("true"));
            EXPECT_THAT(err_msg, HasSubstr("Bool"));
            EXPECT_THAT(err_msg, HasSubstr("Integer"));
            throw;
        }
    },Json::Value::IncorrectTypeConversion);
}

TEST_F(TestValue, constructFromFloatAndGetValueAsFloat)
{
    auto value = 23.5f;
    auto v = Json::Value(value);
    EXPECT_DOUBLE_EQ(value, v.get<Json::FloatingPoint>());
}

TEST_F(TestValue, constructFromDoubleAndGetValueAsFloatingPoint)
{
    auto value = 23.8;
    auto v = Json::Value(value);
    EXPECT_DOUBLE_EQ(value, v.get<Json::FloatingPoint>());
}

TEST_F(TestValue, defaultConstructAndGetValueAsFloatThrowsWithHelpfulMessage)
{
    auto v = Json::Value();
    EXPECT_THROW({
        try
        {
            v.get<Json::FloatingPoint>();
        }
        catch(Json::Value::IncorrectTypeConversion & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("Null"));
            EXPECT_THAT(err_msg, HasSubstr("FloatingPoint"));
            throw;
        }
    },Json::Value::IncorrectTypeConversion);
}

TEST_F(TestValue, constructFromStringAndGetValueAsFloatThrowsWithHelpfulMessage)
{
    auto v = Json::Value(std::string("eggs"));
    EXPECT_THROW({
        try
        {
            v.get<Json::FloatingPoint>();
        }
        catch(Json::Value::IncorrectTypeConversion & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("eggs"));
            EXPECT_THAT(err_msg, HasSubstr("String"));
            EXPECT_THAT(err_msg, HasSubstr("FloatingPoint"));
            throw;
        }
    },Json::Value::IncorrectTypeConversion);
}

TEST_F(TestValue, constructFromIntAndGetValueAsFloatThrowsWithHelpfulMessage)
{
    auto v = Json::Value(13);
    EXPECT_THROW({
        try
        {
            v.get<Json::FloatingPoint>();
        }
        catch(Json::Value::IncorrectTypeConversion & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("13"));
            EXPECT_THAT(err_msg, HasSubstr("Integer"));
            EXPECT_THAT(err_msg, HasSubstr("FloatingPoint"));
            throw;
        }
    },Json::Value::IncorrectTypeConversion);
}

TEST_F(TestValue, constructFromBoolAndGetValueAsFloatThrowsWithHelpfulMessage)
{
    auto v = Json::Value(false);
    EXPECT_THROW({
        try
        {
            v.get<Json::FloatingPoint>();
        }
        catch(Json::Value::IncorrectTypeConversion & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("false"));
            EXPECT_THAT(err_msg, HasSubstr("Bool"));
            EXPECT_THAT(err_msg, HasSubstr("FloatingPoint"));
            throw;
        }
    },Json::Value::IncorrectTypeConversion);
}

TEST_F(TestValue, constructFromBoolAndGetValueAsBool)
{
    auto value = true;
    auto v = Json::Value(value);
    EXPECT_EQ(value, v.get<Json::Bool>());
}

TEST_F(TestValue, defaultConstructAndGetValueAsBoolThrowsWithHelpfulMessage)
{
    auto v = Json::Value();
    EXPECT_THROW({
        try
        {
            v.get<Json::Bool>();
        }
        catch(Json::Value::IncorrectTypeConversion & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("Null"));
            EXPECT_THAT(err_msg, HasSubstr("Bool"));
            throw;
        }
    },Json::Value::IncorrectTypeConversion);
}

TEST_F(TestValue, constructFromStringAndGetValueAsBoolThrowsWithHelpfulMessage)
{
    auto v = Json::Value(std::string("coke"));
    EXPECT_THROW({
        try
        {
            v.get<Json::Bool>();
        }
        catch(Json::Value::IncorrectTypeConversion & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("coke"));
            EXPECT_THAT(err_msg, HasSubstr("String"));
            EXPECT_THAT(err_msg, HasSubstr("Bool"));
            throw;
        }
    },Json::Value::IncorrectTypeConversion);
}

TEST_F(TestValue, constructFromFloatAndGetValueAsBoolThrowsWithHelpfulMessage)
{
    auto v = Json::Value(34.5f);
    EXPECT_THROW({
        try
        {
            v.get<Json::Bool>();
        }
        catch(Json::Value::IncorrectTypeConversion & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("34.50"));
            EXPECT_THAT(err_msg, HasSubstr("FloatingPoint"));
            EXPECT_THAT(err_msg, HasSubstr("Bool"));
            throw;
        }
    },Json::Value::IncorrectTypeConversion);
}

TEST_F(TestValue, constructFromIntAndGetValueAsBoolThrowsWithHelpfulMessage)
{
    auto v = Json::Value(32);
    EXPECT_THROW({
        try
        {
            v.get<Json::Bool>();
        }
        catch(Json::Value::IncorrectTypeConversion & e)
        {
            auto err_msg = e.what();
            EXPECT_THAT(err_msg, HasSubstr("32"));
            EXPECT_THAT(err_msg, HasSubstr("Integer"));
            EXPECT_THAT(err_msg, HasSubstr("Bool"));
            throw;
        }
    },Json::Value::IncorrectTypeConversion);
}

TEST_F(TestValue, equalityOperatorsWhenConstructedFromSameStrings)
{
    auto v1 = Json::Value(std::string("some_string"));
    auto v2 = Json::Value(std::string("some_string"));
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 != v2);
}

TEST_F(TestValue, equalityOperatorsWhenConstructedFromDifferentStrings)
{
    auto v1 = Json::Value(std::string("some_string"));
    auto v2 = Json::Value(std::string("some_other_string"));
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(TestValue, equalityOperatorsWhenConstructedFromSameFloats)
{
    auto v1 = Json::Value(12.5f);
    auto v2 = Json::Value(12.5f);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 != v2);
}

TEST_F(TestValue, equalityOperatorsWhenConstructedFromDifferentFloats)
{
    auto v1 = Json::Value(12.5f);
    auto v2 = Json::Value(10.0f);
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(TestValue, equalityOperatorsWhenConstructedFromSameIntegers)
{
    auto v1 = Json::Value(12);
    auto v2 = Json::Value(12);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 != v2);
}

TEST_F(TestValue, equalityOperatorsWhenConstructedFromDifferentIntegers)
{
    auto v1 = Json::Value(12);
    auto v2 = Json::Value(11);
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(TestValue, equalityOperatorsWhenConstructedFromSameBools)
{
    auto v1 = Json::Value(true);
    auto v2 = Json::Value(true);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 != v2);
}

TEST_F(TestValue, equalityOperatorsWhenConstructedFromDifferentBools)
{
    auto v1 = Json::Value(true);
    auto v2 = Json::Value(false);
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(TestValue, equalityOperatorsWhenConstructedFromDifferentTypes)
{
    auto v1 = Json::Value(true);
    auto v2 = Json::Value(12);
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
}
