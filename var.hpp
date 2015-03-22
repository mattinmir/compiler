#ifndef VAR_HPP
#define VAR_HPP

#include "declaration.hpp"
#include "simple_expressions.hpp"
#include "enums.hpp"
#include "statements.hpp"

#include <vector>
#include <iterator>
#include <iostream>
#include <cstdlib>
#include <map>
#include <string>


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
	void arm(std::ostream& stream, std::map<std::string, unsigned int> &vars, unsigned int &reg)
	{
		if(vars.find(id) != vars.end())
		{
			std::cout << "Error: redeclaration of " << id << std::endl;  
			exit(EXIT_FAILURE);
		}
		else
		{
			vars[id] = address;
			address += 4;
		}
	}
	
	std::string get_id()
	{
		return id;
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
		id->print(stream);
		if(value != NULL)
			value->print(stream);
	}
	void arm(std::ostream& stream, std::map<std::string, unsigned int> &vars, unsigned int &reg)
	{
		id->arm(stream, vars, reg);
		value->arm(stream, vars, reg);
		regs[reg] = true;
		unsigned int regaddr;
		for (int i = 0; i < 13 ; i++)
		{
			if(!regs[i])
			{
				regaddr = i;
				regs[i] = true;
				break;
			}
		}
		stream << "MOV R" << regaddr << ", #" << vars[id->get_id()] << std::endl;
		stream << "STR R" << reg << ", [R" << regaddr << "]" << std::endl;
		regs[reg] = false;
		regs[regaddr] = false;
	}
};


class VarDeclInitList : public DeclarationList
{/*
private:
	std::vector<VarDeclInit*> vardeclinits;
public:
	
	void add(VarDeclInit* vardeclinit)
	{
		vardeclinits.push_back(vardeclinit);
		
	}
	
	void print(std::ostream& stream)
	{
		std::cout << "printing VarDeclList" << std::endl;
		std::vector<VarDeclInit*>::iterator it;
		for (it = vardeclinits.begin(); it != vardeclinits.end(); it++)
		{
			std::cout << *it << std::endl;
			(*it)->print(stream);
		}
	}
	
public:
	VarDeclInitList(){}*/
};




class VarDeclarations :  public Declaration, public Statement
{
private:
	TypeSpecifier type_specifier;
	VarDeclInitList* var_decl_init_list;
public:
	VarDeclarations(TypeSpecifier _type_specifier, VarDeclInitList* _var_decl_init_list) : type_specifier(_type_specifier), var_decl_init_list(_var_decl_init_list) {}
	
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
			stream << "" << std::endl;

	}
	
	virtual void arm(std::ostream& stream, std::map<std::string, unsigned int> &vars, unsigned int &reg)
	{
		var_decl_init_list->arm(stream, vars, reg);
		
	}
};


#endif
