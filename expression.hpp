#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <string>
#include "enums.hpp"
#include "basics.hpp"
#include "declaration.hpp"

class Expression : public Immutable // SimpleExpression and MutableExpression inherit from this as they can both be expressions
{
public:
	Expression(){}
	
	virtual void print(std::ostream& stream) = 0;
};


class Mutable : public Factor
{
private:
	std::string id;
	Expression* array_size;
public:
	Mutable(std::string _id) : id(_id){}
	Mutable(std::string _id, Expression* _array_size) : id(_id), array_size(_array_size){}
	
	void print(std::ostream& stream)
	{
		if(negated)
			stream << "-";
		stream << id;
		if(array_size != NULL)
			array_size->print(stream);
	}
};


class MutableExpression : public Expression
{
private:
	Mutable* mut;
	AssignOp op;
	Expression* expr;
public:
	MutableExpression(Mutable* _mut, AssignOp _op) : mut(_mut), op(_op)	{}// expr NULL when op is increment or decrement
	MutableExpression(Mutable* _mut, AssignOp _op, Expression* _expr ) : mut(_mut), op(_op), expr(_expr){}
	
	void print(std::ostream& stream)
	{
		mut->print(stream);
		
		switch(op)
		{
		case AssignOp::null:
			break;
		case AssignOp::assign:
			stream << "=";
			break;
		case AssignOp::add_assign:
			stream << "+=";
			break;
		case AssignOp::sub_assign:
			stream << "-=";
			break;
		case AssignOp::mul_assign:
			stream << "*=";
			break;
		case AssignOp::div_assign:
			stream << "/=";
			break;
		case AssignOp::bitwise_and_assign:
			stream << "&=";
			break;
		case AssignOp::bitwise_or_assign:
			stream << "|=";
			break;
		case AssignOp::increment:
			stream << "++";
			break;
		case AssignOp::decrement:
			stream << "--";
			break;
		}		
		
		if (expr != NULL)
			expr->print(stream);
	}
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
	void print(std::ostream& stream)
		{}
};
#endif