#ifndef BASICS_HPP
#define BASICS_HPP

#include <string>
#include <vector>
#include "enums.hpp"

class Factor
{
private:
	bool negated; // true if factor should be negated
public:
	Factor() : negated(false){}
	
	void negate()
	{
		negated = !negated;
	}
};

class Immutable : public Factor
{
	
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
	
	void add_op(Mulop* op)
	{
		ops.push_back(op);
	}
};


#endif