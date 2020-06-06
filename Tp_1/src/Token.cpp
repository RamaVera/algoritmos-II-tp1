#include "Token.h"

using namespace std;

const static char __operators__[] = { '+', '-', '*', '/', '^' };
const static char __separators__[] = { '(', ')' };
const char __img_character__ = 'i'; // Esto eventualmente lo sacare

const static char invalidStartOperators[]={'^','*','/',')',']','}'};
const static char invalidEndingOperators[]={'^','*','/','(','{','{','+','-'};

Token::Token() {

	this->symbol = 0;
	this->value = 0;
	// Arranca con un valor por defecto si no es un token valido.
	this->type = "notk";

	// Por defecto si no llega a ser un operador
	this->associativity = 0;
	this->precedence = -1;
}
Token::Token(char c) {

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
	if (std::find(std::begin(__operators__), std::end(__operators__), this->symbol) != end(__operators__)) {
		this->type = "op";

		switch (c) {
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
	if (std::find(std::begin(__separators__), std::end(__separators__), this->symbol) != end(__separators__)) {
		switch (c) {
		case '(':
			this->type = "sep";
			break;
		case ')':
			this->type = "sep";
			break;
		}
	}

	// Chequeo si es un entero o numero imaginario
	//
	if (isdigit(c)) {

		this->value = static_cast<int>(c);
		this->type = "num";
	}
	if (isalpha(c)) {
		if (c == 'i' )
			this->type = "num";
		else if (c == 'z') {
			this->type = "var";
			this->symbol = c;
		}		
		else
		this->type = "func";
	}

	// Chequeo si es un espacio en blanco
	//
	if (c == ' ') {
		this->type = "blank";
	}
}
Token::~Token() {
	this->symbol = 0;
	// Arranca con un valor por defecto si no es un token valido.
	this->type = "notk";

	// Por defecto si no llega a ser un operador
	this->associativity = 0;
	this->precedence = -1;
}


const Token& Token::operator=(char& c) {
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
	if (std::find(std::begin(__operators__), std::end(__operators__), this->symbol) != end(__operators__)) {
		this->type = "op";

		switch (c) {
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
	if (std::find(std::begin(__separators__), std::end(__separators__), this->symbol) != end(__separators__)) {
		switch (c) {
		case '(':
			this->type = "sep";
			break;
		case ')':
			this->type = "sep";
			break;
		}
	}

	// Chequeo si es un entero o si es numero imaginario
	//
	if (isdigit(c)) {
		this->type = "num";
		this->value = static_cast<int>(c);
	}
	
	// Chequeo si es un espacio en blanco
	//
	if (c == ' ') {
		this->type = "blank";
	}

	if (isalpha(c)) {
		if (c == 'i' )
			this->type = "num";
		else if (c == 'z') {
			this->type = "var";
			this->symbol = c;
		}		
		else
		this->type = "func";
	}
	return *this;
}
const Token& Token::operator=(const char& c) {

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
	if (std::find(std::begin(__operators__), std::end(__operators__), this->symbol) != end(__operators__)) {
		this->type = "op";

		switch (c) {
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

		}
	}

	// Chequeo si un separado. Por ahora solo parentesis, despues vere si se agregan mas
	//
	if (std::find(std::begin(__separators__), std::end(__separators__), this->symbol) != end(__separators__)) {
		switch (c) {
		case '(':
			this->type = "sep";
			break;
		case ')':
			this->type = "sep";
			break;
		}
	}

	// Chequeo si es un entero o numero imaginario
	//
	if (isdigit(c)) {

		this->type = "num";
		this->value = static_cast<int>(c);
	}
	
	// Chequeo si es un espacio en blanco
	//
	if (c == ' ') {
		this->type = "blank";
	}

	if (isalpha(c)) {
		if (c == 'i' )
			this->type = "num";
		else if (c == 'z') {
			this->type = "var";
			this->symbol = c;
		}		
		else
		this->type = "func";
	}

	return *this;
}
const Token& Token::operator=(const int& val) {

	this->type = "num";
	this->precedence = -1;
	this->associativity = 0;
	this->value = val;

	return *this;
}
/*
const Token& Token::operator=(const string& s) {

	if (s == "exp") {
		this->type = "func";
		this->symbol = 'e';
	}

	else if (s == "log") {
		this->type = "func";
		this->symbol = 'l';
	}

	else if (s == "Re") {
		this->type = "func";
		this->symbol = 'R';
	}

	else if (s == "Im") {
		this->type = "func";
		this->symbol = 'I';
	}

	else if (s == "max") {
		this->type = "func";
		this->symbol = 'M';
	}

	else if (s == "min") {
		this->type = "func";
		this->symbol = 'm';
	}

	else {
		this->type = "notk";
		this->symbol = 0;
	}

	return *this;
}
const Token& Token::operator=(string& s) {

	if (s == "exp") {
		this->type = "func";
		this->symbol = 'e';
	}

	else if (s == "log") {
		this->type = "func";
		this->symbol = 'l';
	}

	else if (s == "Re") {
		this->type = "func";
		this->symbol = 'R';
	}

	else if (s == "Im") {
		this->type = "func";
		this->symbol = 'I';
	}

	else if (s == "max") {
		this->type = "func";
		this->symbol = 'M';
	}

	else if (s == "min") {
		this->type = "func";
		this->symbol = 'm';
	}

	else {
		this->type = "notk";
		this->symbol = 0;
	}

	return *this;
}
*/

bool Token::leftAssoc() {
	if (this->associativity == 'l')
		return true;
	return false;
}
bool Token::rightAssoc() {
	if (this->associativity == 'r')
		return true;
	return false;
}
bool Token::sepRight() {
	if (this->symbol == ')')
		return true;
	return false;
}
bool Token::sepLeft() {
	if (this->symbol == '(')
		return true;
	return false;
}
bool Token::istoken() {
	if (this->type != "notk")
		return true;
	return false;
}
bool Token::isNumber() {
	if (this->type == "num")
		return true;
	return false;
}
bool Token::isOperator() {
	if (this->type == "op")
		return true;
	return false;
}
bool Token::isSeparator() {
	if (this->type == "sep")
		return true;
	return false;
}
bool Token::isFunction() {
	if (this->type == "func")
		return true;
	return false;
}
bool Token::isVariable() {
	if (this->type == "var")
		return true;
	return false;
}

char Token::sym() {

	return this->symbol;
}
int Token::getPrecedence() {

	return this->precedence;
}


int Token::getNumberOfInvalidStartOperators()
{
	return sizeof(invalidStartOperators)/sizeof(char);
}

int Token::getNumberOfInvalidEndingOperators()
{
	return sizeof(invalidEndingOperators)/sizeof(char);
}


int Token::getInvalidStartOperators(int i)
{
	return invalidStartOperators[i];
}

int Token::getInvalidEndingOperators(int i)
{
	return invalidEndingOperators[i];
}



Complejo apply_cmplx_operation(Complejo& z1, Complejo& z2, char op) {
	switch (op) {
	case '+':
		return z1 + z2;
		break;
	case '-':
		return z1 - z2;
		break;
	case '*':
		return z1 * z2;
		break;
	case '/':
		return z1 / z2;
		break;
	case '^':
		//return __pow(val1, val2);
		break;
	default:
		return Complejo(0, 0);
		break;
	}
}

Complejo apply_func(Complejo& z, char func) {

	Complejo z_aux(0, 0);

	switch (func) {
	case 'e':
		// Aplicar exponencial y devolver
		break;
	case 'l':
		// Aplicar log y devolver
		break;
	case 'R':
		z_aux.setReal(z.getReal());
		return z_aux;
		break;
	case 'I':
		z_aux.setImag(z.getImag());
		return z_aux;
		break;
	}
}
