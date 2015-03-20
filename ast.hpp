#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <vector>

enum class TypeSpecifier
{
	int_t, 
	float_t,
	double_t,
	char_t,
	bool_t
};

enum class Relop
{
	lt_equal_to,
	less_than,
	greater_than,
	gt_equal_to,
	equal_to,
	not_equal_to
};

enum class AssignOp
{
	assign,
	add_assign,
	sub_assign,
	mul_assign,
	div_assign,
	bitwise_and_assign,
	bitwise_or_assign,
	increment,
	decrement
};

enum class Sumop
{
	add,
	sub
};

enum class Mulop
{
	mul,
	div,
	modulo
};


//--------------------------------------------------------------------------------------------------
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


};

//-----------------------------------------------------------------------------------------------

class Expression : public Immutable // SimpleExpression and MutableExpression inherit from thuis as they can both be expressions
{
public:
	Expression(){}
	
};


class Mutable : public Factor
{
private:
	std::string id;
	Expression* array_size;
public:
	Mutable(std::string _id, Expression* _array_size = NULL) 
			: id(_id), array_size(_array_size)
			{}
};


class MutableExpression : public Expression
{
private:
	Mutable* mut;
	AssignOp op;
	Expression* expr;
public:
	MutableExpression(Mutable* _mut, AssignOp _op, Expression* _expr = NULL) // expr NULL when op is increment or decrement
					: mut(_mut), op(_op), expr(_expr)
					{}
};

//-----------------------------------------------------------------------------------------------

class SumExpression
{
private:
	std::vector<>
};


class RelExpression
{
private:
	SumExpression* left;
	Relop op;
	SumExpression* right;
};

class UnaryRelExpression
{
private:
	bool state; //if state is false, logical 'NOT' the expression
	RelExpression* rel_expr;
public:
	UnaryRelExpression(RelExpression* _rel_expr) : rel_expr(_rel_expr), state(true){}
	
	void flip_state()
	{
		state = !state;
	}
};


class  AndExpression
{
private:
	std::vector<UnaryRelExpression*> unary_rel_exprs; // Everything in the vector should be AND'd together
public:
	AndExpression(){}
	
	void add(UnaryRelExpression* unary_rel_expr)
	{
		unary_rel_exprs.push_back(unary_rel_expr);
	}
};

class SimpleExpression : public Expression
{
private:
	std::vector<AndExpression*> and_exprs; // Everything in the vector should be OR'd together
public:
	SimpleExpression(){}
	
	void add(AndExpression* and_expr)
	{
		and_exprs.push_back(and_expr);
	}
};

//-----------------------------------------------------------------------------------------------


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
	VarDeclId* id;
	SimpleExpression* value;
public:
	// If the variable has no initialisation, its value starts as null by deafult
	VarDeclInit(VarDeclId* _id, SimpleExpression* _value = NULL) : id(_id), value(_value) {}
};


class VarDeclInitList :public DeclarationList
{
private:
public:
	VarDeclInitList() {}
};



class VarDeclarations :  public Declaration, public Statement
{
private:
	TypeSpecifier type_specifier;
	VarDeclInitList* var_decl_init_list;
public:
	VarDeclarations(TypeSpecifier _type_specifier) : type_specifier(_type_specifier) {}
};

//---------------------------------------------------------------------------------------------------

class Statement 
{
public:
};

class ExpressionStmt : public Statement
{
private:
	Expression* expr;
public:
	ExpressionStmt(Expression* _expr = NULL) : expr(_expr)
	{}
};

class CompoundStmt : public Statement
{
private:
	std::vector<Statement*> statements;
public:
	CompoundStmt(){}
	
	void add(Statement* statement)
	{
		statements.push_back(statement);
	}
};

class IfStmt : public Statement
{
private:
	SimpleExpression* condition;
	Statement* if_body;
	Statement* else_body;
public:
	IfStmt(SimpleExpression* _condition, Statement* _if_body, Statement* _else_body = NULL)
		: condition(_condition), if_body(_if_body), else_body(_else_body) 
		{}
};

class WhileStmt : public Statement
{
private:
	SimpleExpression* condition;
	Statement* body;
public:
	WhileStmt(SimpleExpression* _condition, Statement* _body) 
			: condition(_condition), body(_body)
			{}
};

class ReturnStmt : public Statement
{
private:
	Expression* expr;
public:
	ReturnStmt(Expression* _expr = NULL) : expr(_expr) {}
};

class BreakStmt : public Statement
{
public:
	BreakStmt(){}
};

//---------------------------------------------------------------------------------------------------


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
	ParamId* param_id;
public:
	ParamIdDecl(TypeSpecifier _type_specifier, ParamId* _param_id) 
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
	ParamList* params;
	Statement* statement;
	
public:
	FunDeclaration(TypeSpecifier _type_specifier, std::string _id, ParamList* _params, Statement* _statement) 
				: type_specifier(_type_specifier),  id(_id),  params(_params),  statement(_statement)
				{}
	
};
//-----------------------------------------------------------------------------------------------------

class ArgList
{
	std::vector<Expression*> exprs;
};

class Call
{
	std::string func_id;
	ArgList* args;
};

class Immutable : public Factor
{
	
};

class Factor
{
private:
	bool negated; // true if factor should be negated
public:
	void negate()
	{
		negated = !negated;
	}
};

class Term 
{
private:
	
};

//------------------------------------------------------------------------------------------------------


class Value
{
public:
    virtual ~Value()
    {}
        
    virtual void print(std::ostream& dst) const=0;
};

class Int : public Value
{
private:
	int val;
public:
	Int(int _val) : val(_val)
	{}
	
	void print(std::ostream& dst) const
	{
		dst << val;
	}
};

class Double : public Value
{
private:
	double val;
public:
	Double(double _val) : val(_val)
	{}
	
	void print(std::ostream& dst) const
	{
		dst << val;
	}
};

class Char : public Value
{
private:
	char val;
public:
	Char(char _val) : val(_val)
	{}
	
	void print(std::ostream& dst) const
	{
		dst << val;
	}
};

class Bool : public Value
{
private:
	bool val;
public:
	Bool(bool _val) : val(_val)
	{}
	
	void print(std::ostream& dst) const
	{
		dst << val;
	}
};

class String : public Value
{
private:
	std::string val;
public:
	String(std::string _val) : val(_val)
	{}
	
	void print(std::ostream& dst) const
	{
		dst << val;
	}
};

#endif // !AST_HPP
