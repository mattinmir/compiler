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
	std::vector<Declaration*> decls;
public:
	DeclarationList()
    {}
    
    void add(Declaration* decl)
    {
    	decls.push_back(decl);
    }
        
   
};



enum class TypeSpecifier
{
	int_t, 
	float_t,
	double_t,
	char_t,
	bool_t
};

class VarDeclarations : public Declaration
{
private:
	TypeSpecifier type_specifier;
public:
	VarDeclarations(TypeSpecifier _type_specifier) : type_specifier(_type_specifier) {}
};

class VarDeclInitList :public DeclarationList
{
private:
	
public:
	VarDeclInitList()
    {}
};

class FunDeclaration : public Declaration
{
	
};

#endif