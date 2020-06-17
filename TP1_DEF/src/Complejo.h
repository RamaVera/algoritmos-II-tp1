
#ifndef COMPLEJOS_INCLUDED
#define COMPLEJOS_INCLUDED

#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <iomanip>  // std::setprecision

class Complejo{
private:
	double real;
	double imag;
	//valor absoluto
	double abs;
	//argumento en radianes. Devuelve un valor entre -PI y PI
	double arg;

	// metodos privados para resetear los atributos polares
	// o rectangulares cuando se modifica algun atributo particular
	// mediante otro metodo publico.
	void setPolar(); 
	void setRect();

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
	void setAbs(double);
	void setArg(double);

	//conjugado:
	Complejo conjugar();

	//emitir:
	void printRect();
	void printPolar();

	//SOBRECARGA
	
	//SUMA
	// entre Complejos
	Complejo operator+(const Complejo &);
	// con un real
	Complejo operator+(double);
	friend Complejo operator+ (double, const Complejo &); 


	//RESTA
	// entre Complejos
	Complejo operator-(const Complejo &);
	// por un real
	Complejo operator-(double);
	// de un real por un Complejo
	friend Complejo operator- (double, const Complejo &);


	//PRODUCTO
	// entre Complejos
	Complejo operator*(const Complejo &);
	// por un real
	Complejo operator*(double);
	// de un real por un Complejo
	friend Complejo operator* (double, const Complejo &);


	//DIVISION
	// por un Complejo
	Complejo operator/(const Complejo&);
	// por un real
	Complejo operator/(double);
	// real por un Complejo
	friend Complejo operator/ (double, const Complejo &);

	//POTENCIA
	// por un Complejo
	Complejo operator^(const Complejo&);
	// por un real
	Complejo operator^(double);
	// por un entero
	Complejo operator^(int);
	// real por un Complejo
	friend Complejo operator^ (double, const Complejo &);


	//OPERADOR ASIGNACION
	// entre complejos
	Complejo& operator=(const Complejo&);


	//OPERADOR "IGUAL QUE"
	bool operator==(const Complejo&);
};

//LOGARITMO COMPLEJO
Complejo log(Complejo&);

#endif//COMPLEJOS_INCLUDED