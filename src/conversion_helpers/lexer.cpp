#include <json/conversion_helpers/lexer.hpp>

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
    if(current_char_ == std::end(json_text_))
    {
        return {TokenType::Eof};
    }
    if(*current_char_ == '[')
    {
        return advanceCurrentCharAndReturnToken(
            {TokenType::LeftArrayBrace});
    }
    else if(*current_char_ == ']')
    {
        return advanceCurrentCharAndReturnToken(
            {TokenType::RightArrayBrace});
    }
    else
    {

        if(*current_char_ == '"')
        {
            ++current_char_;

            auto string_start_char = current_char_;

            while(*current_char_!='"')
            {
                ++current_char_;
            }

            auto value_string = std::string(string_start_char, current_char_);

            return advanceCurrentCharAndReturnToken(
                {TokenType::Value, value_string});
        }
        else if(*current_char_ == 't')
        {
            return advanceCurrentCharAndReturnToken(
                {TokenType::Value, true},
                4);
        }
        else if(*current_char_ == 'f')
        {
            return advanceCurrentCharAndReturnToken(
                {TokenType::Value, false},
                5);
        }
        else if(*current_char_ == 'n')
        {
            return advanceCurrentCharAndReturnToken(
                {TokenType::Value, {}},
                4);
        }
        else
        {

            auto value_start = current_char_;

            while(std::string("0123456789.").find(*current_char_)!=std::string::npos)
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

Token Lexer::advanceCurrentCharAndReturnToken(
    Token const& token,
    size_t const amount_to_advance)
{
    std::advance(current_char_, amount_to_advance);
    return token;
}

}
}
}
