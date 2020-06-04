/*
 Clase Images.
 En ella se guardan los datos de una imagen con formato .pgm
 */

#ifndef IMAGES_H_
#define IMAGES_H_

// Librerias para manejo de archivos 
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>

#include <string.h>
#include <cstdlib>


class Images {
private:
	// Ancho de la imagen
	int width;
	
	// Altura de la imagen
	int height;
	
	// Intensidad maxima de la imagen
	int maxInt; 
	
	// Matriz donde se almacenan los valores de intensidad
	int ** imagen; 
	
	// El header. Si es P2, el formato es pgm
	std::string magicNumber; 

public:
	// Constructor por defecto, inicializa en 0
	Images();
	
	// Constructor, se le pasa como argumento, ancho, alto y maxima intensdad
	Images(int, int, int); 
	
	// Destructor, debera liberar la memoria de la matriz.
	~Images(); 
	
	// Constructor por copia
	Images(const Images &other);

	// Sobreacarga del operador =
	const Images& operator=(const Images &other);
	
	// Sobrecarga del operador []
	int & operator[](const std::pair<int,int> &);
	
	// Sobrecarga operador ()
	//
	int & operator()(const int &, const int &);
	const int & operator()(const int &, const int &) const;

	// Funcion para procesar cada linea del archivo con formato .pgm (la usa el metodo de loadFile)
	friend bool pgmParser(int & , int &, int &, std::stringstream  * , Images * );
	
	// Carga un archivo .pgm.
	const Images & loadFile(std::istream * ); 
	
	// Se guarda la instancia de Images en un archiv formato .pgm
	const Images & saveFile(std::ostream * ); 

	// Obtencion de los atributos
	int getMaxInt() const;
	int getWidth() const;
	int getHeight() const;
	std::string getMagicNumber() const;
	int ** getColours() const;
	
	// Imprime la matriz
	void printColours();
	
	// Devuelve true si la instanciatiene almacenado datos de una imagen pgm 
	bool isPGM();
};

#endif /* IMAGES_H_ */
