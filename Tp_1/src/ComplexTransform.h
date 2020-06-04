#ifndef COMPLEXTRANSFORM_H_
#define COMPLEXTRANSFORM_H_

#include "Complejo.h"
#include <iostream>


enum class TransformStatus
    {
     	funtionIsOk,
     	functionIsNotBalanced,
     	funtionHasSingularity
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

	static TransformStatus isGoodTransform(std::string transformString);
	static void setTransform(std::string transformString);
	static bool isBalanced(const std::string transformString);
	static bool hasSingularity(const std::string transformString);



};

#endif
