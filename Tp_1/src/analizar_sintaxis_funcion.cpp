#include "Token.h"
#include <iostream>
#include <stack>

using namespace std;

const char __img_character__ = 'i'; // Esto eventualmente lo sacare

bool parcing(const string&); // Analiza y devuelve true si no hay errores de sintaxis o false.
const string eq = "z+z";

int main() {

	if (!parcing(eq))
		exit(1);
}

bool parcing(const string& eq) {

	std::cout << eq << endl;

	// Stack de operadores
	stack <char> ops;

	Token token;
	Token toptoken;
	Token prev_token;
	Token next_token;

	size_t i = 0;
	size_t j = 0;

	// Arranca la evaluacion de la cadena
	// 
	while (i < eq.length()) {
		//
		// Mientras que haya tokens para leer:
		//

		// Leo un token
		token = eq[i];

		if (token.sym() == ' ') {
			i++;
			continue;
		}

		// El primer token no puede ser: ) operador 
		if (j == 0) {
			if (token.isOperator() || token.sepRight()) {
				cerr << "error de sintaxis operador o parentesis al inicio" << endl;
				return false;
			}
			prev_token = eq[i];
		}
		else
			prev_token = eq[i - 1]; // esto tiee


		cout << " token anterior " << prev_token.sym() << endl;
		cout << " j == " << j << endl;
		cout << " i == " << i << endl;

		// El ultimo token solo puede ser: ) o variable o numero
		if (i == eq.length()) {
			if (!token.sepRight() || !token.isNumber() || !token.isVariable() || !(token.sym() == ' ')) {
				cerr << "error de sintaxis oeprador o parentesis al final" << endl;
				return false;
			}
			next_token = eq[i];
		}
		else
			next_token = eq[i + 1];

		// SI no es un token valido: No es numero, operador, parentesis, letra reservada para funcion, o espacio en blanco
		if (!token.istoken()) {
			std::cerr << "ecuacion no valida" << endl;
			return false;
		}

		// Si el token es un numero 
		if (token.isNumber()) {
			if (j != 0) {
				// Antes de un numero solo puede haber espacio en blanco, operador o parentesis; otra cosa es error.
				if (prev_token.isOperator() || prev_token.isSeparator() || prev_token.sym() == ' ' || prev_token.isNumber()) {
					i++;
					continue;
				}
				else {
					cerr << "error de sintaxis numero" << endl;
					return false;
				}
			}
		}

		// Si el token es un numero o variable z
		if (token.isVariable()) {
			if (j != 0) {
				// Antes de una variable solo puede haber espacio blanco, operador o parentesis. 
				if ((prev_token.isOperator() || prev_token.isSeparator() || prev_token.sym() == ' ')) {
					i++;
					continue;
				}
				else {
					cerr << "error de sintaxis en variable" << endl;
					return false;
				}
			}
		}

		// Si el token es un operador
		//
		// Si el token anterior es otro operador, ej: ** ++ //
		else if (token.isOperator() && prev_token.isOperator() && i != 0) {
			cerr << "error de sintaxis" << endl;
			return false;
		}
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

					// Pop el toekn del tope de la pila ops
					ops.pop();

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
					ops.pop();

					// SI el stack se acabo, y no encontro ningun parentesis(while no finaliza):
					if (ops.empty()) {
						std::cerr << "equation isn't balanced" << endl;
						return false;
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
				return false;
			}

		}

		// Se incrementa el contador para avanzar al proximo token
		i++;
		j++;
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
			return false;
		}

	}
	//
	// Fin de parseo

	return true;

}