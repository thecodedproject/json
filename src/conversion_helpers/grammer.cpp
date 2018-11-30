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

void doUntilNextComma(
    TokenType expected_first_token,
    Lexer & lexer,
    std::function<void()> f)
{
    auto next_expected_token = expected_first_token;
    do
    {
        lexer.next(next_expected_token);
        f();
        next_expected_token = TokenType::Comma;
    } while(lexer.peekNextTokenType() == TokenType::Comma);
}

Tree document(Lexer & lexer)
{
    auto t = Tree();
    doUntilNextComma(
        TokenType::LeftDocumentBrace,
        lexer,
        [&t, &lexer]() {
            auto field = lexer.next(TokenType::StringValue);
            lexer.next(TokenType::Colon);
            t[field.value.get<std::string>()] = jsonExpression(lexer);
        });
    lexer.next(TokenType::RightDocumentBrace);
    return t;
}

Tree array(Lexer & lexer)
{
    auto t = Tree();
    doUntilNextComma(
        TokenType::LeftArrayBrace,
        lexer,
        [&t, &lexer]() {
            t.pushBack(
                jsonExpression(lexer)
            );
        });
    lexer.next(TokenType::RightArrayBrace);
    return t;
}

}
}
}
}
