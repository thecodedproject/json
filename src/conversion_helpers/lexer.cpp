#include <json/conversion_helpers/lexer.hpp>

#include <functional>
#include <map>

#include <json/conversion_helpers/to_json_text.hpp>

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

Token Lexer::next(TokenType expectedTokenType)
{
    auto actual_token = next();
    if(expectedTokenType != actual_token.type)
    {
        auto last_token_start_column = 1;
        auto last_token_start_line = 1;
        for(auto it=std::cbegin(json_text_);
            it!=last_token_start_char_;
            ++it)
        {
            if(*it == '\n')
            {
                last_token_start_column = 1;
                ++last_token_start_line;
            }
            else
            {
                ++last_token_start_column;
            }

        }

        throw Json::ParseError(
            tokenAsJsonText(current_token_),
            expectedTokenType,
            last_token_start_line,
            last_token_start_column);
    }

    return actual_token;
}

Token Lexer::currentToken()
{
    return current_token_;
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
    auto a = std::bind(&Lexer::advanceCurrentCharAndReturnToken, this, Token{TokenType::LeftArrayBrace});

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
        return advanceCurrentCharAndReturnToken(
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

Token Lexer::advanceCurrentCharAndReturnToken(
    std::pair<Token, size_t> const& token_and_length)
{
    std::advance(current_char_, token_and_length.second);
    return token_and_length.first;
}

Token Lexer::handleStringValue()
{
    ++current_char_;

    auto string_start_char = current_char_;

    while(*current_char_!='"')
    {
        ++current_char_;
    }

    auto value_string = std::string(string_start_char, current_char_);

    return advanceCurrentCharAndReturnToken(
        {{TokenType::StringValue, value_string},1});
}

Token Lexer::handleNumberValue()
{
    auto value_start = current_char_;

    while(std::string("-0123456789.").find(*current_char_)!=std::string::npos)
    {
        ++current_char_;
    }

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

std::string Lexer::tokenAsJsonText(Token const& token) const
{
    switch(token.type)
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
        case TokenType::Eof:
            return "Eof";
        case TokenType::StartOfFile:
            return "StartOfFile";
        case TokenType::StringValue:
        case TokenType::Value:
            return toJsonText(token.value);
    }
}

}
}
}
