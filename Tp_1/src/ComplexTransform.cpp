#include "ComplexTransform.h"

#include "Token.h"



std::string ComplexTransform::userFunction;

ComplexTransform::ComplexTransform(){
	this->function = userFunction;
}

ComplexTransform::ComplexTransform(std::string function){
	this->function = function;
}

ComplexTransform::~ComplexTransform(){
/*No solicita memoria dinámica*/
}

void ComplexTransform::fun(Complejo & input){
// @TODO
//shuntigYard(input);
}

Complejo ComplexTransform::getInput(){
	return this->input;
}

Complejo ComplexTransform::getOutput(){
	return this->output;
}

std::string ComplexTransform::getFunction(void)
{
	return this->function;
}

TransformStatus ComplexTransform::isGoodTransform(string transformString)
{
	if( ComplexTransform::isBalanced(transformString)== false ) 	return TransformStatus::functionIsNotBalanced;
	if( ComplexTransform::hasSingularity(transformString)== true ) return TransformStatus::funtionHasSingularity;
	// Agregar mas estado errones
	// Si paso todo la funcion es correcta
	return TransformStatus::funtionIsOk;
}

void ComplexTransform::setTransform(std::string transformString)
{
	ComplexTransform::userFunction = transformString;
}


bool ComplexTransform::isBalanced(const std::string functionExpresion)
{
	char symbol = 0;
	size_t i = 0;
	stack <char> trash;

	while(i < functionExpresion.length()){

		symbol = functionExpresion[i];

		switch(symbol){
			case '{':
				trash.push(symbol);
			break;
			case '}':
				if(trash.top() == '{')
					trash.pop();
				else
					trash.push('{');
			break;
			case '[':
				trash.push(symbol);
			break;
			case ']':
				if(trash.top() == '[')
					trash.pop();
				else
					trash.push('[');
			break;
			case '(':
				trash.push(symbol);
			break;
			case ')':
				if(trash.top() == '(')
					trash.pop();
				else
					trash.push('(');
			break;
			default:
			break;
		}
		i++;
	}

	if(trash.empty())
		return true;
	else
		return false;
}

bool ComplexTransform::hasSingularity(std::string transformString)
{
	return false;
	// @TODO
}
