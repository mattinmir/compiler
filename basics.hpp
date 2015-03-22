#ifndef BASICS_HPP
#define BASICS_HPP


#include <vector>
#include "enums.hpp"
#include "declaration.hpp"

class Factor
{
protected:
	bool negated; // true if factor should be negated
public:
	Factor() : negated(false){}
	
	void negate()
	{
		negated = !negated;
	}
	virtual void print(std::ostream& stream) = 0;
	virtual void arm(std::ostream& stream, std::map<std::string, unsigned int> &vars, unsigned int &reg) {}
	
};

class Immutable : public Factor
{
public:
	virtual void print(std::ostream& stream) = 0;
	virtual void arm(std::ostream& stream, std::map<std::string, unsigned int> &vars, unsigned int &reg) {}
};


class Term 
{

private:
	std::vector<Factor*> factors; 
	std::vector<Mulop> ops; // ops[0] goes between terms[0] and terms[1]
public:
	Term(){}
	
	void add_factor(Factor* factor)
	{
		factors.push_back(factor);
	}
	
	void add_op(Mulop op)
	{
		ops.push_back(op);
	}
	
	void print(std::ostream& stream)
	{
		std::vector<Factor*>::iterator factor_it;
		std::vector<Mulop>::iterator op_it;
		for (factor_it = factors.begin(), op_it = ops.begin(); factor_it != factors.end(); factor_it++, op_it++)
		{
			(*factor_it)->print(stream);
			if(op_it != ops.end())
			{
				switch(*op_it)
				{
				case Mulop::null:
					break;
				case Mulop::mul:
					stream << "*";
					break;
				case Mulop::div:
					stream << "/";
					break;
				case Mulop::modulo:
					stream << "%";
					break;
				
				}
			}
		}
	}
	
	void arm(std::ostream& stream, std::map<std::string, unsigned int> &vars, unsigned int &reg)
	{
		factors[0]->arm(stream, vars, reg);
	}
};


#endif