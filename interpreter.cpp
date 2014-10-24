extern "C" {
#include "interpreter.h"
#include "rpcalc.h"
}

#include <iostream>
#include <list>
#include <map>
#include <string>

class ByteCode;

typedef std::list<ByteCode*> CodeList;
typedef std::map<std::string, CodeList::iterator> FunctionDict;

CodeList code;
FunctionDict function_map;

class ByteCode
{
public:
	virtual int Perform ()=0;
	virtual void Add () {};
};

class Operation : public ByteCode
{
	std::string _op_name;
public:
	Operation (char *op_name) { _op_name += op_name; }
	int Perform ()
	{
		if (_op_name.compare("+") == 0)
			rpAdd();
		else if (_op_name.compare("-") == 0)
			rpSub();
		else if (_op_name.compare("*") == 0)
			rpMul();
		else if (_op_name.compare("/") == 0)
			rpDiv();
		else if (_op_name.compare("^") == 0)
			rpPow();
		else if (_op_name.compare("sin") == 0)
			rpSin();
		else if (_op_name.compare("cos") == 0)
			rpCos();
		else if (_op_name.compare("tan") == 0)
			rpTan();
		else if (_op_name.compare("sinh") == 0)
			rpSinh();
		else if (_op_name.compare("cosh") == 0)
			rpCosh();
		else if (_op_name.compare("tanh") == 0)
			rpTanh();
		else if (_op_name.compare("round") == 0)
			rpRound();
		else if (_op_name.compare("sqrt") == 0)
			rpSqrt();
		else if (_op_name.compare(".") == 0)
			rpPrint();
		else if (_op_name.compare("dump") == 0)
			rpDump();
		else if (_op_name.compare("dup") == 0)
			rpDup();
		else if (_op_name.compare("swap") == 0)
			rpSwap();
		else if (_op_name.compare("drop") == 0)
			rpDrop();
		else if (_op_name.compare("catch") == 0)
			rpCatch();
		else
			std::cout << "Operation '" << _op_name << "' is undefined\n\r";
	
		return 0;
	}
};

class Number : public ByteCode
{
	double _value;
public:
	Number (double value) { _value = value; }
	int Perform ()
	{
		rpPush(_value);

		return 0;
	}
};

class FuncDefinition : public ByteCode
{
	std::string _name;
public:
	FuncDefinition (char *name) { _name += name; }
	int Perform ()
	{
		CodeList::iterator it = function_map[_name];
		it++;
		while ((*it)->Perform() != -1)
			it++;

		return 0;
	}
	void Add ()
	{
		code.push_back(this); // Push definition to the code list
		function_map[_name] = --code.end(); // Add the function into the function map
	}
};

class FuncCall : public ByteCode
{
	std::string _name;
public:
	FuncCall (char *name) { _name += name; }
	int Perform ()
	{
		FunctionDict::iterator it = function_map.find(_name);
		if (it == function_map.end())
			std::cout << "Function '" << _name << "' has not been defined yet!\n\r";
		else
		{
			(*(it->second))->Perform();
		}

		return 0;
	}
};

class EndOfFunction : public ByteCode
{
public:
	EndOfFunction () {}
	int Perform ()
	{
		return -1;
	}
};

/*******************************     Public functions used by the parser ***********************************************************/
// Handling operations
extern "C" void interpret_operation (char *op_name, int perform)
{
	Operation *op = new Operation(op_name);
	code.push_back(op);

	if (perform)
		op->Perform();
}

// Handling numbers
extern "C" void interpret_number (double number, int perform)
{
	Number *num = new Number(number);
	code.push_back(num);

	if (perform)
		num->Perform();
}

// Function definitios
extern "C" void interpret_func_definition (char *func_name)
{
	FuncDefinition *def = new FuncDefinition(func_name);
	def->Add();
}

// Function calls
extern "C" void interpret_func_call (char *func_name, int perform)
{
	FuncCall *call = new FuncCall(func_name);
	code.push_back(call);

	if (perform)
		call->Perform();
}

// Function end
extern "C" void interpret_end_of_func ()
{
	EndOfFunction *eof = new EndOfFunction();
	code.push_back(eof);

	eof->Perform();
}
