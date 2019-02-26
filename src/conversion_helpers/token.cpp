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
#include <json/conversion_helpers/token.hpp>

namespace CodedProject
{
namespace Json
{
namespace ConversionHelpers
{

bool Token::operator==(Token const& rhs) const
{
    return type == rhs.type &&
        value == rhs.value;
}

std::string toString(TokenType const& type)
{
    switch(type)
    {
        case TokenType::LeftArrayBrace:
            return "TokenType::LeftArrayBrace";
        case TokenType::RightArrayBrace:
            return "TokenType::RightArrayBrace";
        case TokenType::LeftDocumentBrace:
            return "TokenType::LeftDocumentBrace";
        case TokenType::RightDocumentBrace:
            return "TokenType::RightDocumentBrace";
        case TokenType::Colon:
            return "TokenType::Colon";
        case TokenType::Comma:
            return "TokenType::Comma";
        case TokenType::Value:
            return "TokenType::Value";
        case TokenType::StringValue:
            return "TokenType::StringValue";
        case TokenType::Eof:
            return "TokenType::Eof";
        case TokenType::StartOfFile:
            return "TokenType::StartOfFile";
    }
}

std::string toString(Token const& token)
{
    if(token.type == TokenType::Value ||
        token.type == TokenType::StringValue)
    {
        return "Token("
            + toString(token.type)
            + ", "
            + toDebugString(token.value)
            + ")";
    }
    else
    {
        return "Token("
            + toString(token.type)
            + ")";

    }
}

}
}
}
