//
//
// Falta:
// 
// - numeros de mas de 1 digito: DONE
// - funciones: NO TENGO IDEA -- AYUDA
// - variables: TENGO LA IDEA
//
//
// agregarle a la clase token el numero imaginario
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
	//			sin(): s
	//			cos(): c
	// espacio vacio ' ': blank 
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
	const Token& operator=(const string&); // Done; Loq ue hace es recibir la funcion
	const Token& operator=(const char&); // Done
	const Token& operator=(const int&); // Done; Pero no sirve para nada
	const Token& operator=(string&); // Done
	const Token& operator=(char&); // Done

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
	bool isVariable();

};

int __pow(int r, int k); // Habria que implementarlo para complejos
Complejo apply_cmplx_operation(Complejo&, Complejo&, char); // Recibe dos complejos y le aplica la operacion + - * / falta potencia
Complejo apply_func(Complejo& z, char); // Recibe un complejo y le aplica la funcion; Falta la mayoria...

#endif
