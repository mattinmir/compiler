#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <vector>
#include <map>
#include <stdexcept>
#include <iostream>

class Declaration
{
private:
	
public:
    virtual ~Declaration()
    {}
        
};


class DeclarationList
{
private:
	std::vector<Declaration*> declaration_list;
public:
	DeclarationList()
    {}
    
    void add_decl(Declaration* decl)
    {
    	declaration_list.push_back(decl);
    }
        
   
};


/*
typedef enum Type
{
	"int",
	"float",
	"double",
	"char",
	"bool"
};

class VarDeclaration : public Declaration
{
private:
	Type type_specifier;
};


class FunDeclaration : public Declaration
{
	
};
*/
#endif