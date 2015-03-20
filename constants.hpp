#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP


#include <vector>
#include <map>
#include <stdexcept>
#include <iostream>

#include "basics.hpp"

class Constant : public Immutable
{
	
};

class Number : public Constant
{
	
};

class Int : public Number
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

class Double : public Number
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

class Char : public Constant
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

class Boolean : public Constant
{
private:
	bool val;
public:
	Boolean(bool _val) : val(_val)
	{}
	
	void print(std::ostream& dst) const
	{
		dst << val;
	}
};

class String : public Constant
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


#endif