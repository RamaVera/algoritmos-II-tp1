#ifndef COMPLEXTRANSFORM_H_
#define COMPLEXTRANSFORM_H_

#include "Complejo.h"
#include "Token.h"
#include <stack>
#include <iostream>
#include <cctype> //isalpha


enum class TransformStatus
    {
     	funtionIsOk,
     	functionIsNotBalanced,
     	functionHasOperatorError
    };

class ComplexTransform{
private:
	Complejo input;
	Complejo output;
	std::string function;
	static std::string userFunction;

public:
	ComplexTransform(); //constructor
	ComplexTransform(std::string); //con parámetros
	~ComplexTransform(); //destructor

	void fun(Complejo &);

	Complejo getInput();
	Complejo getOutput();

	std::string getFunction( void );

	static TransformStatus isGoodExpresion(std::string transformString);
	static void setTransform(std::string transformString);
	static bool isBalanced(const std::string transformString);
	static bool hasOperatorError(const std::string transformString);

	static int getNumberOfValidFunctions();
	static string getValidFunctions(int i);
	static bool isOnValidFunctionTable(string fun);


};

#endif
