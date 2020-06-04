//
// Falta:
// 
// - numeros de mas de 1 digito: DONE
// - funciones: NO TENGO IDEA -- AYUDA
// - variables: TENGO LA IDEA
//
//
// agregarle a la clase token el numero imaginario

#include <cctype> //  isdigit()
#include "Complejo.h"
#include <iostream>
#include <stack> 
#include <queue> 
#include <string> 
#include <algorithm> // std::find() ; std::begin() ; std::end()

using namespace std;

const static char __operators__[] = { '+', '-', '*', '/', '^' };
const static char __separators__[] = { '(', ')' }; 

const char __img_character__ = 'i'; // Esto eventualmente lo sacare

class Token {

	// Este objeto puede tomar cualquier simbolo; si es un operador tendra las propiedades de precedencia
	// y asocitaivdad; en cambio si no es un operador, devolvera un caracter comun pero con precedencia y asoc. 0
	// 
	//
public:

	// El token en cuestion
	char symbol;
	int value;
	//string str;

	// Tipo de simbolo:
	// 
	// Operador: op
	// Numero: num
	// Numero imaginario 'i': img
	// Separador: sep
	// Ffuncion: func
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
	Token(char); // Done
	Token(const Token&);
	~Token(); // Done

	const Token& operator=(const Token&);
	const Token& operator=(const string&);
	const Token& operator=(const char&); // Done
	const Token& operator=(const int&); // Done; Pero no sirve para nada
	const Token& operator=(string&);
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
	bool isFunction();
	bool istoken(); // Done

};


bool isBalanced(const string&);
int __pow(int r, int k);
int apply_operation(int, int, char);
Complejo apply_cmplx_operation(Complejo &, Complejo &, char);

// ==================================================================================================================================== //
// ==================================================================================================================================== //


int main(int argc, char* argv[]) {
	
	std::cout << argv[1] << endl;
	const string eq = argv[1];

	// Stack de operadores
	stack <char> ops;

	// En este stack ira a parar el resultado
	//stack <int> values;
	// Stack imaginario LOL
	stack <Complejo> cmplx_values;

	// Cola de salida en RPN( solo para numeros de 1 digito, sin funcion ni variables) 
	queue <char> output;


	Token token;
	Token toptoken;
	Token next_token;

	size_t i = 0;

	// Arranca la evaluacion de la cadena
	// 
	while (i < eq.length()) {
		//
		// Mientras que haya tokens para leer:
		//

		// Leo un token
		token = eq[i];

		// SI no es un token valido: No es numero, operador, parentesis, o funcion
		if (!token.istoken()) {
			i++;
			continue;
		}

		// Si el token es un numero
		if (token.isNumber()) {

			next_token = eq[i];
			Complejo z_aux(0, 0); // No se si es bueno llamar al constructor en cada iteracion, pero bueno que seyooo
			int val = 0;

			// Lo que se hara es ver si el numero es de + de 1 digito
			while (next_token.isNumber() && i < eq.length()) {
				if (next_token.sym() == __img_character__)
					z_aux.setImag(1);
				else {

					// Aqui es donde recorro hasta que no haya mas enteros a leer
					//
					// Se almacena en val susecivamente los enteros de 1 digito
					//
					val = (val * 10) + (next_token.sym() - '0');

				}

				// Se lee el siguiente token
				i++;
				next_token = eq[i];
			}

			z_aux.setReal((double)val);

			// Mando al stack SOLO el primer digito; Enrealidad esto lo voy a sacar eventualmente NO DARLE BOLA
			output.push(token.sym());

			// Mando al stack values el numero
			cmplx_values.push(z_aux);

			continue;
		}

		// No hay funcion pero habria que colocar else if(token.isFunc)

		// Si el token es un operador 
		else if (token.isOperator()) {
			//
			// Mientras que haya un operador para sacar en la pila de ops., 
			// y el operador en el tope de la pila ops tenga mayor precedencia que el token 
			// O,, (el operador en el tope de la pila tiene igual precedencia y el token sea left associative)
			// Y el operador en el tope de la pila no sea left parentesis
			//
			//
			if (!ops.empty()) {
				// Pop token de arriba de la pila
				toptoken = ops.top();

				while (
					(!ops.empty())
					&&
					(toptoken.getPrecedence() > token.getPrecedence()
						|| (toptoken.getPrecedence() == token.getPrecedence() && token.leftAssoc()))
					&&
					(!toptoken.sepLeft())
					)
				{

					// Push  token del tope de la pila en la cola de salida
					output.push(toptoken.sym());
					// Pop el toekn del tope de la pila ops
					ops.pop();

					//
					// Realizo la operacion dentro de los parentesis:
					//
					// Tomo los dos operandos de la pila de values
					//
					Complejo z2(cmplx_values.top().getReal(), cmplx_values.top().getImag());
					cmplx_values.pop();

					Complejo z1(cmplx_values.top().getReal(), cmplx_values.top().getImag());
					cmplx_values.pop();

					cmplx_values.push(apply_cmplx_operation(z1, z2, toptoken.sym()));
					
					// Uso el token del tope de la pila, para la siguiente evaluacion del while
					if (!ops.empty())
						toptoken = ops.top();

				}
			}

			// Coloco el token en la pila ops
			ops.push(token.sym());
		}

		// Si el token es parentesis izquierdo
		else if (token.sepLeft()) {
			ops.push(token.sym());
		}

		// Si el token es un parentesis derecho
		else if (token.sepRight()) {

			// Mientras qe el operador en el tope del stack no sea un parentesis izquierdo
			if (!ops.empty()) {
				toptoken = ops.top();

				while (!toptoken.sepLeft()) {

					//
					// Realizo la operacion dentro de los parentesis:
					//
					// Tomo los dos operandos de la pila de values
					//
					Complejo z2(cmplx_values.top().getReal(), cmplx_values.top().getImag());
					cmplx_values.pop();

					Complejo z1(cmplx_values.top().getReal(), cmplx_values.top().getImag());
					cmplx_values.pop();
					//

					ops.pop();
					// Se realiza la operacion y se manda a la pila de resultados
					cmplx_values.push(apply_cmplx_operation(z1, z2, toptoken.sym()));

					// Se manda el operador a la cola de salida.
					output.push(toptoken.sym());

					// SI el stack se acabo, y no encontro ningun parentesis(while no finaliza):
					if (ops.empty()) {
						std::cerr << "equation isn't balanced" << endl;
						exit(1);
					}

					toptoken = ops.top();
				}

				if (toptoken.sepLeft()) {
					ops.pop();
				}
			}
			//
			// Si el stack estuviera vacio seria esta sitacion : ")...", quiere decir que esta desbalanceado, mala suerte...
			else {
				cerr << "equation isn't balanced" << endl;
				exit(1);
			}

		}

		// Se incrementa el contador para avanzar al proximo token
		// Y se reestablece z_aux
		i++;
	}
	// Todo lo que quede en el stack ops, va a parar a la cola
	// Excepto si hay algun parentesis, en ese caso la ecuacion noe sta balanceada
	//
	while (!ops.empty()) {

		// Saco el tope de la pila 
		toptoken = ops.top();
		ops.pop();

		// SI queda un parentesis ==> desbalanceado
		//
		if (toptoken.sepLeft() || toptoken.sepRight()) {
			cerr << "equation isn't balanced" << endl;
			exit(1);
		}

		output.push(toptoken.sym());

		// Realizo la operacion dentro de los parentesis:
		//
		// Tomo los dos operandos de la pila de values
		//
		Complejo z2(cmplx_values.top().getReal(), cmplx_values.top().getImag());
		cmplx_values.pop();

		Complejo z1(cmplx_values.top().getReal(), cmplx_values.top().getImag());
		cmplx_values.pop();

		cmplx_values.push(apply_cmplx_operation(z1, z2, toptoken.sym()));

	}
	//
	// Fin de parseo

	//std::cout << "Cola de salida: " << endl;

	//while (!output.empty()) {
	//	std::cout << output.front() << endl;
	//	output.pop();
	//}

	std::cout << "Resultado" << endl;
	cmplx_values.top().printRect();

	return 0;
}

// ==================================================================================================================================== //
// ==================================================================================================================================== //

bool isBalanced(const string& s) {

	char symbol = 0;
	size_t i = 0;
	stack <char> trash;

	while (i < s.length()) {

		symbol = s[i];

		switch (symbol) {
		case '{':
			trash.push(symbol);
			break;
		case '}':
			if (trash.top() == '{')
				trash.pop();
			else
				trash.push('{');
			break;
		case '[':
			trash.push(symbol);
			break;
		case ']':
			if (trash.top() == '[')
				trash.pop();
			else
				trash.push('[');
			break;
		case '(':
			trash.push(symbol);
			break;
		case ')':
			if (trash.top() == '(')
				trash.pop();
			else
				trash.push('(');
			break;
		default:
			break;
		}
		i++;
	}

	if (trash.empty())
		return true;
	else
		return false;
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

	// Chequeo si es un entero
	//
	if (isdigit(c)) {
		this->type = "num";
		this->value = static_cast<int>(c);
	}

	if (c == 'i') {
		this->type = "num";
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

	// Chequeo si es un entero
	//
	if (isdigit(c)) {

		this->type = "num";
		this->value = static_cast<int>(c);
	}

	if(c == 'i') {
		this->type = "num";
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

	// Chequeo si es un entero
	//
	if (isdigit(c)) {

		this->value = static_cast<int>(c);
		this->type = "num";
	}

	if(c == 'i') {
		this->type = "num";
	}
}

Token::Token() {

	this->symbol = 0;
	this->value = 0;
	// Arranca con un valor por defecto si no es un token valido.
	this->type = "notk";

	// Por defecto si no llega a ser un operador
	this->associativity = 0;
	this->precedence = -1;
}

Token::~Token() {
	this->symbol = 0;
	// Arranca con un valor por defecto si no es un token valido.
	this->type = "notk";

	// Por defecto si no llega a ser un operador
	this->associativity = 0;
	this->precedence = -1;
}

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

int Token::getPrecedence() {

	return this->precedence;
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

char Token::sym() {

	return this->symbol;
}

int apply_operation(int val1, int val2, char  op) {
	switch (op) {
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
	case '^':
		return __pow(val1,val2);
		break;
	default:
		return 0;
		break;
	}
}

int __pow(int r, int k) {
	if (k == 0)
		return 1;
	return r * __pow(r, k - 1);
}

Complejo apply_cmplx_operation(Complejo & z1, Complejo & z2, char op) {
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
		return Complejo(0,0);
		break;
	}
}