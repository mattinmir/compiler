#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP


#include <vector>
#include <map>
#include <stdexcept>
#include <iostream>




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


#endif