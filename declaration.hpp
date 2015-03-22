#ifndef DECLARATION_HPP
#define DECLARATION_HPP



#include <vector>
#include <iterator>
#include <stdexcept>
#include <iostream>

class Declaration 
{
public:
	Declaration(){}

	virtual void print(std::ostream& stream){}
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
    
};

#endif /* DECLARATION_HPP */
