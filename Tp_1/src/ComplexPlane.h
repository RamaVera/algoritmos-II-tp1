#ifndef COMPLEXPLANE_H_
#define COMPLEXPLANE_H_

#include "Complejo.h"
#include "Images.h"

class ComplexPlane {
private:
	Complejo comp; //número complejo guardado
	Images image; //imagen utilizada
	int row; //fila y
	int col; //columna guardadas para el número complejo entregado

public:
	ComplexPlane();
	ComplexPlane(const Images &); //guarda los datos de una imagen para tener sus dimensiones
	~ComplexPlane(); //destructor
	ComplexPlane(const ComplexPlane &); // constructor copia
	ComplexPlane& operator=(const ComplexPlane &); //sobrecarga de la asignación

	
	Complejo getComp() const;
	Images getImage() const;
	int getRow() const;
	int getCol() const;

	void index2Comp(int, int);
	void comp2Index(Complejo &);

};

#endif /* COMPLEXPLANE_H_ */
