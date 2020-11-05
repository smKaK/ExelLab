#include "node.h"
#include <cmath>
#include <QDebug>
//Node statement//////////////////////////////////////////////////////////////////////

using cpp_int = boost::multiprecision::cpp_int;



Node_Statement::Node_Statement( ) : Node()
{

}


cpp_int Node_Statement::calculate(const Cell* parentCell)
{
    qDebug() << "calculate";
    return 1000;
    // return exprNode->calculate(parentCell);
}

void Node_Statement::setExpressionNode(const QSharedPointer<Node_Expression> &newExprNode)
{
    exprNode = newExprNode;
}




//Node_ExpresionRight////////////////////////////////////////////////////////////////


cpp_int  Node_ExpressionRight::calculate(const Cell* parentCell)
{
    cpp_int result(0);
    cpp_int multRes(multNode->calculate(parentCell));
    cpp_int exprRightNodeCalcRes = exprRightNode->calculate(parentCell);
    if(exprRightNode->GetOperator() == TokenType::kPlus)
    {
        result = multRes +  exprRightNodeCalcRes;
    }
    else if(exprRightNode->GetOperator() == TokenType::kMinus)
    {
        result = multRes - exprRightNodeCalcRes;
    }
    return result;
}

 TokenType Node_ExpressionRight::GetOperator()
{
    return op;
}

//Node Expression/////////////////////////////////////////////////////////////////////
cpp_int Node_Expression::calculate(const Cell* parentCell)
{
    cpp_int result(0);
    cpp_int multRes(multNode->calculate(parentCell));
    cpp_int exprRightNodeCalcRes = exprRightNode->calculate(parentCell);
    if(exprRightNode->GetOperator() == TokenType::kPlus)
    {
        result = multRes + exprRightNodeCalcRes;
    }
    else if(exprRightNode->GetOperator() == TokenType::kMinus)
    {
        result = multRes - exprRightNodeCalcRes;
    }
    return result;
}

//Node_Multiplication/////////////////////////////////////////////////////////////////
cpp_int Node_Multiplication::calculate(const Cell* parentCell)
{
    cpp_int result(0);
    cpp_int powRes(powerNode->calculate(parentCell));
    cpp_int multRightNodeCalcRes = multRightNode->calculate(parentCell) ;
    if(multRightNode->GetOperator() == TokenType::kStar)
    {
        result = powRes * multRightNodeCalcRes;

    } else if(multRightNode->GetOperator() == TokenType::kDiv)
    {
        result = powRes / multRightNodeCalcRes;
    }
    return result ;
}

//Node_MultiplicationRight////////////////////////////////////////////////////////////

cpp_int Node_MultiplicationRight::calculate(const Cell* parentCell)
{
    cpp_int result(0);
    cpp_int powRes =  powerNode->calculate(parentCell);
    cpp_int multRightNodeCalcRes =  multRightNode->calculate(parentCell);
    if(multRightNode->GetOperator() == TokenType::kStar)
    {
        result = powRes * multRightNodeCalcRes;
    } else if(multRightNode->GetOperator() == TokenType::kDiv)
    {
        result = powRes / multRightNodeCalcRes;
    }
    return result;
}

TokenType Node_MultiplicationRight::GetOperator() const
{
    return op;
}

//Node_Power//////////////////////////////////////////////////////////////////////////

cpp_int Node_Power::power(cpp_int base, cpp_int pow) const
{
    if (pow == 0)
        {
            return 1;
        }

        cpp_int temp = 1;
        while (pow != 1)
        {
            if (pow % 2 == 0)
            {
                pow /= 2;
                base *= base;
            }
            else
            {
                pow -= 1;
                temp *= base;
            }
        }
       return   temp * base;

}

cpp_int Node_Power::calculate(const Cell* parentCell)
{
    cpp_int result(0);
    cpp_int termRes(termNode->calculate(parentCell) );
    cpp_int powerRightNodeCalcRes = powerRightNode->calculate(parentCell) ;
    if(powerRightNode->GetOperator() == TokenType::kPow)
    {
        result = power(termRes,  powerRightNodeCalcRes);
    }
    return result;
}

//Node_PowerRight////////////////////////////////////////////////////////////////////
 cpp_int Node_PowerRight::power(cpp_int base, cpp_int pow) const
{
    if (pow == 0)
        {
            return 1;
        }

        cpp_int temp = 1;
        while (pow != 1)
        {
            if (pow % 2 == 0)
            {
                pow /= 2;
                base *= base;
            }
            else
            {
                pow -= 1;
                temp *= base;
            }
        }
        return base * temp;
}

cpp_int Node_PowerRight::calculate(const Cell* parentCell)
{
    cpp_int result(0);
    cpp_int termRes(termNode->calculate(parentCell));
    cpp_int powerRightNodeCalcRes =  powerRightNode->calculate(parentCell);
    if(powerRightNode->GetOperator() == TokenType::kPow)
    {
        result = power(termRes, powerRightNodeCalcRes);
    }
    return result;
}

TokenType Node_PowerRight::GetOperator() const
{
    return op;
}

//Node_Number///////////////////////////////////////////////////////////////////////
cpp_int Node_Number::calculate(const Cell* parentCell)
{
    return (numLexema).toInt();
}

//Node_CellLink/////////////////////////////////////////////////////////////////////
cpp_int Node_CellLink::calculate(const Cell* parentCell)
{
    return 1;
}

//Node_Term//////////////////////////////////////////////////////////////////////////
cpp_int Node_Term::calculate(const Cell* parentCell)
{
    return 1;
}
