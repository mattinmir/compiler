#ifndef EXPRESSIONS_HPP
#define EXPRESSIONS_HPP 

#include <vector>
#include <map>
#include <stdexcept>
#include <iostream>



class  AndExpression
{
private:
	std::vector<UnaryRelExpression*> unary_rel_exprs;
public:
	AndExpression(){}
};

class SimpleExpression : 
{
private:
	std::vector<AndExpression*> and_exprs;
public:
	SimpleExpression(){}
};


#endif