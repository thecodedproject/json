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

using namespace CodedProject::Json;

class TestConversionToJsonString : public ::testing::Test
{
};

TEST_F(TestConversionToJsonString, nullValueTree)
{
    auto t = Tree(Value());
    auto expected = "null";
    auto actual = toString(t);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionToJsonString, integerValueTree)
{
    auto t = Tree(1234);
    auto expected = "1234";
    auto actual = toString(t);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionToJsonString, stringValueTree)
{
    auto t = Tree("hello world");
    auto expected = "\"hello world\"";
    auto actual = toString(t);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionToJsonString, boolTrueValueTree)
{
    auto t = Tree(true);
    auto expected = "true";
    auto actual = toString(t);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionToJsonString, boolFalseValueTree)
{
    auto t = Tree(false);
    auto expected = "false";
    auto actual = toString(t);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionToJsonString, arrayWithSingleValue)
{
    auto t = Builder()
        .pushBack(234)
        .getTree();
    auto expected = "[234]";
    auto actual = toString(t);
    EXPECT_EQ(expected, actual);
}

TEST_F(TestConversionToJsonString, arrayWithMultipleNestedDocumentsAndArraysWithFormatting)
{
    auto t = Builder()
        .pushBack(123)
        .openSubtree()
            .append("a", true)
            .openSubtree("b")
                .pushBack(1)
                .openSubtree()
                    .openSubtree("1")
                        .pushBack(5)
                    .closeSubtree()
                    .openSubtree("2")
                        .append("a", true)
                    .closeSubtree()
                .closeSubtree()
            .closeSubtree()
        .closeSubtree()
        .openSubtree()
            .pushBack(true)
            .pushBack(6)
            .openSubtree()
                .pushBack(987)
                .pushBack(true)
            .closeSubtree()
        .closeSubtree()
    .getTree();

    auto expected =
        "[\n"
        "    123,\n"
        "    {\n"
        "        \"a\": true,\n"
        "        \"b\": [\n"
        "            1,\n"
        "            {\n"
        "                \"1\": [\n"
        "                    5\n"
        "                ],\n"
        "                \"2\": {\n"
        "                    \"a\": true\n"
        "                }\n"
        "            }\n"
        "        ]\n"
        "    },\n"
        "    [\n"
        "        true,\n"
        "        6,\n"
        "        [\n"
        "            987,\n"
        "            true\n"
        "        ]\n"
        "    ]\n"
        "]";
    auto actual = toString(t, true);
    EXPECT_EQ(expected, actual);
}
