#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP


#include <vector>
#include <map>
#include <stdexcept>
#include <iostream>

#include "declaration.hpp"
#include "basics.hpp"

class Constant : public Immutable
{
	virtual void print(std::ostream& stream) = 0;
	virtual void arm(std::ostream& stream, std::map<std::string, unsigned int> &vars, unsigned int &reg) {}
};

class Number : public Constant
{
	virtual void print(std::ostream& stream) = 0;
	virtual void arm(std::ostream& stream, std::map<std::string, unsigned int> &vars, unsigned int &reg) {}
};

class Int : public Number
{
private:
	int val;
public:
	Int(int _val) : val(_val)
	{}
	
	void print(std::ostream& stream) 
	{
		stream << val;
	}
	
    void arm(std::ostream& stream, std::map<std::string, unsigned int> &vars, unsigned int &reg)
    {
    	
		for (int i = 0; i < 13 ; i++)
		{
			if(!regs[i])
			{
				reg = i;
				regs[i] = true;
				break;
			}
		}
    	stream << "MOV R" << reg << ", #" << val << std::endl;
    	
    }
	
};

class Double : public Number
{
private:
	double val;
public:
	Double(double _val) : val(_val)
	{}
	
	void print(std::ostream& stream) 
	{
		stream << val;
	}
};

class Char : public Constant
{
private:
	char val;
public:
	Char(char _val) : val(_val)
	{}
	
	void print(std::ostream& stream) 
	{
		stream << val;
	}
};

class Boolean : public Constant
{
private:
	bool val;
public:
	Boolean(bool _val) : val(_val)
	{}
	
	void print(std::ostream& stream) 
	{	
		switch(val)
		{
		case true:
			stream << "true";
			break;
		case false:
			stream << "false";
			break;
		}
		
	}
};

class String : public Constant
{
private:
	std::string val;
public:
	String(std::string _val) : val(_val)
	{}
	
	void print(std::ostream& stream) 
	{
		stream << val;
	}
};


#endif