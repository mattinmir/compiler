#ifndef VAR_HPP
#define VAR_HPP

#include "declaration.hpp"
#include "simple_expressions.hpp"
#include "enums.hpp"
#include "statements.hpp"

#include <vector>
#include <iterator>
#include <iostream>




class VarDeclId
{
private:
	std::string id;

public:
	// If the variable has no array size, its array size starts as null by deafult
	VarDeclId(std::string _id) : id(_id) {}

	
	void print(std::ostream& stream)
	{
			stream << "hello"; // id;
	}
};

class VarDeclInit : public Declaration
{
private:
	VarDeclId* id;
	SimpleExpression* value;
public:

	VarDeclInit(VarDeclId* _id) : id(_id) {}
	VarDeclInit(VarDeclId* _id, SimpleExpression* _value) : id(_id), value(_value) {}
	
	void print(std::ostream& stream)
	{
		if(id != NULL)
		{
			id->print(stream);
		}
		//value->print(stream);
	}
};



class VarDeclInitList //: public DeclarationList
{
private:
	std::vector<VarDeclInit*> vardeclinits;
public:
	
	void add(VarDeclInit* vardeclinit)
	{
		vardeclinits.push_back(vardeclinit);
		std::cout << "added to list, Size is " << vardeclinits.size() << std::endl;
		
	}
	
	void print(std::ostream& stream)
	{
		std::cout << "printing VarDeclList" << std::endl;

		for (int i = 0; i < vardeclinits.size(); i++)
		{
			std::cout << "got past it" << std::endl;
			if(vardeclinits[i] == NULL)
			{
				std::cout << "vardecl is null" << std::endl;
			}
				vardeclinits[i]->print(stream);
		}


		/*std::vector<VarDeclInit*>::iterator it;
		for (it = vardeclinits.begin(); it != vardeclinits.end(); it++)
		{
			std::cout << *it << std::endl;
			(*it)->print(stream);
		}*/
	}
	
public:
	VarDeclInitList(){}
};




class VarDeclarations :  public Declaration
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
			if(var_decl_init_list == NULL)
				var_decl_init_list->print(stream);
			
	}
};


class LocalDeclarations : public Statement
{
private:
	VarDeclarations* var_declaration;
public:
	LocalDeclarations(VarDeclarations* _var_declaration) : var_declaration(_var_declaration){}

	void print(std::ostream& stream)
	{
		if(var_declaration != NULL)
			var_declaration->print(stream);
	}
};

#endif
