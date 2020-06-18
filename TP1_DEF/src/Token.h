//
// Clase Token. 
//
#ifndef __TOKEN__
#define __TOKEN__

#include <cctype> //  isdigit()
#include "Complejo.h"
#include <iostream>
#include <string> 
#include <algorithm> // std::find() ; std::begin() ; std::end()

using namespace std;


class Token {

	// La clase si es un operador tendra las propiedades de precedencia
	// y asocitaivdad; en cambio si no es un operador, devolvera un caracter comun pero con precedencia y asoc. 0
	// 
	//
public:

	// El token en cuestion
	char symbol;
	int value;

	// Tipo de simbolo:
	// 
	// Operador: op
	// Numero: num
	// Numero imaginario 'i': img
	// Separador: sep
	// Funcion: func
	//			min(): m
	//			max(): M
	//			Re(): R
	//			Im(): I
	//			exp(): e
	//			ln(): l
	//			sen(): s
	//			cos(): c
	// 			modulo o Abs(): A
	// espacio vacio ' ': blank 
	// variable 'z': var
	// No es un token valido: notk
	//
	string type;

	// Propiedad de los operadors
	//
	// ^ 4 	Right
	// × 3 	Left
	// / 3 	Left
	// + 2 	Left
	// − 2 	Left 
	//
	int precedence; // Puede ser 4; 3; 2; 
	char associativity; // Puede ser r (right) o l (left)


public:

	Token(); // Done
	Token(char); // Done
	Token(const Token&);
	~Token(); // Done

	const Token& operator=(const Token&);
	const Token& operator=(const char&); 
	const Token& operator=(const int&); 
	const Token& operator=(char&); 

	char sym(); // Done

	int getPrecedence(); // Done

	bool leftAssoc(); // Done
	bool rightAssoc(); // Done
	bool sepRight(); // Done
	bool sepLeft(); // Done
	bool isOperator(); // Done
	bool isSeparator(); // Done
	bool isNumber(); // Done
	bool isFunction(); // Done
	bool istoken(); // Done
	bool isVariable(); // Done
	bool isImag(); // Done

	static int getInvalidStartOperators(int i);
	static int getInvalidEndingOperators(int i);

	static int getNumberOfInvalidStartOperators();
	static int getNumberOfInvalidEndingOperators();

};



#endif
