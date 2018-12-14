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

#include <json/conversion.hpp>

#include <json/builder.hpp>

using namespace CodedProject;

class TestConversionFromJsonString : public ::testing::Test
{
};

TEST_F(TestConversionFromJsonString, convertDocumentWithSingleIntegerFieldAndNoSpaces)
{
    auto json_string = "{\"i\":1}";

    auto expected = Json::Builder()
        .append("i", 1)
        .getTree();

    auto actual = Json::fromString(json_string);

    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionFromJsonString, convertDocumentWithSingleBoolFieldAndNoSpaces)
{
    auto json_string = "{\"b\":true}";

    auto expected = Json::Builder()
        .append("b", true)
        .getTree();

    auto actual = Json::fromString(json_string);

    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionFromJsonString, convertDocumentWithSingleFloatFieldAndNoSpaces)
{
    auto json_string = "{\"f\":12.5}";

    auto expected = Json::Builder()
        .append("f", 12.5f)
        .getTree();

    auto actual = Json::fromString(json_string);

    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionFromJsonString, convertDocumentWithSingleStringFieldWithSpaces)
{
    auto json_string = " { \"s\" :  \"hello world\" } ";

    auto expected = Json::Builder()
        .append("s", "hello world")
        .getTree();

    auto actual = Json::fromString(json_string);

    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionFromJsonString, convertDocumentWithSingleArrayWithSingleElement)
{
    auto json_string = "{\"array\": [10]}";

    auto expected = Json::Builder()
        .openSubtree("array")
            .pushBack(10)
        .closeSubtree()
        .getTree();

    auto actual = Json::fromString(json_string);

    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionFromJsonString, convertDocumentWithSingleArrayWithMultipleElements)
{
    auto json_string = "{\"array\": [10, true, \"hello\", \"world\"]}";

    auto expected = Json::Builder()
        .openSubtree("array")
            .pushBack(10)
            .pushBack(true)
            .pushBack("hello")
            .pushBack("world")
        .closeSubtree()
        .getTree();

    auto actual = Json::fromString(json_string);

    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionFromJsonString, convertDocumentWithMultipleValuesOfDifferentTypes)
{
    auto json_string = R"({
        "s": "hello world",
        "i": 10,
        "negative": -10,
        "b": true,
        "f": 12.5
    })";

    auto expected = Json::Builder()
        .append("s", "hello world")
        .append("i", 10)
        .append("negative", -10)
        .append("b", true)
        .append("f", 12.5f)
        .getTree();

    auto actual = Json::fromString(json_string);

    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionFromJsonString, convertDocumentWithMultipleArraysAndValues)
{
    auto json_string = R"({
        "s": "hello world",
        "i": 10,
        "a1": [true, false, 10, "hello"],
        "negative": -10,
        "a2": [false, -210, "world"]
    })";

    auto expected = Json::Builder()
        .append("s", "hello world")
        .append("i", 10)
        .openSubtree("a1")
            .pushBack(true)
            .pushBack(false)
            .pushBack(10)
            .pushBack("hello")
        .closeSubtree()
        .append("negative", -10)
        .openSubtree("a2")
            .pushBack(false)
            .pushBack(-210)
            .pushBack("world")
        .closeSubtree()
        .getTree();

    auto actual = Json::fromString(json_string);

    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionFromJsonString, convertDocumentWithSingleSubdocument)
{
    auto json_string = R"({
        "d": {
            "s": "hello world",
            "i": 10,
            "negative": -10
        }
    })";

    auto expected = Json::Builder()
        .openSubtree("d")
            .append("s", "hello world")
            .append("i", 10)
            .append("negative", -10)
        .closeSubtree()
        .getTree();

    auto actual = Json::fromString(json_string);

    EXPECT_EQ(expected, actual);
}
