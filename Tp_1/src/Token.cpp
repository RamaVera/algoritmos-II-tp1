/*
 * FunctionStack.cpp
 *
 *  Created on: 3 jun. 2020
 *      Author: Ramiro
 */

#include "Token.h"


const static char __operators__[] = {'+', '-', '*', '/', '^'};
const static char __separators__[] = {'(', ')'}; // TODO , '{', '}', '[', ']'}; No creo que vayan asi que al pedo


const Token & Token::operator=(char & c){
	this->symbol = c;

	// Arranca con un valor por defecto si no es un token valido.
	this->type = "notk";

	// Por defecto si no llega a ser un operador
	this->associativity = 0;
	this->precedence = -1;

	// Por defecto si no esun numero
	//this->numSuspect = false;

	// Chequeo si es un operador
	//
	if(std::find(std::begin(__operators__), std::end(__operators__), this->symbol) != end(__operators__)){
		this->type = "op";

		switch(c){
			case '+':
				this->precedence = 2;
				this->associativity = 'l';
			break;
			case '-':
				this->precedence = 2;
				this->associativity = 'l';
			break;
			case '*':
				this->precedence = 3;
				this->associativity = 'l';
			break;
			case '/':
				this->precedence = 3;
				this->associativity = 'l';
			break;
			case '^':
				this->precedence = 4;
				this->associativity = 'r';
			break;
			default:
			break;

			// Falta implementar % y !
		}
	}

	// Chequeo si un separado. Por ahora solo parentesis, despues vere si se agregan mas
	//
	if(std::find(std::begin(__separators__), std::end(__separators__), this->symbol) != end(__separators__)){
		switch(c){
			case '(':
				this->type = "sep";
			break;
			case ')':
				this->type = "sep";
			break;
		}
	}

	// Chequeo si es un entero
	//
	if(isdigit(c)){
		this->type = "num";
		this->value = static_cast<int>(c);
	}

	return *this;
}

const Token & Token::operator=(const char & c){

	this->symbol = c;

	// Arranca con un valor por defecto si no es un token valido.
	this->type = "notk";

	// Por defecto si no llega a ser un operador
	this->associativity = 0;
	this->precedence = -1;

	// Por defecto si no esun numero
	//this->numSuspect = false;

	// Chequeo si es un operador
	//
	if(std::find(std::begin(__operators__), std::end(__operators__), this->symbol) != end(__operators__)){
		this->type = "op";

		switch(c){
			case '+':
				this->precedence = 2;
				this->associativity = 'l';
			break;
			case '-':
				this->precedence = 2;
				this->associativity = 'l';
			break;
			case '*':
				this->precedence = 3;
				this->associativity = 'l';
			break;
			case '/':
				this->precedence = 3;
				this->associativity = 'l';
			break;
			case '^':
				this->precedence = 4;
				this->associativity = 'r';
			break;
			default:
			break;

			// Falta implementar % y !
		}
	}

	// Chequeo si un separado. Por ahora solo parentesis, despues vere si se agregan mas
	//
	if(std::find(std::begin(__separators__), std::end(__separators__), this->symbol) != end(__separators__)){
		switch(c){
			case '(':
				this->type = "sep";
			break;
			case ')':
				this->type = "sep";
			break;
		}
	}

	// Chequeo si es un entero
	//
	if(isdigit(c)){

		this->type = "num";
		this->value = static_cast<int>(c);
	}

	return *this;
}

const Token & Token::operator=(const int & val){

	this->type = "num";
	this->precedence = -1;
	this->associativity = 0;
	this->value = val;

	return *this;
}

Token::Token(char c){

	this->symbol = c;
	// Arranca con un valor por defecto si no es un token valido.
	this->type = "notk";

	// Por defecto si no llega a ser un operador
	this->associativity = 0;
	this->precedence = -1;

	// Por defecto si no esun numero
	//this->numSuspect = false;

	// Chequeo si es un operador
	//
	if(std::find(std::begin(__operators__), std::end(__operators__), this->symbol) != end(__operators__)){
		this->type = "op";

		switch(c){
			case '+':
				this->precedence = 2;
				this->associativity = 'l';
			break;
			case '-':
				this->precedence = 2;
				this->associativity = 'l';
			break;
			case '*':
				this->precedence = 3;
				this->associativity = 'l';
			break;
			case '/':
				this->precedence = 3;
				this->associativity = 'l';
			break;
			case '^':
				this->precedence = 4;
				this->associativity = 'r';
			break;
			default:
			break;

			// Falta implementar % y !
		}
	}

	// Chequeo si un separado. Por ahora solo parentesis, despues vere si se agregan mas
	//
	if(std::find(std::begin(__separators__), std::end(__separators__), this->symbol) != end(__separators__)){
		switch(c){
			case '(':
				this->type = "sep";
			break;
			case ')':
				this->type = "sep";
			break;
		}
	}

	// Chequeo si es un entero
	//
	if(isdigit(c)){

		this->value = static_cast<int>(c);
		this->type = "num";
	}
}

Token::Token(){

	this->symbol = 0;
	this->value = 0;
	// Arranca con un valor por defecto si no es un token valido.
	this->type = "notk";

	// Por defecto si no llega a ser un operador
	this->associativity = 0;
	this->precedence = -1;
}

Token::~Token(){
	this->symbol = 0;
	// Arranca con un valor por defecto si no es un token valido.
	this->type = "notk";

	// Por defecto si no llega a ser un operador
	this->associativity = 0;
	this->precedence = -1;
}

bool Token::leftAssoc(){
	if(this->associativity == 'l')
		return true;
	return false;
}

bool Token::rightAssoc(){
	if(this->associativity == 'r')
		return true;
	return false;
}

bool Token::sepRight(){
	if(this->symbol == ')')
		return true;
	return false;
}

bool Token::sepLeft(){
	if(this->symbol == '(')
		return true;
	return false;
}

int Token::getPrecedence(){

	return this->precedence;
}

bool Token::istoken(){
	if(this->type != "notk")
		return true;
	return false;
}

bool Token::isNumber(){
	if(this->type == "num")
		return true;
	return false;
}

bool Token::isOperator(){
	if(this->type == "op")
		return true;
	return false;
}

bool Token::isSeparator(){
	if(this->type == "sep")
		return true;
	return false;
}

char Token::sym(){

	return this->symbol;
}

int apply_operation(int val1, int val2, char  op){
	switch(op){
		case '+':
			return val1 + val2;
		break;
		case '-':
			return val1 - val2;
		break;
		case '*':
			return val1 * val2;
		break;
		case '/':
			return val1 / val2;
		break;
		default:
			return 0;
		break;
	}
}


