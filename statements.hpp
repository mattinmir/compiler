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
	virtual void print(std::ostream& stream) = 0;
};

class ExpressionStmt : public Statement
{
private:
	Expression* expr;
public:
	ExpressionStmt(Expression* _expr = NULL) : expr(_expr)
	{}
	
	virtual void print(std::ostream& stream)
	{
		if(expr != NULL)
			expr->print(stream);
		stream << ";";
	}
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
	
	virtual void print(std::ostream& stream)
	{
		std::vector<Statement*>::iterator it;
		for (it = statements.begin(); it != statements.end(); it++)
			(*it)->print(stream);
	}
};

class IfStmt : public Statement
{
private:
	SimpleExpression* condition;
	Statement* if_body;
	Statement* else_body;
public:
	IfStmt(SimpleExpression* _condition, Statement* _if_body)
			: condition(_condition), if_body(_if_body)
			{}
	
	IfStmt(SimpleExpression* _condition, Statement* _if_body, Statement* _else_body)
		: condition(_condition), if_body(_if_body), else_body(_else_body) 
		{}
	
	virtual void print(std::ostream& stream)
	{
		stream << "if(";
		condition->print(stream);
		stream << "){";
		if_body->print(stream);
		stream << "}";
		if(else_body != NULL)
		{
			stream << "else{";
			else_body->print(stream);
			stream << "}";
		}
	}
};

class WhileStmt : public Statement
{
private:
	SimpleExpression* condition;
	Statement* body;
public:
	WhileStmt(SimpleExpression* _condition, Statement* _body) 
			: condition(_condition), body(_body)
			{}
	virtual void print(std::ostream& stream)
	{
		stream << "while(";
		condition->print(stream);
		stream << "){";
		body->print(stream);
		stream << "}";
	}
};

class ReturnStmt : public Statement
{
private:
	Expression* expr;
public:
	ReturnStmt(Expression* _expr = NULL) : expr(_expr) {}
	
	virtual void print(std::ostream& stream)
	{
		stream << "return ";
		expr->print(stream);
		stream << ";";
	}
};

class BreakStmt : public Statement
{
public:
	BreakStmt(){}
	
	virtual void print(std::ostream& stream)
	{
		stream << "break;";
	}
};

#endif