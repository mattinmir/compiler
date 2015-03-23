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
	
	void arm(std::ostream& stream, std::map<std::string, unsigned int> &vars, unsigned int &reg)
	{
		if (vars.find(id) == vars.end())
		{
			std::cout << "Error:" << id << " has not been declared" << std::endl; 
		}
		else
		{
			for (int i = 0; i < 13 ; i++)
			{
				if(!regs[i])
				{
					reg = i;
					regs[i] = true;
					break;
				}
			}
			
			unsigned int regaddr;
			for (int i = 0; i < 13 ; i++)
			{
				if(!regs[i])
				{
					regaddr = i;
					regs[i] = true;
					break;
				}
			}
			stream << "MOV R" << regaddr << ", #" << vars[id] << std::endl;
			stream << "LDR R" << reg << ", [R" << regaddr << "]" << std::endl;
		}
	}
	
	std::string get_id()
	{
		return id;
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
	
	 void arm(std::ostream& stream, std::map<std::string, unsigned int> &vars, unsigned int &reg)
	 {

		mut->arm(stream, vars, reg);
		unsigned int mutreg = reg;
		regs[mutreg] = true;

		expr->arm(stream, vars, reg);
		unsigned int exprreg = reg;
		regs[exprreg] = true;
		
		unsigned int regaddr;
		for (int i = 0; i < 13 ; i++)
		{
			if(!regs[i])
			{
				regaddr = i;
				regs[i] = true;
				break;
			}
		}
		stream << "MOV R" << regaddr << ", #" << vars[mut->get_id()] << std::endl;
		switch(op)
		{
		case AssignOp::null:
			break;
		case AssignOp::assign:
			stream << "MOV R" << mutreg << ", R" << exprreg << std::endl << "STR R" << mutreg << ", [R" << regaddr << "]" << std::endl;
			break;
		case AssignOp::add_assign: 
			stream << "ADD R" << mutreg << ", R" << mutreg << ", R" << exprreg << std::endl << "STR R" << mutreg << ", [R" << regaddr << "]" << std::endl;
			break;
		case AssignOp::sub_assign:
			stream << "SUB R" << mutreg << ", R" << mutreg << ", R" << exprreg << std::endl << "STR R" << mutreg << ", [R" << regaddr << "]" << std::endl;
			break;
		case AssignOp::mul_assign:
			stream << "MUL R" << mutreg << ", R" << mutreg << ", R" << exprreg << std::endl << "STR R" << mutreg << ", [R" << regaddr << "]" << std::endl;
			break;
		case AssignOp::div_assign:
			stream << "DIV R" << mutreg << ", R" << mutreg << ", R" << exprreg << std::endl << "STR R" << mutreg << ", [R" << regaddr << "]" << std::endl;
			break;
		case AssignOp::bitwise_and_assign:
			stream << "AND R" << mutreg << ", R" << mutreg << ", R" << exprreg << std::endl << "STR R" << mutreg << ", [R" << regaddr << "]" << std::endl;
			break;
		case AssignOp::bitwise_or_assign:
			stream << "ORR R" << mutreg << ", R" << mutreg << ", R" << exprreg << std::endl << "STR R" << mutreg << ", [R" << regaddr << "]" << std::endl;
			break;
		case AssignOp::increment:
			stream << "ADD R" << mutreg << ", R" << mutreg << ", #1" << std::endl << "STR R" << mutreg << ", [R" << regaddr << "]"<< std::endl;
			break;
		case AssignOp::decrement:
			stream << "SUB R" << mutreg << ", R" << mutreg << ", #1" << std::endl << "STR R" << mutreg << ", [R" << regaddr << "]" << std::endl;
			break;
		}
		
		regs[regaddr] = false;
		regs[exprreg] = false;
		regs[mutreg] = false;
		regs[reg] = false;
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
	
	void print(std::ostream& stream)
	{
		std::vector<Expression*>::iterator it;
		for (it = exprs.begin(); it != exprs.end(); it++)
			(*it)->print(stream);
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
	{
		stream << func_id << "(";
		args->print(stream);
		stream << ");";
	}
};
#endif