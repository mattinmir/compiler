#ifndef FUN_HPP_
#define FUN_HPP_

#include "enums.hpp"
#include "declaration.hpp"
#include "statements.hpp"

#include <vector>
#include <iterator>
#include <iostream>


class ParamId
{
private:
	std::string id;
	bool is_array;
public:
	ParamId(std::string _id, bool _is_array) : id(_id), is_array(_is_array)
	{}

	void print(std::ostream& stream)
	{
		stream << id;
		if(is_array)
			stream << "[]";
	}
};

class ParamIdDecl
{
private:
	TypeSpecifier type_specifier;
	ParamId* param_id;
public:
	ParamIdDecl(TypeSpecifier _type_specifier, ParamId* _param_id) 
				: type_specifier(_type_specifier), param_id(_param_id)
				{}
	void print(std::ostream& stream)
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
		param_id->print(stream);
		
	}
};

class ParamList
{
private:
	std::vector<ParamIdDecl*> param_id_decls;
public:
	ParamList()
	{}
	
	void add(ParamIdDecl* param_id_decl)
	{
		param_id_decls.push_back(param_id_decl);
	}
	
	void print(std::ostream& stream)
	{
		std::vector<ParamIdDecl*>::iterator it;
		for (it = param_id_decls.begin(); it != param_id_decls.end(); it++)
			(*it)->print(stream);
	}
};

class FunDeclaration : public Declaration
{
private:
	TypeSpecifier type_specifier;
	std::string id;
	ParamList* params;
	Statement* statement;
	
public:
	FunDeclaration(TypeSpecifier _type_specifier, std::string _id, ParamList* _params, Statement* _statement) 
				: type_specifier(_type_specifier),  id(_id),  params(_params),  statement(_statement)
				{}
	
	void print(std::ostream& stream)
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
		stream << " " << id;
		params->print(stream);
		statement->print(stream);
		
	}
	
};


#endif /* FUN_HPP_ */
