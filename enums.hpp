#ifndef ENUMS_HPP
#define ENUMS_HPP

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
#endif