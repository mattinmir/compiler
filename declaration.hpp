#ifndef DECLARATION_HPP
#define DECLARATION_HPP

#include <vector>
#include <iterator>
#include <stdexcept>
#include <iostream>
#include <map>

static bool regs[13]; // false = empty, true = full
static unsigned int address = 0;

class Declaration 
{
public:
	Declaration(){}

	virtual void print(std::ostream& stream) {}
	virtual void arm(std::ostream& stream, std::map<std::string, unsigned int> &vars, unsigned int &reg){}
};


class DeclarationList
{
protected:
	std::vector<Declaration*> decls;
public:
	DeclarationList()
	{}
	
    void add(Declaration* decl)
    {
    	decls.push_back(decl);
    }
    
    void print(std::ostream& stream) 
    {
    	std::vector<Declaration*>::iterator it;
		for (it = decls.begin(); it != decls.end(); it++)
			(*it)->print(stream);
    }
    
    void arm(std::ostream& stream, std::map<std::string, unsigned int> &vars, unsigned int &reg)
    {
    	std::vector<Declaration*>::iterator it;
		for (it = decls.begin(); it != decls.end(); it++)
			(*it)->arm(stream, vars, reg);
    }
    
};

#endif /* DECLARATION_HPP */
