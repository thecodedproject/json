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
#include <json/conversion_helpers/lexer.hpp>

#include <functional>
#include <map>

#include <json/conversion_helpers/to_json_text.hpp>
#include <json/parse_error.hpp>

namespace CodedProject
{
namespace Json
{
namespace ConversionHelpers
{

Lexer::Lexer(std::string const& json_text)
: json_text_{json_text},
  current_char_{std::begin(json_text_)}
{
}

Token Lexer::next()
{
    skipWhitespace();
    last_token_start_char_ = current_char_;
    current_token_ = handleNextToken();
    return current_token_;
}

Token Lexer::next(TokenType expected_token_type)
{
    auto actual_token = next();
    if(expected_token_type != actual_token.type)
    {
        if(!(expected_token_type == TokenType::Value &&
            actual_token.type == TokenType::StringValue))
        {
            throw ParseError::expectedToken(
                toJsonText(current_token_),
                expected_token_type,
                lineAndColumnOfChar(last_token_start_char_)
            );
        }
    }

    return actual_token;
}

Token Lexer::currentToken()
{
    return current_token_;
}

TokenType Lexer::peekNextTokenType(int num_tokens_to_peek_forward)
{
    auto current_char = current_char_;
    auto last_token_start_char = last_token_start_char_;
    auto current_token = current_token_;

    auto next_token = Token{};
    for(auto i=0; i<num_tokens_to_peek_forward; ++i)
        next_token = next();

    current_char_ = current_char;
    last_token_start_char_ = last_token_start_char;
    current_token_ = current_token;

    return next_token.type;
}

void Lexer::skipWhitespace()
{
    while(*current_char_ == ' ' || *current_char_ == '\n')
    {
        ++current_char_;
    }
}

Token Lexer::handleNextToken()
{
    auto char_tokens_and_length = std::map<char,std::pair<Token, size_t>>{
        {'[', {{TokenType::LeftArrayBrace},1}},
        {']', {{TokenType::RightArrayBrace},1}},
        {'{', {{TokenType::LeftDocumentBrace},1}},
        {'}', {{TokenType::RightDocumentBrace},1}},
        {':', {{TokenType::Colon},1}},
        {',', {{TokenType::Comma},1}},
        {'t', {{TokenType::Value, true},4}},
        {'f', {{TokenType::Value, false},5}},
        {'n', {{TokenType::Value, {}},4}}
    };

    if(current_char_ == std::end(json_text_))
    {
        return {TokenType::Eof};
    }
    else if(char_tokens_and_length.count(*current_char_))
    {
        return checkTokenStringIsValidAndAdvanceCurrentChar(
            char_tokens_and_length[*current_char_]);
    }
    else if(*current_char_ == '"')
    {
        return handleStringValue();
    }
    else
    {
        return handleNumberValue();
    }
}

Token Lexer::checkTokenStringIsValidAndAdvanceCurrentChar(
    std::pair<Token, size_t> const& token_and_length)
{
    auto token_start_char = current_char_;
    advanceCurrentCharButNotBeyondEnd(token_and_length.second);
    auto expected_token_string = toJsonText(token_and_length.first);
    auto actual_token_string = std::string(token_start_char, current_char_);

    if(expected_token_string != actual_token_string)
    {
        throw ParseError::invalidToken(
            actual_token_string,
            lineAndColumnOfChar(token_start_char)
        );
    }

    return token_and_length.first;
}

Token Lexer::handleStringValue()
{
    ++current_char_;

    auto string_start_char = current_char_;

    advanceCurrentCharButNotBeyondEndWhile([](auto c){
        return c!='"';
    });

    if(current_char_ == std::end(json_text_))
    {
        throw ParseError::unterminatedString(
            {string_start_char, current_char_},
            lineAndColumnOfChar(string_start_char)
        );
    }

    auto value_string = std::string(string_start_char, current_char_);

    std::advance(current_char_, 1);
    return {TokenType::StringValue, value_string};
}

Token Lexer::handleNumberValue()
{
    auto value_start = current_char_;

    advanceCurrentCharButNotBeyondEndWhile([](auto c){
        return std::string("-0123456789.").find(c)!=std::string::npos;
    });

    auto value_string = std::string(value_start, current_char_);

    if(value_string.find(".") == std::string::npos)
    {
        return {TokenType::Value, std::stoi(value_string)};
    }
    else
    {
        return {TokenType::Value, std::stof(value_string)};
    }
}

void Lexer::advanceCurrentCharButNotBeyondEnd(size_t amount_to_advance)
{
    if(std::distance(current_char_, std::cend(json_text_)) < amount_to_advance)
    {
        current_char_=std::end(json_text_);
    }
    else
    {
        std::advance(current_char_, amount_to_advance);
    }
}

void Lexer::advanceCurrentCharButNotBeyondEndWhile(
    std::function<bool(char)> while_predicate)
{
    while(while_predicate(*current_char_)
        &&current_char_!=std::end(json_text_))
    {
        ++current_char_;
    }
}

std::pair<int, int> Lexer::lineAndColumnOfChar(
    std::string::const_iterator start_char) const
{
    auto char_column = 1;
    auto char_line = 1;
    for(auto it=std::cbegin(json_text_);
        it!=start_char;
        ++it)
    {
        if(*it == '\n')
        {
            char_column = 1;
            ++char_line;
        }
        else
        {
            ++char_column;
        }

    }
    return {char_line, char_column};
}

}
}
}
