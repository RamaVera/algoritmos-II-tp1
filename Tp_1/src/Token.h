/*
 * FunctionStack.h
 *
 *  Created on: 3 jun. 2020
 *      Author: Ramiro
 */

#ifndef SRC_TOKEN_H_
#define SRC_TOKEN_H_

#include <iostream>
#include <cctype> //  isdigit()
#include <stack>
#include <queue>
#include <string>
#include <algorithm> // std::find() ; std::begin() ; std::end()


using namespace std;

class Token {
private:
	string function;

public:
private:

	// El token en cuestion
	char symbol;
	int value;
	//string str;

	// Tipo de simbolo:
	//
	// Operador: op
	// Numero: num
	// Separador: sep
	// Ffuncion: func
	// No es un token valido: notk
	//
	string type;


	// Numero
	// numSuspect: Flag. SI llega a ingresar un caracter entero se activa
	// Siempre que se ingrese un int, se pregunta si ese flag esta en 1
	// En caso de que entre otro tipo, se baja el flag
	//
	//bool numSuspect;
	//string number;

	// Si es una funcion; se implementara en la version alpha
	// Flag de sospecha de encontrar caracter de funcion:
	// cos ; sin/sen ; exp
	// En prev se almacena el caracter anterior, ejemplo:
	// si se encuentra s se guarda en prev, se activa el flag; si luego se encuentra
	// una i, se compara con prev y luego hasta la n. se forma sin
	//
	//string func;
	//char prev;
	//bool funcSuspect;

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

	// Usar asi:
	// Declaro token por defecto: Token token;
	// Dentro del while:
	// -- token = c;
	// -- Pregunto si es num, funcion, parentesis.
	// ----- SI es num: Guardo token
	// -------- Para todo token y mientras que sea int
	// ------------ val = (val*10) + (tokens[i]-'0'); Push val
	// ----- SI es op: Guardo el operador

public:

	Token(); // Done
	Token(char ); // Done
	Token(const Token &);
	~Token(); // Done

	const Token & operator=(const Token &);
	const Token & operator=(const string &);
	const Token & operator=(const char &); // Done
	const Token & operator=(const int &); // Done; Pero no sirve para nada
	const Token & operator=(string &);
	const Token & operator=(char &); // Done

	char sym(); // Done

	int getPrecedence(); // Done

	bool leftAssoc(); // Done
	bool rightAssoc(); // Done
	bool sepRight(); // Done
	bool sepLeft(); // Done
	bool isOperator(); // Done
	bool isSeparator(); // Done
	bool isNumber(); // Done
	bool isFunction();
	bool istoken(); // Done

};

#endif /* SRC_TOKEN_H_ */
