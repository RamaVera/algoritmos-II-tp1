//
// Falta:
// 
// - numeros de mas de 1 digito
// - funciones
// - variables
//

#include <cctype> //  isdigit()
#include <iostream>
#include <stack> 
#include <queue> 
#include <string> 
#include <algorithm> // std::find() ; std::begin() ; std::end() 

using namespace std;

const static char __operators__[] = {'+', '-', '*', '/', '^'}; 
const static char __separators__[] = {'(', ')'}; // TODO , '{', '}', '[', ']'}; No creo que vayan asi que al pedo

class Token{

// Este objeto puede tomar cualquier simbolo; si es un operador tendra las propiedades de precedencia
// y asocitaivdad; en cambio si no es un operador, devolvera un caracter comun pero con precedencia y asoc. 0
// 
//
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


bool isBalanced(const string & );
int apply_operation(int, int, char  );

// ==================================================================================================================================== //
// ==================================================================================================================================== //


int main(int argc, char * argv[]){

	cout << argv[1] << endl;
	const string eq = argv[1];

	// Stack de operadores
	stack <char> ops;

	// En este stack ira a parar el resultado
	stack <int> values;

	// Cola de salida en RPN( solo para numeros de 1 digito, sin funcion ni variables) 
	queue <char> output;

	int val = 0;

	Token token;
	Token toptoken;
	Token next_token;

	size_t i = 0;

	// Arranca la evaluacion de la cadena
	// 
	while(i < eq.length()){   			
	//
	// Mientras que haya tokens para leer:
	//

		// Leo un token
		token = eq[i]; 
		
		// SI no es un token valido: No es numero, operador, parentesis, o funcion
		if(!token.istoken()){
			i++;
			continue;
		}

		// Si el token es un numero
		if(token.isNumber()){

			next_token = eq[i];

			// Lo que se hara es ver si el numero es de + de 1 digito
			// Aqui es donde recorro hasta que no haya mas enteros a leer
			//
			val = 0;
			while(next_token.isNumber() && i < eq.length()){
						
				// Se almacena en val susecivamente los enteros de 1 digito
				val = (val * 10) + (next_token.sym() -'0'); 

				// Se lee el siguiente token
				i++;
				next_token = eq[i];		

			} 

			// Mando al stack SOLO el primer digito; Esta es la primera aproximacion segun Wikipedia
			output.push(token.sym());

			// Mando al stack values el numero
			values.push(val);

			continue;
		}

		// No hay funcion pero habria que colocar else if(token.isFunc)

		// Si el token es un operador 
		else if(token.isOperator()){
			//
			// Mientras que haya un operador para sacar en la pila de ops., 
			// y el operador en el tope de la pila ops tenga mayor precedencia que el token 
			// O,, (el operador en el tope de la pila tiene igual precedencia y el token sea left associative)
			// Y el operador en el tope de la pila no sea left parentesis
			//
			//
			if(!ops.empty()){
				// Pop token de arriba de la pila
				toptoken = ops.top(); 

				while(
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

					// Uso el token del tope de la pila, para la siguiente evaluacion del while
					if(!ops.empty())
						toptoken = ops.top();

					//
					// Realizo la operacion dentro de los parentesis:
					//
					// Tomo los dos operandos de la pila de values
					//
					int val2 = values.top(); 
                	values.pop(); 
                  
                	int val1 = values.top(); 
                	values.pop(); 
                  	
                  	values.push(apply_operation(val1, val2, toptoken.sym()));
				}
			}

			// Coloco el token en la pila ops
			ops.push(token.sym());
		}

		// Si el token es parentesis izquierdo
		else if(token.sepLeft()){
			ops.push(token.sym());
		}

		// Si el token es un parentesis derecho
		else if(token.sepRight()){

			// Mientras qe el operador en el tope del stack no sea un parentesis izquierdo
			if(!ops.empty()){
				toptoken = ops.top();

				while(!toptoken.sepLeft()){

					//
					// Realizo la operacion dentro de los parentesis:
					//
					// Tomo los dos operandos de la pila de values
					//
					int val2 = values.top(); 
                	values.pop(); 
                  
                	int val1 = values.top(); 
                	values.pop(); 
                  	//

					ops.pop();
					// Se realiza la operacion y se manda a la pila de resultados
					values.push(apply_operation(val1, val2, toptoken.sym()));

					// Se manda el operador a la cola de salida.
					output.push(toptoken.sym());

					// SI el stack se acabo, y no encontro ningun parentesis(while no finaliza):
					if(ops.empty()){
						std::cerr << "equation isn't balanced" << endl;
						exit(1);
					}

					toptoken = ops.top();
				}

				if(toptoken.sepLeft()){
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
	//
	i++;
	}
	// Todo lo que quede en el stack ops, va a parar a la cola
	// Excepto si hay algun parentesis, en ese caso la ecuacion noe sta balanceada
	//
	while(!ops.empty()){

		// Saco el tope de la pila 
		toptoken = ops.top();
		ops.pop();

		// SI queda un parentesis ==> desbalanceado
		//
		if(toptoken.sepLeft() || toptoken.sepRight()){
			cerr << "equation isn't balanced" << endl;
			exit(1);
		}

		output.push(toptoken.sym());

		// Realizo la operacion dentro de los parentesis:
		//
		// Tomo los dos operandos de la pila de values
		//
		int val2 = values.top(); 
        values.pop(); 
                  
        int val1 = values.top(); 
		values.pop(); 

		values.push(apply_operation(val1, val2, toptoken.sym()));

	}
	//
	// Fin de parseo

	cout << "Cola de salida: " << endl;

	while(!output.empty()){
		std::cout << output.front() << endl;
		output.pop();
	}

	cout << values.top() << endl;

	return 0;
}

// ==================================================================================================================================== //
// ==================================================================================================================================== //

bool isBalanced(const string & s){

	char symbol = 0;
	size_t i = 0;
	stack <char> trash;

	while(i < s.length()){
		
		symbol = s[i];

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
