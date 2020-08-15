#include "ComplexPlane.h"
using namespace std;

ComplexPlane::ComplexPlane(){
	row = col = 0;
	this->comp.setReal(0);
	this->comp.setImag(0);
}

ComplexPlane::ComplexPlane(const Images & original){
	row = col = 0;
	this->image = original;
	this->comp.setReal(0);
	this->comp.setImag(0);
}

ComplexPlane::~ComplexPlane(){
	
}

ComplexPlane::ComplexPlane(const ComplexPlane & init){
	this->comp = init.getComp();
	this->image = init.getImage();
	this->row = init.getRow();
	this->col = init.getCol();
}

ComplexPlane& ComplexPlane::operator=(const ComplexPlane & right){
	comp = right.getComp();
	image = right.getImage();
	row = right.getRow();
	col = right.getCol();
	return *this;
}

Complejo ComplexPlane::getComp() const {
	return this->comp;
}

Images ComplexPlane::getImage() const {
	return this->image;
}

int ComplexPlane::getRow() const {
	return this->row;
}

int ComplexPlane::getCol() const {
	return this->col;
}

//guarda en this->comp un número complejo correspondiente a la posición solicitada de la imagen.
void ComplexPlane::index2Comp(int row, int col){
	Complejo z(0,0);

	if(0 > row || row >= image.getHeight() || 0 > col || col >= image.getWidth()) //valor inválido
		this->comp = z;

	else
	{
		/* Se divide la matriz en cuatro regiones:
			se calcula el valor de la fila y columna "central" de la matriz.
			se reduce a un número entero puesto que, si se tiene una matriz cuadrada,
			no existirá un centro alcanzable. Pero igualmente se puede operar corriendo
			dicho centro un paso hacia atrás.
		*/
		int rowCentral = this->image.getHeight()/2;
		int colCentral = this->image.getWidth()/2;
		this->row = row;
		this->col = col;

		if(row < rowCentral)
			z.setImag( (1-(double)row/rowCentral) );



		if(row >= rowCentral)
			z.setImag( (-1 + (double)((this->image.getHeight() - 1) - row)/(double)rowCentral) );

		
		if(col < colCentral)
			z.setReal( (-1+(double)col/colCentral) );

		if(col >= colCentral)
			z.setReal( (1 - (double)((this->image.getWidth()-1) - col)/(double)colCentral) );

		this->comp = z;
	}

}

//guarda en row y col los índices asociados al número complejo entregado
void ComplexPlane::comp2Index(Complejo & z){
	long double real = z.getReal();
	long double imaginario = z.getImag();
	
	//si sale por fuera del plano, se guardan valores negativos de col y row 
	if(std::round(abs(real)) > 1.0 || std::round(abs(imaginario)) > 1.0)
	{
		this->row = -1;
		this->col = -1;
	} 

	else
	{
		int rowCentral = this->image.getHeight()/2;
		int colCentral = this->image.getWidth()/2;
		this->comp = z;

		//se aplican las funciones inversas a las utilizadas en index2comp();
		if(real <= 0)
			this->col = std::round(colCentral*(real+1));

		if(real > 0)
			this->col = std::round((real-1)*colCentral + (this->image.getWidth()-1));

		if(imaginario >= 0)
			this->row = std::round(rowCentral*(1-imaginario));

		if(imaginario < 0)
			this->row = std::round((this->image.getHeight()-1) - (imaginario+1)*rowCentral);
	}

}

