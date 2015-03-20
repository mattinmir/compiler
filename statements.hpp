#ifndef STATEMENTS_HPP
#define STATEMENTS_HPP

#include "var.hpp"
#include "enums.hpp"
#include "expression.hpp"
#include "simple_expressions.hpp"

#include <vector>

class Statement
{
public:
	Statement(){}
};

class ExpressionStmt : public Statement
{
private:
	Expression* expr;
public:
	ExpressionStmt(Expression _expr = NULL) : expr(_expr)
	{}
};

class CompoundStmt : public Statement
{
private:
	std::vector<Statement*> statements;
public:
	CompoundStmt(){}
	
	void add(Statement* statement)
	{
		statements.push_back(statement);
	}
};

class IfStmt : public Statement
{
private:
	SimpleExpression condition;
	Statement if_body;
	Statement else_body;
public:
	IfStmt(SimpleExpression _condition, Statement _if_body, Statement _else_body = NULL)
		: condition(_condition), if_body(_if_body), else_body(_else_body) 
		{}
};

class WhileStmt : public Statement
{
private:
	SimpleExpression condition;
	Statement body;
public:
	WhileStmt(SimpleExpression _condition, Statement _body) 
			: condition(_condition), body(_body)
			{}
	
	
};

class IterationStmt : public Statement
{
	
};

class ReturnStmt : public Statement
{
	
};

class BreakStmt : public Statement
{
	
};




#endif