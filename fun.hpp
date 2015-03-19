#ifndef FUN_HPP_
#define FUN_HPP_

#include "enums.hpp"
#include "declaration.hpp"
#include "statements.hpp"

#include <vector>
#include <stdexcept>
#include <iostream>


class ParamId
{
private:
	std::string id;
	bool is_array;
public:
	ParamId(std::string _id, bool _is_array) : id(_id), is_array(_is_array)
	{}

};

class ParamIdDecl
{
private:
	TypeSpecifier type_specifier;
	ParamId param_id;
public:
	ParamIdDecl(TypeSpecifier _type_specifier, ParamId _param_id) 
				: type_specifier(_type_specifier), param_id(_param_id)
				{}
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
};

class FunDeclaration : public Declaration
{
private:
	TypeSpecifier type_specifier;
	std::string id;
	ParamList params;
	Statement statement;
	
public:
	FunDeclaration(TypeSpecifier _type_specifier, std::string _id, Params _params, Statement _statement) 
				: type_specifier(_type_specifier),  id(_id),  params(_params),  statement(_statement)
				{}
	
};


#endif /* FUN_HPP_ */
