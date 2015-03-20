#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <string>

class Expression // SimpleExpression and MutableExpression inherit from thuis as they can both be expressions
{
public:
	Expression(){}
	
};


class Mutable
{
private:
	std::string id;
	Expression array_size;
public:
	Mutable(std::string _id, Expression _array_size = NULL) 
			: id(_id), array_size(_array_size)
			{}
};


class MutableExpression : public Expression
{
private:
	Mutable mut;
	AssignOp op;
	Expression expr;
public:
	MutableExpression(Mutable _mut, AssignOp _op, Expression _expr = NULL) // expr NULL when op is increment or decrement
					: mut(_mut), op(_op), expr(_expr)
					{}
};

#endif