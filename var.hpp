#ifndef VAR_HPP
#define VAR_HPP

#include "declaration.hpp"
#include "expressions.hpp"
#include "enums.hpp"

#include <vector>
#include <map>
#include <stdexcept>
#include <iostream>




class VarDeclId
{
private:
	std::string id;
	int array_size;
public:
	// If the variable has no array size, its array size starts as null by deafult
	VarDeclId(std::string _id, int _array_size = NULL) : id(_id), array_size(_array_size) {}
};

class VarDeclInit : public Declaration
{
private:
	VarDeclId id;
	SimpleExpression value;
public:
	// If the variable has no initialisation, its value starts as null by deafult
	VarDeclInit(VarDeclId _id, SimpleExpression _value = NULL) : id(_id), value(_value) {}
};


class VarDeclInitList :public DeclarationList
{
private:
public:
	VarDeclInitList() {}
};



class VarDeclarations : public Declaration
{
private:
	TypeSpecifier type_specifier;
	VarDeclInitList var_decl_init_list;
public:
	VarDeclarations(TypeSpecifier _type_specifier) : type_specifier(_type_specifier) {}
};


#endif