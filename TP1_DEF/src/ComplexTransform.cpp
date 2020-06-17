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


// OJO: Hay que corregirlo esta mallll
bool ComplexTransform::isBalanced(const std::string functionExpresion)
{
	char symbol = 0;
	size_t i = 0;
	Stack <char> pila;

	while(i < functionExpresion.length()){

		symbol = functionExpresion[i];

		switch(symbol){
			case '{':
				pila.push(symbol);
			break;
			case '}':
				if(pila.top() == '{')
					pila.pop();
				else
					pila.push('{');
			break;
			case '[':
				pila.push(symbol);
			break;
			case ']':
				if(pila.top() == '[')
					pila.pop();
				else
					pila.push('[');
			break;
			case '(':
				pila.push(symbol);
			break;
			case ')':
				if(pila.top() == '(')
					pila.pop();
				else
					pila.push('(');
			break;
			default:
			break;
		}
		i++;
	}

	if(pila.isEmpty())
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

std::string ComplexTransform::parseExpresion( std::string inputExpresion)
 {
	std::string outputExpresion = inputExpresion;
	int L = outputExpresion.length();

	for(int i = 0 ; i < L ; ++i)
	{
		Token token = outputExpresion[i];
		if( token.isFunction() )
		{
			outputExpresion.replace(i,3,outputExpresion.substr(i,1));
			//cout<< outputExpresion << endl;
			L = outputExpresion.length();
		}
	}
	return outputExpresion;

 }

// ==================================================================================================================================== //
//								Implementacion del algoritmo para evaluar una cadena en formato rpn (?? 
// ==================================================================================================================================== //
//
// 
// Implementacion del algoritmo shunting yard. Recibe una cadena* que representa la funcion a evaluar
// y el valor de la variable z. Dentro de una pila llamada cmplx_values, se ira almacenando el resultado
// de haber hecho la operacion entre numeros complejos. Al finalizar, la pila solo contendra el resultado final.
// El algoritmo recorre toda la cadena, apila los operadores en un stack, y el resultado en otro stack.
//
// *
// PRECONDICION: La cadena debera estar correcta de sintaxis:
// Solo es valido:
// Cadenas balanceadas del tipo a+b*i
// FUnciones de un caracter: log --> l ; exp --> e ; Imag -- > I ; Re --> R;
// 
// METODO De la clase ComplexTransform.
// 



// Realiza la operacion pasada por Token entre complejos y lo pushea en un stack. 
// Usa las funciones __apply_cmplx_operation y __ apply_func
//
void apply_operation(Stack <Complejo> &, Token &);// DEberia ser const TOken &, pero para eso todos los metodos deberian ser con const

Complejo __apply_cmplx_operation(Complejo&, Complejo&, char); // Recibe dos complejos y le aplica la operacion

// Recibe un complejo y le aplica la funcion; OJO: Los caracteres identificatorios DEBEN COINCIDIR con los de 
// la clase Token;; 
//
Complejo __apply_func(Complejo& z, char); 


// ==================================================================================================================================== //
// ==================================================================================================================================== //

void ComplexTransform::fun(Complejo & input){

	// Stack de operadores
	Stack <char> ops;
	// En este stack ira a parar el resultado
	Stack <Complejo> cmplx_values;

	Token token;
	Token toptoken;
	Token next_token;

	Complejo z(0,0);
	z.setReal(input.getReal());
	z.setImag(input.getImag());

	size_t i = 0;


	// Arranca la evaluacion de la cadena
	// 
	while (i < function.length()) {
		//
		// Mientras que haya tokens para leer:
		//

		// Leo un token
		token = function[i];
	
		// SI no es un token valido: No es numero, operador, parentesis, letra reservada para funcion, o espacio en blanco
		if (!token.istoken()) {
			std::cerr << "ecuacion no valida" << endl;
			exit(1);
		}

		// Si el token es un numero
		if (token.isNumber() || token.isImag() || next_token.sym() == '.') {

			next_token = function[i];

			Complejo z_aux(0, 0); // No se si es bueno llamar al constructor en cada iteracion, pero bueno que seyooo

			double val = 0; // En val se guardara el numero real 
			double frac = 0.1; 

			int dots = 0; // Sirve para ver si se ingreso mas de un punto consecutivo

			bool imagFlag = false; // Sirve para validar que no se haya ingresado un i consecutivo o previo a un numero sin el *
			bool numFlag = false; 
			bool dotFlag = false; // Dice si se ingreso un punto, para saber que hay que trabajar en la parte decimal del numero

			// Lo que se hara es ver si el numero es de + de 1 digito o si hay parte decimal
			// se recorre hasta que no haya mas enteros a leer o que 
			//
			while ((next_token.isNumber() || next_token.isImag() || next_token.sym() == '.') && i < userFunction.length()) {
				
				if(imagFlag || (dots != 0 && dots != 1) ){
					// Si ya hubo un numero imaginario, y se ingreso otro consecutivo es error de sintaxis
					exit(1);
					std::cerr << "error de sintaxis" << std::endl;
				} 

				if (next_token.isImag()){

					if(numFlag){
						// Si hubo un numero y consecutivamente un numero imaginario, es error sintaxis
						exit(1);
						std::cerr << "error de sintaxis" << std::endl;		
					}

					z_aux.setImag(1);
					imagFlag = true;
				}
				else if(next_token.isNumber()) {

					numFlag = true;

					if(!dotFlag){
						// Se almacena en val susecivamente los enteros de 1 digito
						//
						val = (val * 10) + (next_token.sym() - '0'); // Restarle cero para que el char lo lea como int
					} else {
						val = val + (next_token.sym() - '0') * frac;
						frac = frac * 0.1;
					}

				}
				else if(next_token.sym() == '.'){
					dots++;
					dotFlag = true;
				}
					

				// Se lee el siguiente token
				i++;
				next_token = function[i];
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


		else if(token.isFunction()){
			ops.push(token.sym());
		}

		else if (token.isOperator() ) {
			//
			// Mientras que haya un operador para sacar en la pila de ops., 
			// y el operador en el tope de la pila ops tenga mayor precedencia que el token 
			// O,, (el operador en el tope de la pila tiene igual precedencia y el token sea left associative)
			// Y el operador en el tope de la pila no sea left parentesis
			//
			//
			if (!ops.isEmpty()) {
				// Pop token de arriba de la pila
				toptoken = ops.top();

				while (
					(!ops.isEmpty())
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
					//
					//
					apply_operation(cmplx_values, toptoken);
					

					// Uso el token del tope de la pila, para la siguiente evaluacion del while
					if (!ops.isEmpty())
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
			if (!ops.isEmpty()) {
				toptoken = ops.top();

				while (!toptoken.sepLeft()) {
					//
					// Realizo la operacion dentro de los parentesis:
					//
					apply_operation(cmplx_values, toptoken);

					ops.pop();

					// SI el stack se acabo, y no encontro ningun parentesis(while no finaliza):
					if (ops.isEmpty()) {
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
	while (!ops.isEmpty()) {

		// Saco el tope de la pila 
		toptoken = ops.top();
		ops.pop();

		// SI queda un parentesis ==> desbalanceado
		//
		if (toptoken.sepLeft() || toptoken.sepRight()) {
			cerr << "equation isn't balanced" << endl;
			exit(1);
		}

		apply_operation(cmplx_values, toptoken);
	}
	//
	// Fin de parseo

	// Le asigno al numero complejo de entrada el resultado de la funcion.
	this->output = cmplx_values.top();

}


// ==================================================================================================================================== //
// ==================================================================================================================================== //




Complejo __apply_cmplx_operation(Complejo& z1, Complejo& z2, char op) {
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
		return z1 ^ z2;
		break;
	default:
		return Complejo(0, 0);
		break;
	}
}

Complejo __apply_func(Complejo& z, char func) {

	Complejo z_aux(0, 0);

	switch (func) {

	// exp(z)
	case 'e':
		z_aux.setReal( exp(z.getReal()) * cos(z.getImag()) );
		z_aux.setImag( exp(z.getReal()) * sin(z.getImag()) );
		return z_aux;
	break;

	// log(z)
	case 'l':
		return log(z);
	break;

	// Re(z)
	case 'R':
		z_aux.setReal(z.getReal());
		return z_aux;
	break;

	// Im(z)
	case 'I':
		z_aux.setReal(z.getImag());
		return z_aux;
	break;

	default:
		return z_aux;
	break;
	}

}

void apply_operation(Stack <Complejo> & cmplx_values, Token & toptoken){

	if(toptoken.isFunction()){

		Complejo z2(cmplx_values.top().getReal(), cmplx_values.top().getImag());
		cmplx_values.pop();

		cmplx_values.push(__apply_func(z2, toptoken.sym()));							

		} else {

		Complejo z2(cmplx_values.top().getReal(), cmplx_values.top().getImag());
		cmplx_values.pop();

		Complejo z1(cmplx_values.top().getReal(), cmplx_values.top().getImag());
		cmplx_values.pop();

		cmplx_values.push(__apply_cmplx_operation(z1, z2, toptoken.sym()));	
	}

}
