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
#pragma once

#include <functional>
#include <string>

#include <json/conversion_helpers/token.hpp>

namespace CodedProject
{
namespace Json
{
namespace ConversionHelpers
{

class Lexer
{
public:
    Lexer(std::string const& json_text);

    Token next();

    Token next(TokenType expected_token_type);

    Token currentToken();

    TokenType peekNextTokenType(int num_tokens_to_peek_forward=1);

private:

    void skipWhitespace();

    Token handleNextToken();

    Token checkTokenStringIsValidAndAdvanceCurrentChar(
        std::pair<Token, size_t> const& token_and_length);

    Token handleStringValue();

    Token handleNumberValue();

    void advanceCurrentCharButNotBeyondEnd(size_t amount_to_advance=1);

    void advanceCurrentCharButNotBeyondEndWhile(
        std::function<bool(char)> while_predicate);

    std::pair<int, int> lineAndColumnOfChar(std::string::const_iterator start_char) const;

    std::string json_text_ = {};
    std::string::const_iterator current_char_ = {};
    std::string::const_iterator last_token_start_char_ = {};
    Token current_token_ = {TokenType::StartOfFile};
};

}
}
}
