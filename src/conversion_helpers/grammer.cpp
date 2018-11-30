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

Tree document(Lexer & lexer)
{
    auto t = Tree();
    auto next_expected_token = TokenType::LeftDocumentBrace;
    do
    {
        lexer.next(next_expected_token);
        auto field = lexer.next(TokenType::StringValue);
        lexer.next(TokenType::Colon);
        t[field.value.get<std::string>()] = jsonExpression(lexer);
        next_expected_token = TokenType::Comma;

    } while(lexer.peekNextTokenType() == TokenType::Comma);
    lexer.next(TokenType::RightDocumentBrace);
    return t;
}

Tree array(Lexer & lexer)
{
    auto t = Tree();
    auto next_expected_token = TokenType::LeftArrayBrace;
    do
    {
        lexer.next(next_expected_token);
        t.pushBack(
            jsonExpression(lexer)
        );
        next_expected_token = TokenType::Comma;
    } while(lexer.peekNextTokenType() == TokenType::Comma);
    lexer.next(TokenType::RightArrayBrace);
    return t;
}

}
}
}
}
