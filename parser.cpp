#include "parser.h"
#include <QSharedPointer>


QSharedPointer<Node_Statement> Parser::parse(const QVector<Token> &inputTokens)
{
     QVector<Token>::const_iterator it = inputTokens.begin();

     QSharedPointer<Node_Statement>  tree;

     tree = stmt(inputTokens, it, tree->bIsExeption);

     return tree;

}

QSharedPointer<Node_Statement> Parser::stmt(const QVector<Token> &input, QVector<Token>::const_iterator &it, bool& bIsExeption)
{
    QSharedPointer<Node_Statement> statement(new Node_Statement());
     TokenType type = it->getType();
     if(type == TokenType::kNum  ||
        type == TokenType::kMin  ||
        type == TokenType::kMax  ||
        type == TokenType::kCell ||
        type == TokenType::kLb   ||
        type == TokenType::kInc  ||
        type == TokenType::kDec  ||
        type == TokenType::kPlus ||
        type == TokenType::kMinus)
    {
        QSharedPointer<Node_Expression> expressionNode = expr(input, it, bIsExeption);
        statement->setExpressionNode(expressionNode);
        return statement;
     }
     else if( type == TokenType::kEof)
     {
         statement->setExpressionNode(nullptr);
         return statement;
     }
     else
     {
         bIsExeption = true;
         statement->setExpressionNode(nullptr);
         return statement;
     }
}

QSharedPointer<Node_Expression> Parser::expr(const QVector<Token> &input, QVector<Token>::const_iterator &it, bool& bIsExeption)
{
   QSharedPointer<Node_Expression> expression(new Node_Expression());
    TokenType type = it->getType();
    if(type == TokenType::kNum  ||
       type == TokenType::kMin  ||
       type == TokenType::kMax  ||
       type == TokenType::kCell ||
       type == TokenType::kLb   ||
       type == TokenType::kInc  ||
       type == TokenType::kDec  ||
       type == TokenType::kPlus ||
       type == TokenType::kMinus)
    {
         QSharedPointer<Node_Multiplication> multiplicationNode = mult(input, it, bIsExeption);
         if(bIsExeption)
         {
             return nullptr;
         }
         else
         {
             expression->setMultNode(multiplicationNode);
             QSharedPointer<Node_ExpressionRight> exprRightNode = exprRight(input, ++it, bIsExeption);
             if(bIsExeption)
             {
                 return nullptr;
             }
             else
             {
                 expression->setRightExprNode(exprRightNode);
                 return expression;
             }
         }
     }
     else if(type == TokenType::kEof)
    {
        return nullptr;
    }
     else
     {
        bIsExeption = true;
        return nullptr;
     }
}

QSharedPointer<Node_Expression> Parser::exprRight(const QVector<Token> &input, QVector<Token>::const_iterator &it, bool& bisExption)
{

}
