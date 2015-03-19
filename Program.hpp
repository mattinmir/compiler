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
    
    void add_decl(Declaration* decl)
    {
    	decls.push_back(decl);
    }
        
   
};



enum struct TypeSpecifier
{
	int_t,
	float_t,
	double_t,
	char_t,
	bool_t
};

class VarDeclaration : public Declaration
{
private:
	TypeSpecifier type_specifier;
	VarDeclarationList var_decls
public:
	VarDeclaration(TypeSpecifier _type_specifier) : type_specifier(_type_specifier)
};

class VarDeclarationList
{
private:
	std::vector<VarDeclaration> var_decls;
	
public:
	VarDeclarationList()
    {}
	
    void add_var_decl(VarDeclaration var_decl)
    {
    	var_decls.push_back(var_decl);
    }
};

class FunDeclaration : public Declaration
{
	
};

#endif