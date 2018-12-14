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

#include <stdexcept>
#include <string>

#include <json/conversion_helpers/token_type.hpp>

namespace CodedProject
{
namespace Json
{

class ParseError : public std::runtime_error
{
public:
    static ParseError expectedToken(
        std::string const& actual_token_string,
        ConversionHelpers::TokenType const expected_token_type,
        std::pair<int,int> const error_line_and_column)
    {
        return ParseError(
            "Expected " +
            toString(expected_token_type) + " but got token"
            " '" + actual_token_string + "'",
            error_line_and_column);
    }

    static ParseError invalidToken(
        std::string actual_token_string,
        std::pair<int,int> const error_line_and_column)
    {
        return ParseError(
            "Invalid token '" +
            actual_token_string + "'",
            error_line_and_column);

    }

    static ParseError unterminatedString(
        std::string string_value,
        std::pair<int,int> const error_line_and_column)
    {
        auto string_to_print = string_value;
        if(string_value.size() > 5)
            string_to_print = string_value.substr(0, 5) + "...";
        return ParseError(
            "Unterminated string literal '" +
            string_to_print + "' starting",
            error_line_and_column);

    }

private:

    ParseError(
        std::string const& error_string,
        std::pair<int,int> const error_line_and_column)
    : std::runtime_error(
        "Parse error: " +
        error_string +
        " at line " +
        std::to_string(error_line_and_column.first) +
        ", column " + std::to_string(error_line_and_column.second))
    {
    }
};

}
}
