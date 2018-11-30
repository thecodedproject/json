#include <json/conversion.hpp>

#include <json/builder.hpp>
#include <json/conversion_helpers/lexer.hpp>

#include <iostream>

namespace CodedProject
{
namespace Json
{

//*** Grammer functions (experiement)

// ---

//json_expression: document | array | VALUE | STRING_VALUE

//document: LEFT_DOCUMENT_BRACE STRING_VALUE COLON json_expression (COMMA STRING_VALUE json_expression)* RIGHT_DOCUMENT_BRACE

//array: LEFT_ARRAY_BRACE json_expression (COMMA expression_list)* RIGHT_ARRAY_BRACE

//array_list:

//document_list:





//json_expression: document | array | VALUE | STRING_VALUE

//document: LEFT_DOCUMENT_BRACE expression_list RIGHT_DOCUMENT_BRACE

//array: LEFT_ARRAY_BRACE expression_list RIGHT_ARRAY_BRACE

//expression_list: expression | expression COMMA expression_list

//expression: field_value_expression | json_expression

//field_value_expression: STRING_VALUE COLON json_expression


/*
void jsonExpression(Builder & builder, Lexer & lexer, Token const& current_token);

void fieldValueExpression(Builder & builder, Lexer & lexer, Token const& current_token)
{
    auto field = current_token.value.get<std::string>();

    lexer.next(); // TokenType::Colon

    document_token = lexer.next();

    builder.append(field, document_token.value);
}

Tree expressionList(Lexer & lexer, Token const& current_token)
{
    return tree;
}

Tree array(Lexer & lexer, Token const& current_token)
{
    auto array_token = lexer.next(); // LEFT_ARRAY_BRACE
    auto tree = expressionList(lexer, array_token);
    lexer.next() // RIGHT_ARRAY_BRACE
    return tree;
}

Tree document(Lexer & lexer, Token const& current_token)
{
    auto document_token = lexer.next(); // LEFT_DOCUMENT_BRACE
    auto tree = expressionList(lexer, document_token);
    lexer.next() // RIGHT_DOCUMENT_BRACE
    return tree;
}

Tree jsonExpression(Builder & builder, Lexer & lexer, Token const& current_token)
{
    if(current_token.type == TokenType::LeftArrayBrace)
    {
        return array(builder, lexer, current_token);
    }
    else if(current_token.type == TokenType::LeftDocumentBrace)
    {
        return document(builder, lexer, current_token);
    }
    else
    {
        return current_token.value;
    }
}

*/
//*** End Grammer functions (experiement)

Tree fromString(std::string const& json_string)
{
    using ConversionHelpers::TokenType;
    auto lexer = ConversionHelpers::Lexer(json_string);

    auto builder = Json::Builder();

    auto token = lexer.next();
    while(token.type != TokenType::Eof)
    {
        //std::cout << ConversionHelpers::toString(token) << std::endl;

        if(token.type == TokenType::Value || token.type == TokenType::StringValue)
        {
            auto field = token.value.get<std::string>();
            lexer.next();
            token = lexer.next();

            if(token.type == TokenType::LeftArrayBrace)
            {
                auto & sub = builder.openSubtree(field);

                auto array_token = lexer.next();
                while(array_token.type != TokenType::RightArrayBrace)
                {
                    sub.pushBack(array_token.value);
                    array_token = lexer.next();
                    if(array_token.type == TokenType::Comma)
                        array_token = lexer.next();
                }
                sub.closeSubtree();
            }
            else if(token.type == TokenType::LeftDocumentBrace)
            {
                auto & sub = builder.openSubtree(field);

                auto document_token = lexer.next();
                while(document_token.type != TokenType::RightDocumentBrace)
                {
                    auto field = document_token.value.get<std::string>();
                    lexer.next();
                    document_token = lexer.next();

                    sub.append(field, document_token.value);

                    document_token = lexer.next();

                    if(document_token.type == TokenType::Comma)
                        document_token = lexer.next();

                }
                sub.closeSubtree();
            }
            else
            {
                builder.append(field, token.value);
            }
        }

        token = lexer.next();
    }

    return builder.getTree();
}

}
}
