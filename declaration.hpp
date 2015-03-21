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


};


class DeclarationList
{
private:
	std::vector<Declaration*> decls;
public:
	DeclarationList()
	{}

    void add(Declaration* decl)
    {
    	decls.push_back(decl);
    }
    
    void print(std::ostream& dst) const
    {	
    	
    		dst << decls.size() << std::endl;
    } 
};




#endif /* DECLARATION_HPP */
