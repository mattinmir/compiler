#ifndef SIMPLE_EXPRESSIONS_HPP
#define SIMPLE_EXPRESSIONS_HPP

#include "enums.hpp"
#include "expression.hpp"
#include "basics.hpp"

#include <vector>
#include <map>
#include <stdexcept>
#include <iostream>





class SumExpression
{
private:
	std::vector<Term*> terms; 
	std::vector<Sumop> ops; // ops[0] goes between terms[0] and terms[1]
public:
	SumExpression(){}
	
	void add_term(Term* term)
	{
		terms.push_back(term);
	}
	
	void add_op(Sumop* op)
	{
		ops.push_back(op);
	}
	
};


class RelExpression
{
private:
	SumExpression* left;
	Relop op;
	SumExpression* right;
public:
	RelExpression(SumExpression* _left, Relop _op, SumExpression* _right)
				: left(_left), op(_op), right(_right) {}
};

class UnaryRelExpression
{
private:
	bool negated; //if negated is true, logical 'NOT' the expression
	RelExpression* rel_expr;
public:
	UnaryRelExpression(RelExpression* _rel_expr) : rel_expr(_rel_expr), negated(false){}
	
	void logical_not()
	{
		negated = !negated;
	}
};


class  AndExpression
{
private:
	std::vector<UnaryRelExpression*> unary_rel_exprs; // Everything in the vector should be AND'd together
public:
	AndExpression(){}
	
	void add(UnaryRelExpression* unary_rel_expr)
	{
		unary_rel_exprs.push_back(unary_rel_expr);
	}
};

class SimpleExpression : public Expression
{
private:
	std::vector<AndExpression*> and_exprs; // Everything in the vector should be OR'd together
public:
	SimpleExpression(){}
	
	void add(AndExpression* and_expr)
	{
		and_exprs.push_back(and_expr);
	}
};


#endif
