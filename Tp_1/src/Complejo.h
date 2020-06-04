
#ifndef COMPLEJOS_INCLUDED
#define COMPLEJOS_INCLUDED

#include <iostream> //lo dejamos?
#include <cmath>
#include <iomanip>  // std::setprecision (para qué?)

class Complejo{
private:
	double real;
	double imag;
	double abs; //valor absoluto
	double arg; //argumento en radianes. Devuelve un valor entre -PI y PI

	void setPolar();

public:
	//constructores:
	Complejo();
	Complejo(double, double);
	Complejo(const Complejo &);
	//destructor:
	~Complejo();
	//obtener atributos:
	double getReal();
	double getImag();
	double getAbs();
	double getArg();
	//setear atributos:
	void setReal(double);
	void setImag(double);

	//conjugado:
	Complejo conjugar();

	//emitir:
	void printRect();
	void printPolar();

	//sobrecarga de operadores
	Complejo operator+(const Complejo &); //suma entre Complejos
	Complejo operator+(double); //suma con un real
	friend Complejo operator+ (double, const Complejo &); 

	Complejo operator-(const Complejo &); //resta ente Complejos
	Complejo operator-(double); //resta por un real
	friend Complejo operator- (double, const Complejo &);

	Complejo operator*(const Complejo &); //producto entre Complejos
	Complejo operator*(double); //producto por un real (escalar)
	friend Complejo operator* (double, const Complejo &);

	Complejo operator/(const Complejo&); //división entre Complejos
	Complejo operator/(double); //división por un real (escalar)


	Complejo& operator=(const Complejo&); //asignación entre Complejos
	bool operator==(const Complejo&); // comparación entre Complejos
};


#endif//COMPLEJOS_INCLUDED