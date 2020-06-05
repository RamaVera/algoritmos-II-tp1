#include "Token.h"
#include <stack> // Implementarlo nosotros
#include <queue> // implementarlo nosotros
#include <iostream>


// ==================================================================================================================================== //
// ==================================================================================================================================== //

const char __img_character__ = 'i'; // Esto eventualmente lo sacare

const string eq = "z+z";

int main(int argc, char* argv[]) {

	//std::cout << argv[1] << endl;
	const string eq2 = argv[1];
	std::cout << eq << endl;

	// Hay un problema con la division de complejos

	// Stack de operadores
	stack <char> ops;
	// En este stack ira a parar el resultado
	stack <Complejo> cmplx_values;

	Token token;
	Token toptoken;
	Token prev_token;
	Token next_token;

	Complejo z(2, 2);

	size_t i = 0;


	// Arranca la evaluacion de la cadena
	// 
	while (i < eq.length()) {
		//
		// Mientras que haya tokens para leer:
		//

		// Leo un token
		token = eq[i];
		if (i == 0)
			prev_token = eq[i];
		else
			prev_token = eq[i - 1];
		if (i == eq.length() - 1)
			next_token = eq[i];
		else
			next_token = eq[i + 1];

		// SI no es un token valido: No es numero, operador, parentesis, letra reservada para funcion, o espacio en blanco
		if (!token.istoken()) {
			std::cerr << "ecuacion no valida" << endl;
			exit(1);
		}

		// Si el token es un numero
		if (token.isNumber()) {

			next_token = eq[i];
			Complejo z_aux(0, 0); // No se si es bueno llamar al constructor en cada iteracion, pero bueno que seyooo
			int val = 0;

			// Lo que se hara es ver si el numero es de + de 1 digito
			// se recorre hasta que no haya mas enteros a leer
			//
			while (next_token.isNumber() && i < eq.length()) {
				if (next_token.sym() == __img_character__)
					z_aux.setImag(1);
				else {


					// Se almacena en val susecivamente los enteros de 1 digito
					//
					val = (val * 10) + (next_token.sym() - '0');

				}

				// Se lee el siguiente token
				i++;
				next_token = eq[i];
			}

			z_aux.setReal((double)val);

			// Mando al stack values el numero
			cmplx_values.push(z_aux);

			continue;
		}

		// Si es una variable
		else if (token.isVariable()) {
			cmplx_values.push(z);
		}


		// Si el token es un operador
		//
		// Si sucdio esto: ++ o ** o //
		else if (token.isOperator() && prev_token.isOperator() && i != 0) {
			cerr << "error de sintaxis" << endl;
			exit(1);
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

		Complejo z2(cmplx_values.top().getReal(), cmplx_values.top().getImag());
		cmplx_values.pop();

		Complejo z1(cmplx_values.top().getReal(), cmplx_values.top().getImag());
		cmplx_values.pop();

		cmplx_values.push(apply_cmplx_operation(z1, z2, toptoken.sym()));

	}
	//
	// Fin de parseo

	std::cout << "Resultado" << endl;
	cmplx_values.top().printRect();

	return 0;
}

// ==================================================================================================================================== //
// ==================================================================================================================================== //
