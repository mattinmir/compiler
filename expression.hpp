#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <string>
#include "enums.hpp"
#include "basics.hpp"

class Expression : public Immutable // SimpleExpression and MutableExpression inherit from this as they can both be expressions
{
public:
	Expression(){}
	
};


class Mutable : public Factor
{
private:
	std::string id;
	Expression* array_size;
public:
	Mutable(std::string _id, Expression* _array_size = NULL) 
			: id(_id), array_size(_array_size)
			{}
};


class MutableExpression : public Expression
{
private:
	Mutable* mut;
	AssignOp op;
	Expression* expr;
public:
	MutableExpression(Mutable* _mut, AssignOp _op, Expression* _expr = NULL) // expr NULL when op is increment or decrement
					: mut(_mut), op(_op), expr(_expr)
					{}
};


class ArgList
{
private:
	std::vector<Expression*> exprs;
public:
	ArgList(){}
	
	void add(Expression* expr)
	{
		exprs.push_back(expr);
	}
};

class Call : public Immutable
{
private:
	std::string func_id;
	ArgList* args;
public:
	Call(std::string _func_id, ArgList* _args) : func_id(_func_id), args(_args){}

};
#endif