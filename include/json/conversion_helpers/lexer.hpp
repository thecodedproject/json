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
