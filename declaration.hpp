#ifndef DECLARATION_HPP
#define DECLARATION_HPP



#include <vector>
#include <map>
#include <stdexcept>
#include <iostream>

class Declaration 
{
private:

public:
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
    
    void print(std::ostream& stream) const
    {
    	for (unsigned i = 0; i < decls.size(); i++)
    	{
    		decls[i]->print(stream);
    	}
    }
    
};

#endif /* DECLARATION_HPP */
