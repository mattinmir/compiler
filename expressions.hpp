#ifndef EXPRESSIONS_HPP
#define EXPRESSIONS_HPP 

#include "enums.hpp"

#include <vector>
#include <map>
#include <stdexcept>
#include <iostream>

class SumExpression
{
	
};


class RelExpression
{
private:
	SumExpression left;
	Relop op;
	SumExpression right;
};

class UnaryRelExpression
{
private:
	bool state; //if state is false, logical 'NOT' the expression
	RelExpression rel_expr;
public:
	UnaryRelExpression(RelExpression _rel_expr) : rel_expr(_rel_expr), state(true){}
	
	void flip_state()
	{
		state = !state;
	}
};


class  AndExpression
{
private:
	std::vector<UnaryRelExpression*> unary_rel_exprs;
public:
	AndExpression(){}
	
	void add(UnaryRelExpression* unary_rel_expr)
	{
		unary_rel_exprs.push_back(unary_rel_expr);
	}
};

class SimpleExpression
{
private:
	std::vector<AndExpression*> and_exprs;
public:
	SimpleExpression(){}
	
	void add(AndExpression* and_expr)
	{
		and_exprs.push_back(and_expr);
	}
};


#endif