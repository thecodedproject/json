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

#include <json/conversion_helpers/to_json_text.hpp>

#include <json/conversion_helpers/token.hpp>
#include <json/value.hpp>

using namespace CodedProject::Json;
using namespace CodedProject::Json::ConversionHelpers;

class TestToJsonText : public ::testing::Test
{
};

TEST_F(TestToJsonText, stringValue)
{
    auto v = Value("some_value");
    EXPECT_EQ("\"some_value\"", toJsonText(v));
}

TEST_F(TestToJsonText, differentStringValue)
{
    auto v = Value("some_other_value");
    EXPECT_EQ("\"some_other_value\"", toJsonText(v));
}

TEST_F(TestToJsonText, intValue)
{
    auto v = Value(123);
    EXPECT_EQ("123", toJsonText(v));
}

TEST_F(TestToJsonText, differentIntValue)
{
    auto v = Value(12345);
    EXPECT_EQ("12345", toJsonText(v));
}

TEST_F(TestToJsonText, boolTrueValue)
{
    auto v = Value(true);
    EXPECT_EQ("true", toJsonText(v));
}

TEST_F(TestToJsonText, boolFalseValue)
{
    auto v = Value(false);
    EXPECT_EQ("false", toJsonText(v));
}

TEST_F(TestToJsonText, floatValue)
{
    auto v = Value(1.5f);
    EXPECT_EQ("1.500000", toJsonText(v));
}

TEST_F(TestToJsonText, differentFloatValue)
{
    auto v = Value(10.5f);
    EXPECT_EQ("10.500000", toJsonText(v));
}

TEST_F(TestToJsonText, nullValue)
{
    auto v = Value();
    EXPECT_EQ("null", toJsonText(v));
}

TEST_F(TestToJsonText, rightArrayBraceToken)
{
    auto t = Token{TokenType::RightArrayBrace};
    EXPECT_EQ("]", toJsonText(t));
}

TEST_F(TestToJsonText, leftArrayBraceToken)
{
    auto t = Token{TokenType::LeftArrayBrace};
    EXPECT_EQ("[", toJsonText(t));
}

TEST_F(TestToJsonText, leftDocumentBraceToken)
{
    auto t = Token{TokenType::LeftDocumentBrace};
    EXPECT_EQ("{", toJsonText(t));
}

TEST_F(TestToJsonText, rightDocumentBraceToken)
{
    auto t = Token{TokenType::RightDocumentBrace};
    EXPECT_EQ("}", toJsonText(t));
}

TEST_F(TestToJsonText, colonToken)
{
    auto t = Token{TokenType::Colon};
    EXPECT_EQ(":", toJsonText(t));
}

TEST_F(TestToJsonText, commaToken)
{
    auto t = Token{TokenType::Comma};
    EXPECT_EQ(",", toJsonText(t));
}

TEST_F(TestToJsonText, valueToken)
{
    auto t = Token{TokenType::Value, 123};
    EXPECT_EQ("123", toJsonText(t));
}

TEST_F(TestToJsonText, stringValueToken)
{
    auto t = Token{TokenType::StringValue, "hello"};
    EXPECT_EQ("\"hello\"", toJsonText(t));
}

TEST_F(TestToJsonText, eofTokenThrowsError)
{
    auto t = Token{TokenType::Eof};
    EXPECT_THROW(
        toJsonText(t),
        std::runtime_error);
}

TEST_F(TestToJsonText, startOfFileTokenThrowsError)
{
    auto t = Token{TokenType::Eof};
    EXPECT_THROW(
        toJsonText(t),
        std::runtime_error);
}

TEST_F(TestToJsonText, ValueTokenTypeThrowsError)
{
    EXPECT_THROW(
        toJsonText(TokenType::Value),
        std::runtime_error);
}

TEST_F(TestToJsonText, StringValueTokenTypeThrowsError)
{
    EXPECT_THROW(
        toJsonText(TokenType::StringValue),
        std::runtime_error);
}
