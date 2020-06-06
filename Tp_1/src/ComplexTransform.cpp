#include "ComplexTransform.h"


const static string __functions__[] = { "exp", "min", "max", "exp", "Rel", "Img", "log", "cos", "sin" };
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
//shuntigYard(function,input);
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

TransformStatus ComplexTransform::isGoodExpresion(string transformString)
{
	if( ComplexTransform::hasOperatorError(transformString)	== true ) 	return TransformStatus::functionHasOperatorError;
	if( ComplexTransform::isBalanced(transformString)		== false ) 	return TransformStatus::functionIsNotBalanced;

	// Agregar mas estado errones
	// Si paso todo la funcion es correcta
	return TransformStatus::funtionIsOk;
}

void ComplexTransform::setTransform(std::string transformString)
{
	ComplexTransform::userFunction = transformString;
}

int ComplexTransform::getNumberOfValidFunctions()
{
	return sizeof(__functions__)/sizeof(string);
}

string ComplexTransform::getValidFunctions(int i)
{
	return __functions__[i];
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

bool ComplexTransform::hasOperatorError(std::string transformString)
{
	// Chequeo si comienza con caracteres invalidos ( ^,*,/,) )
	size_t N=Token::getNumberOfInvalidStartOperators();
	for(size_t i = 0 ; i < N ; ++i)
	{
		if(transformString[0] == Token::getInvalidStartOperators(i) ) return true;
	}

	// Analizo el cuerpo de la expresion
	size_t L = transformString.length();

	for(size_t i = 1 ; i < L ; ++i)
	{
		Token prevToken = transformString[i-1];
		Token token = transformString[i];

		// Chequeo si tiene expresiones binarias invalidas de caracteres (--, ++, +*, etc)
		if( ( prevToken.isOperator() ) && ( token.isOperator() ) ) 	return true;

		// Chequeo si tiene expresiones binarias invalidas de numeros complejos ( 5i, ii, z5, zz etc)
		if( ( prevToken.isNumber() ) 	&& ( token.sym() == 'i' ) ) 	return true;
		if( ( prevToken.sym() == 'z')  && ( token.isNumber() ) )		return true;

		// Si el token es un caracter alfanumerico (excepto z o i) tiene que pertenecer a una funcion
		if( prevToken.isFunction() )
		{
			// Chequeo que la funcion este en la lista de funciones validas
			std::string funExpresion = transformString.substr (i-1,3);
			if( ComplexTransform::isOnValidFunctionTable(funExpresion) == false )
			{
				cerr << funExpresion << " No es una funcion valida : Recuerde las funciones se escriben en minuscula" << endl;
				return true;
			}
			i=i+2;
		}
	}

	// Chequeo si termina con caracteres invalidos ( ^,*,/,(,{ )
	size_t M=Token::getNumberOfInvalidEndingOperators();
	for(size_t i = 0 ; i < M ; ++i)
	{
		Token lastToken = transformString[L-1];
		if( lastToken.sym() == Token::getInvalidEndingOperators(i) ) return true;
		if( lastToken.isFunction() == true) return true;
	}



	return false;

}

bool ComplexTransform::isOnValidFunctionTable(string fun )
{
	//@TODO
	// Las funciones deben tener un ancho de 3 (se puede hacer un resize)
	// Las funciones distinguen minisculas o mayus (se puede hacer un tolower a todo antes de comparar)

	size_t F = ComplexTransform::getNumberOfValidFunctions();
	bool functionIsOnTable = false;
	for(size_t i = 0 ; i < F ; ++i)
	{
		if( fun.compare(__functions__[i]) == 0 )
		{
			functionIsOnTable = true;
			break;
		}
	}
	return functionIsOnTable;
}
