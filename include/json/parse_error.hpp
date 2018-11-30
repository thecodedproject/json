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
