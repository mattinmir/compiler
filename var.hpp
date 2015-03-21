#ifndef VAR_HPP
#define VAR_HPP

#include "declaration.hpp"
#include "simple_expressions.hpp"
#include "enums.hpp"
#include "statements.hpp"

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
	VarDeclId(std::string _id, int _array_size = -1) : id(_id), array_size(_array_size) {}
	
	void print(std::ostream& stream)
	{
			stream << id;
			
			if (array_size != -1)
				stream << "[" << array_size << "]";
	}
};

class VarDeclInit : public Declaration
{
private:
	VarDeclId* id;
	SimpleExpression* value;
public:
	// If the variable has no initialisation, its value starts as null by default
	VarDeclInit(VarDeclId* _id, SimpleExpression* _value = NULL) : id(_id), value(_value) {}
	
	void print(std::ostream& stream)
	{
		id->print(stream);
		//value->print(stream);
	}
};


class VarDeclInitList : public DeclarationList
{/*
private:
	std::vector<VarDeclInit*> vardeclinits;
public:
	VarDeclInitList() {}
	
	void add(VarDeclInit* vardeclinit)
	{
		vardeclinits.push_back(vardeclinit);
		
	}
	
	virtual void print(std::ostream& stream)
	{
		for (unsigned i = 0; i < vardeclinits.size(); i++)
			vardeclinits[i]->print(stream);
	}
	*/
public:
	VarDeclInitList(){}
};



class VarDeclarations :  public Declaration, public Statement
{
private:
	TypeSpecifier type_specifier;
	VarDeclInitList* var_decl_init_list;
public:
	VarDeclarations(TypeSpecifier _type_specifier) : type_specifier(_type_specifier) {}
	
	virtual void print(std::ostream& stream)
	{
			switch(type_specifier)
			{
			case TypeSpecifier::int_t:
				stream << "int";
				break;
			case TypeSpecifier::float_t:
				stream << "float";
				break;
			case TypeSpecifier::double_t:
				stream << "double";
				break;
			case TypeSpecifier::char_t:
				stream << "char";
				break;
			case TypeSpecifier::bool_t:
				stream << "bool";
				break;
			}
			stream << " ";
			var_decl_init_list->print(stream);
	}
};


#endif