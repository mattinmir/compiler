#ifndef ENUMS_HPP
#define ENUMS_HPP

enum class TypeSpecifier
{
	null,
	int_t, 
	float_t,
	double_t,
	char_t,
	bool_t
};

enum class Relop
{
	null,
	lt_equal_to,
	less_than,
	greater_than,
	gt_equal_to,
	equal_to,
	not_equal_to
};

enum class AssignOp
{
	null,
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
	null,
	add,
	sub
};

enum class Mulop
{
	null,
	mul,
	div,
	modulo
};



#endif