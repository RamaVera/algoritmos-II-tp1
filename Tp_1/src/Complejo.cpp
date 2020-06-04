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
	real=val;
	setPolar();
}

void Complejo::setImag(double val){
	imag=val;
	setPolar();
}

void Complejo::setPolar(){
	abs=sqrt(pow(real,2) + pow(imag,2));
	arg=atan2(imag, real); //calcula atan2(imag/real) y devuelve un valor entre -PI y PI
}


//conjugar
Complejo Complejo::conjugar(){
	Complejo aux(real, -imag);
	return aux;
}


//emitir
void Complejo::printRect(){
	std::cout << real << "+j(" << imag << ')' << std::endl;
}

void Complejo::printPolar(){
	std::cout << abs << "*exp(j" << arg << ')' << std::endl;
}


//sobrecarga de operadores:
//suma
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

//resta
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

//producto
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


//división
Complejo Complejo::operator/(const Complejo & right){
	double a = (real*right.real - imag*right.imag)/pow(right.abs,2);
	double b = (real*right.imag + imag*right.real)/pow(right.abs,2);
	Complejo aux(a, b);
	return aux;
}

Complejo Complejo::operator/(double right){
	Complejo aux(real/right, imag/right);
	return aux;
}

//asignación
Complejo& Complejo::operator=(const Complejo & right){
	real = right.real;
	imag = right.imag;
	abs = right.abs;
	return *this;
}

//comparación
bool Complejo::operator==(const Complejo & right){
	if(real == right.real && imag == right.imag)
		return true;

	return false;
}