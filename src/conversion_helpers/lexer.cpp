#include <json/conversion_helpers/lexer.hpp>

#include <functional>
#include <map>

#include <iostream>

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
    current_token_ = handleNextToken();
    return current_token_;
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
        {{TokenType::Value, value_string},1});
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

}
}
}
