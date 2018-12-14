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
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
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
#include <json/conversion_helpers/to_json_text.hpp>

#include <sstream>

#include <json/conversion_helpers/token.hpp>
#include <json/tree.hpp>
#include <json/value.hpp>

namespace CodedProject
{
namespace Json
{
namespace ConversionHelpers
{

void addStringIf(
    std::stringstream & ss,
    std::string const s,
    bool const add_string)
{
    if(add_string) ss << s;
}

void addFormatNewLine(
    std::stringstream & ss,
    bool const format)
{
    addStringIf(ss,"\n",format);
}

void addFormatSpaces(
    std::stringstream & ss,
    bool const format,
    int const n_spaces)
{
    addStringIf(ss,std::string(n_spaces,' '),format);
}

void addFormatNewLineAndIndent(
    std::stringstream & ss,
    bool const format,
    int indent_width)
{
    addFormatNewLine(ss, format);
    addFormatSpaces(ss,format,indent_width);
}


std::string multiValueTreeToJsonText(
    Tree const& t,
    TokenType opening_token,
    TokenType closing_token,
    bool const format,
    int const current_indent,
    std::function<void(Tree::value_type const&,std::stringstream&,bool,int)> add_element)
{
    auto indent_width=4;
    auto ss = std::stringstream{};
    ss << toJsonText(opening_token);
    auto add_comma = false;
    auto const subtree_indent = current_indent+indent_width;
    for(auto const& kv : t)
    {
        addStringIf(ss,toJsonText(TokenType::Comma),add_comma);
        addFormatNewLineAndIndent(ss, format,subtree_indent);
        add_element(kv,ss,format,subtree_indent);
        add_comma = true;
    }
    addFormatNewLineAndIndent(ss, format,current_indent);
    ss << toJsonText(closing_token);
    return ss.str();

}

std::string toJsonText(Tree const& t, bool const format, int const indent)
{
    if(t.isArray())
    {
        return multiValueTreeToJsonText(
            t,
            TokenType::LeftArrayBrace,
            TokenType::RightArrayBrace,
            format,
            indent,
            [](auto kv, auto & ss, auto const format, auto const indent){
                ss << toJsonText(kv.second, format, indent);
            });
    }
    else if(t.isDocument())
    {
        return multiValueTreeToJsonText(
            t,
            TokenType::LeftDocumentBrace,
            TokenType::RightDocumentBrace,
            format,
            indent,
            [](auto kv, auto & ss, auto const format, auto const indent){
                ss << toJsonText(Value(kv.first));
                ss << toJsonText(TokenType::Colon);
                addFormatSpaces(ss,format,1);
                ss << toJsonText(kv.second, format, indent);
            });
    }
    else if(t.isValue())
    {
        return toJsonText(t.getValue());
    }
    else
    {
        return "null";
    }
}

std::string toJsonText(Value const& v)
{
    switch(v.type())
    {
        case Value::Type::String:
            return "\"" + v.get<std::string>() + "\"";
        case Value::Type::Integer:
            return std::to_string(v.get<int>());
        case Value::Type::Bool:
            if(v.get<bool>())
                return "true";
            else
                return "false";
        case Value::Type::Float:
            return std::to_string(v.get<float>());
        case Value::Type::Null:
            return "null";
    }
}

std::string toJsonText(Token const& t)
{
    switch(t.type)
    {
        case TokenType::Value:
        case TokenType::StringValue:
            return toJsonText(t.value);
        case TokenType::Eof:
        case TokenType::StartOfFile:
            throw std::runtime_error(
                "ConversionHelpers::toJsonText(Token): Token" +
                toString(t.type) + " is not JSON serialisable.");
        default:
            return toJsonText(t.type);
    }
}

std::string toJsonText(TokenType const& type)
{
    switch(type)
    {
        case TokenType::LeftArrayBrace:
            return "[";
        case TokenType::RightArrayBrace:
            return "]";
        case TokenType::LeftDocumentBrace:
            return "{";
        case TokenType::RightDocumentBrace:
            return "}";
        case TokenType::Colon:
            return ":";
        case TokenType::Comma:
            return ",";
        case TokenType::Value:
        case TokenType::StringValue:
        case TokenType::Eof:
        case TokenType::StartOfFile:
            throw std::runtime_error(
                "ConversionHelpers::toJsonText(TokenType): Token type" +
                toString(type) + " cannot be converted to JSON without value.");
    }
}

}
}
}
