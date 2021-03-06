#ifndef COMPLEXTRANSFORM_H_
#define COMPLEXTRANSFORM_H_

#include "Complejo.h"
#include "Token.h"
#include "Stack.h"
#include <iostream>
#include <cctype>  //isalpha
#include <string>
#include <math.h> // Para coseno seno y exp


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
	static std::string parseExpresion( std::string);


};

#endif
