#ifndef SIMPLE_EXPRESSIONS_HPP
#define SIMPLE_EXPRESSIONS_HPP

#include "enums.hpp"
#include "expression.hpp"
#include "basics.hpp"

#include <vector>
#include <iterator>
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
	
	void add_op(Sumop op)
	{
		ops.push_back(op);
	}
	void print(std::ostream& stream)
	{
		std::vector<Term*>::iterator term_it;
		std::vector<Sumop>::iterator op_it;
		for (term_it = terms.begin(), op_it = ops.begin(); term_it != terms.end(); term_it++, op_it++)
		{
			(*term_it)->print(stream);
			if(op_it != ops.end())
			{
				switch(*op_it)
				{
				case Sumop::null:
					break;
				case Sumop::add:
					stream << "+";
					break;
				case Sumop::sub:
					stream << "-";
					break;
				}
			}
				
		}
	}
};


class RelExpression
{
private:
	SumExpression* left;
	Relop op;
	SumExpression* right;
public:
	RelExpression(SumExpression* _left, Relop _op = Relop::null, SumExpression* _right = NULL)
				: left(_left), op(_op), right(_right) {}
	
	void print(std::ostream& stream)
	{		
		left->print(stream);
		
		switch(op)
		{
		case Relop::null:
			break;
		case Relop::lt_equal_to:
			stream << "<=";
			break;
		case Relop::less_than:
			stream << "<";
			break;
		case Relop::greater_than:
			stream << ">";
			break;
		case Relop::gt_equal_to:
			stream << ">=";
			break;
		case Relop::equal_to:
			stream << "==";
			break;
		case Relop::not_equal_to:
			stream << "!=";
			break;
		}
		
		if (op != Relop::null)
			right->print(stream);
	}
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
	
	void print(std::ostream& stream)
	{
		if(negated)
			stream << "-";
		rel_expr->print(stream);
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
	
	void print(std::ostream& stream)
	{
		std::vector<UnaryRelExpression*>::iterator it;
		for (it = unary_rel_exprs.begin(); it != unary_rel_exprs.end(); it++)
			(*it)->print(stream);
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
	
	void print(std::ostream& stream)
	{
		std::vector<AndExpression*>::iterator it;
		for (it = and_exprs.begin(); it != and_exprs.end(); it++)
			(*it)->print(stream);
	}
};


#endif
