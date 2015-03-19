#ifndef STATEMENTS_HPP
#define STATEMENTS_HPP

#include "var.hpp"
#include "enums.hpp"

class Statement
{

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

class Expression // SimpleExpression and MutableExpression inherit from thuis as they can both be expressions
{
private:
public:
	Expression(){}
	
};

class ExpressionStmt : public Statement
{
private:
	Expression expr;
public:
	ExpressionStmt(Expression _expr = NULL) : expr(_expr)
	{}
};

#endif