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
#include <json/conversion_helpers/grammer.hpp>

#include <json/conversion_helpers/lexer.hpp>
#include <json/parse_error.hpp>

namespace CodedProject
{
namespace Json
{
namespace ConversionHelpers
{
namespace Grammer
{

Tree jsonExpression(Lexer & lexer)
{
    auto next_token = lexer.peekNextTokenType();
    if(next_token == TokenType::LeftDocumentBrace)
    {
        return document(lexer);
    }
    else if(next_token == TokenType::LeftArrayBrace)
    {
        return array(lexer);
    }
    return lexer.next(TokenType::Value).value;
}

void doForEntireCommaSeperatedList(
    TokenType expected_first_token,
    TokenType expected_end_token,
    Lexer & lexer,
    std::function<void()> f)
{
    auto next_expected_token = expected_first_token;
    do
    {
        lexer.next(next_expected_token);
        if(lexer.peekNextTokenType() == expected_end_token &&
            next_expected_token == expected_first_token)
        {
            break;
        }
        f();
        next_expected_token = TokenType::Comma;
    } while(lexer.peekNextTokenType() == TokenType::Comma);
    lexer.next(expected_end_token);
}

Tree document(Lexer & lexer)
{
    auto t = Tree(Tree::Type::Document);
    doForEntireCommaSeperatedList(
        TokenType::LeftDocumentBrace,
        TokenType::RightDocumentBrace,
        lexer,
        [&t, &lexer]() {
            auto field = lexer.next(TokenType::StringValue);
            lexer.next(TokenType::Colon);
            t[field.value.get<std::string>()] = jsonExpression(lexer);
        });
    return t;
}

Tree array(Lexer & lexer)
{
    auto t = Tree(Tree::Type::Array);
    doForEntireCommaSeperatedList(
        TokenType::LeftArrayBrace,
        TokenType::RightArrayBrace,
        lexer,
        [&t, &lexer]() {
            t.pushBack(
                jsonExpression(lexer)
            );
        });
    return t;
}

}
}
}
}
