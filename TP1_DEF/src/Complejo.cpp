#include "Complejo.h"

//constructores:
Complejo::Complejo(){
	real = 0;
	imag = 0;
	abs = 0;
	arg = 0;
}

Complejo::Complejo(double x, double y){
	real = x;
	imag = y;
	this->setPolar();
}

Complejo::Complejo(const Complejo & init){
	real = init.real;
	imag = init.imag;
	abs = init.abs;
	arg = init.arg;
}

//destructor:
Complejo::~Complejo(){
	real = 0;
	imag = 0;
	abs = 0;
	arg = 0;
}

//obtener atributos:
double Complejo::getReal(){
	return real;
}

double Complejo::getImag(){
	return imag;
}

double Complejo::getAbs(){
	return abs;
}

double Complejo::getArg(){
	return arg;
}

//setear atributos:
void Complejo::setReal(double val){
	this->real=val;
	setPolar();
}

void Complejo::setImag(double val){
	this->imag=val;
	setPolar();
}

void Complejo::setAbs(double val){
	if(val >= 0)
		this->abs=val;
	else
		this->abs=-val;
	setRect();
}

void Complejo::setArg(double val){
	if(val > M_PI)
		this->arg = std::fmod(val, -M_PI);
	else if(val < -M_PI)
		this->arg = std::fmod(-val, M_PI);
	else 
		this->arg=val;
	setRect();
}

void Complejo::setPolar(){
	abs=sqrt(pow(real,2) + pow(imag,2));
	arg=atan2(imag, real); //calcula atan2(imag/real) y devuelve un valor entre -PI y PI
}

void Complejo::setRect(){
	real=abs*(cos(arg));
	imag=abs*(sin(arg));
}

//CONJUGAR:
Complejo Complejo::conjugar(){
	Complejo aux(real, -imag);
	return aux;
}


//emitir
void Complejo::printRect(){
	std::cout << real << "+j(" << imag << ')' << std::endl;
}

void Complejo::printPolar(){
	std::cout << abs << "*exp(i" << arg << ')' << std::endl;
}


//sobrecarga de operadores:
//SUMA
Complejo Complejo::operator+(const Complejo & right){
	Complejo aux(real + right.real, imag + right.imag);
	return aux;
}

Complejo Complejo::operator+(double right){
	Complejo aux(real + right, imag);
	return aux;
}

Complejo operator+ (double left, const Complejo & right){
	return Complejo(right.real + left, right.imag);
}

//RESTA
Complejo Complejo::operator-(const Complejo & right){
	Complejo aux(real - right.real, imag - right.imag);
	return aux;
}

Complejo Complejo::operator-(double right){
	Complejo aux(real - right, imag);
	return aux;
}

Complejo operator- (double left, const Complejo & right){
	return Complejo(left - right.real, - right.imag );
}

//PRODUCTO
Complejo Complejo::operator*(const Complejo & right){
	Complejo aux(real*right.real - imag*right.imag, real*right.imag + imag*right.real);
	return aux;
}

Complejo Complejo::operator*(double right){
	Complejo aux(right*real, right*imag);
	return aux;
}

Complejo operator* (double left, const Complejo & right){
	return Complejo(left * right.real, left * right.imag);
}


//DIVISION
Complejo Complejo::operator/(const Complejo & right){
	double a = (this->real*right.real + this->imag*right.imag)/pow(right.abs,2);
	double b = (this->imag*right.real - this->real*right.imag)/pow(right.abs,2);
	Complejo aux(a, b);
	return aux;
}

Complejo Complejo::operator/(double right){
	Complejo aux(real/right, imag/right);
	return aux;
}

Complejo operator/ (double left, const Complejo & right){
	Complejo aux = right;
	aux = aux.conjugar()*left/pow(aux.getAbs(),2);
	return aux;
}


//POTENCIA
////// Tenemos que Z1^Z2 == exp(Z2*log(Z1))
	// aux = Z2*log(Z1) = a + ib
	// resultado = |exp(a)| exp(ib)
Complejo Complejo::operator^(const Complejo & right){


	//utilizo result como auxiliar tambien, pero despues se sobrescribe
	Complejo result(real, imag), aux(right);
	if(aux.getImag() == 0){
		int n = aux.getReal();
		//std::cout << "n = " << n << std::endl;
		return result ^ (n);
	}

	aux = aux * log(result);

	//se setea mediante coordenadas polares
	result.setAbs( exp(aux.getReal()) );
	result.setArg( aux.getImag() );

	return result;
}

Complejo Complejo::operator^(double right){
	Complejo result, aux(real, imag);
	aux = right * log(aux);

	//se setea mediante coordenadas polares
	result.setAbs( exp(aux.getReal()) );
	result.setArg( aux.getImag() );

	return result;	
}

Complejo Complejo::operator^(int n){
	Complejo resultado(1, 0);
	//Acumulador de las potencias
	Complejo acum = *this;

	if(n<0){
		//invierto el num complejo
		acum = 1/acum;
		//busco la potencia de este numero
		return acum^(-n);
	}
	//Empezamos del LSB al MSB
	while(n){
		//si vale 1, actualizamos el resultado con el nuevo valor del acum
		if(n&1)
			resultado = resultado * acum;
		//contamos el bit
		acum = acum * acum;
		//shifteamos a la derecha a n, desechando el LSB por el siguiente
		n >>= 1;
	}

	return resultado;
}

Complejo operator^ (double left, const Complejo & right){
	Complejo result, aux(right);
	aux = aux * log(left);

	//se setea mediante coordenadas polares
	result.setAbs( exp(aux.getReal()) );
	result.setArg( aux.getImag() );

	return result;	
}

//ASIGNACION
Complejo& Complejo::operator=(const Complejo & right){
	real = right.real;
	imag = right.imag;
	abs = right.abs;
	arg = right.arg;
	return *this;
}

//IGUAL A
bool Complejo::operator==(const Complejo & right){
	if(real == right.real && imag == right.imag)
		return true;

	return false;
}

//POR FUERA DE LA CLASE:
//LOGARITMO COMPLEJO
Complejo log(Complejo & z){
	Complejo aux;
	aux.setReal( log(z.getAbs()) );
	aux.setImag( z.getArg() );
	return aux;
}