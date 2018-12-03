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
