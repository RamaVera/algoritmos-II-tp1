
#include "Images.h"
#include <cstdlib>

using namespace std;

Images::Images() {
	// Valores nulos, puesto que no se tiene imagen alguna
	// 
	this->width = 0;
	this->height = 0;
	this->maxInt = 0;

	// El puntero apunta a null.
	//
	this->imagen = NULL;

	// El header esta vacio
	this->magicNumber = "";
}

Images::Images(int width, int height, int max) {

	if(width <= 0 || height <= 0){
		// Valores por defecto: (Los elegi sin criterio)
		//
		this->width = 10;
		this->height = 10;
		this->maxInt = 255;

	} else
	{
		this->width = width;
		this->height = height;
		this->maxInt = max;
	}

	// Pido memoria para la matriz.
	//
	this->imagen = new int * [this->height];

	for(int filas = 0; filas < height; filas++)
		this->imagen[filas] = new int[width];

	// Inicializo la matriz con 0´s
	//
	for(int filas = 0; filas < height; filas++)
		for(int cols = 0; cols < width; cols++)
			this->imagen[filas][cols] = 0;
	
	// El nombre del header queda en blanco
	this->magicNumber = "";
}

Images::~Images() {
	// Destructor, debe eliminar la memoria pedida
 	//
	for(int i = 0; i < height; i++)
		delete [] this->imagen[i];
	delete [] this->imagen;
	
	// Pongo todos los valores en 0
	this->width = 0;
	this->height = 0;
	this->maxInt = 0;
	this->magicNumber = "";

}

Images::Images(const Images &other) {
	// Constructor copia. Le asigna todos los atributos iguales a other, y
	// Pide memoria para una nueva matriz
	//

	this->width = other.width;
	this->height = other.height;
	this->maxInt = other.maxInt;
	this->magicNumber = other.magicNumber;

	// Pido memoria p/ la matriz
	//
	this->imagen = new int * [this->height];
	for(int filas = 0; filas < height; filas++)
		this->imagen[filas] = new int[width];

	// Inicializo la matriz con los valores de other
	//
	for(int filas = 0; filas < height; filas++)
		for(int cols = 0; cols < width; cols++)
			this->imagen[filas][cols] = other.imagen[filas][cols];
}

const Images& Images::operator=(const Images &other) {
	// Si son iguales, no hace nada.
	//
	if(this == &other)
		return *this;
	
	for(int i = 0; i < this->height; i++)
		delete [] this->imagen[i];
	delete [] this->imagen;

	this->width = other.width;
	this->height = other.height;
	this->maxInt = other.maxInt;
	this->magicNumber = other.magicNumber;

	// Pido memoria p/ la matriz
	//
	this->imagen = new int * [this->height];
	for(int filas = 0; filas < height; filas++)
		this->imagen[filas] = new int[width];

	// Inicializo la matriz
	//
	for(int filas = 0; filas < height; filas++)
		for(int cols = 0; cols < width; cols++)
			this->imagen[filas][cols] = other.imagen[filas][cols];

	return *this;

}

int & Images::operator[](const std::pair<int,int> & index){
	
	// Le asigno a row el primer valor de <int,int> (fila) 
	// Y a col el segundo valor (columna)
	//
	int row = index.first;
	int col = index.second;

	// Si los indices estan afuera devuelve el valor de [0][0]
	if( (row < 0 || row >= this->height) && (col < 0 || col >= this->width) )
		return this->imagen[0][0];

	return this->imagen[row][col];
}

int & Images::operator()(const int & row, const int & col){

	if(row < 0 || col < 0 || row >= this->height || col >= this->width)
		return imagen[0][0];

	return(this->imagen[row][col]);
}

const int & Images::operator()(const int & row, const int & col) const{

	if(row < 0 || col < 0 || row >= this->height || col >= this->width)
		return imagen[0][0];

	return(this->imagen[row][col]);
}



int Images::getWidth() const{
	return this->width;
}

int Images::getMaxInt() const{
	return this->maxInt;
}

int Images::getHeight() const{
	return this->height;
}

int ** Images::getColours() const{
	return this->imagen;
}

std::string Images::getMagicNumber() const{
	return this->magicNumber;
}

bool Images::isPGM(){
	if(magicNumber == "P2")
		return true;
	return false;
}

void Images::printColours(){
	for(int i = 0; i < this->height; i++){
		for(int j = 0; j < this->width; j++){
            std::cout << std::left << std::setw(2) << this->imagen[i][j];
		}
		cout << endl;
	}
}

/*--------------------------------------------------------------------------------*/
/*------------------------------ Manejo de archivos ------------------------------*/

bool pgmParser(int & nline, int & nfils, int & ncols, std::stringstream  * ss , Images * image){
	if(ss->peek() == EOF)
		return true;

	// Chequea si en la linea a leer existe el caracter #. En caso de que exista corta el proceso.
	//
	size_t npos = string::npos;
	if (ss->str().find('#') != npos){
		nline--;
		return true;
	}

	// Primera linea, el header
	//
	if(nline == 1){
		image->magicNumber = ss->str();

		// Elimina el \n o \r que en algunos .pgm aparece
		//
		for (size_t i = 0; i < image->magicNumber.length(); i++){
		    if (		image->magicNumber.c_str()[i] == '\r'
		    		|| 	image->magicNumber.c_str()[i] == '\n'
		    		|| 	image->magicNumber.c_str()[i] == '\r\n'){

		    	image->magicNumber = image->magicNumber.substr(0, i);
		    }
		}
		// Si no es P2, la funcion devuelve falso. Y en ese caso debera cortar la carga del archivo ya que no estamos
		// interesados en otro tipo de formato.
		//
		if( image->magicNumber.compare("P2") != 0 ){
			cerr << "Formato no .pgm" << endl;
			return false;
		}
		return true;
	}

	// Segunda linea. Primero elimina la matriz cargada por el construcutor. Luego lee los nuevos tama;os
	// Por ultimo pide memoria para la matriz con los nuevos tamalios
	//
	if(nline == 2){
		for(int i = 0; i < image->height; i++)
			delete [] image->imagen[i];
		delete [] image->imagen;

		*ss >> image->width >> image->height;

		image->imagen = new int * [image->height];

		for(int filas = 0; filas < image->height; filas++)
			image->imagen[filas] = new int[image->width];

		// Inicializo la matriz con 0´s
		//
		for(int filas = 0; filas < image->height; filas++)
			for(int cols = 0; cols < image->width; cols++)
				image->imagen[filas][cols] = 0;

		return true;
	}

	// Tercera linea, lee el maximo brillo.
	//
	if(nline == 3){
		*ss >> image->maxInt;
		return true;
	}

	// Comienza a leer los colores
	//
	while( nfils < image->height && !ss->eof() ) {
		for(; (ncols < image->width) && !ss->eof(); ncols++){
			if( !(*ss >> image->imagen[nfils][ncols]) )
				ncols--;
		}
    	// Esta verificacion es por si el for corto por el lado de que se llego a eof
		if(ncols == image->width){
			ncols = 0;
			nfils++;
		}
	}

	return true;
}

const Images & Images::loadFile(std::istream * image){

	if( !(image->good()) ){
		cerr << "Fallo al abrir el archivo" << endl;
		//return *this;
		exit(1);
	}
	
	// line es el string donde se almacenera la linea leida en cuestion.
	// nline es el numero de linea. La primer linea es donde esta el magic number, la segunda linea
	// es donde esta la altura y ancho y la tercera linea el maximo brillo.
	// Todas las lineas siguientes corresponden a los valores de intensidad de la imagen. Si hay un comentario
	// se ignora esa linea en cuestion.
	//
	string line;
	int nline = 1;
	int nfils = 0;
	int ncols = 0;

	// Lee linea por linea y la almacena en string, hasta encontrar eof.
	// Luego se llama a la funcion pgmParse, la cual se encargara de procesar que linea es en cuestion
	// y guardar los valores en la clase imagen. Notar que en esa funcion si se encuentra un comentario
	// nline no aumenta. 
	//
	while( getline(*image, line) ){
		stringstream ss(line);
		if(!pgmParser(nline, nfils, ncols, &ss, this))
			return *this;
		nline++;
	}

	return *this;

}

const Images & Images::saveFile(ostream * image){

	if(!image->good()){
		cerr << "Fallo al abrir el archivo" << endl;
		return *this;
	}

	*image << this->magicNumber << endl;
	*image << "# Imagen .pgm generada desde tp0.exe" << endl;
	*image << this->width << " " << this->height << endl;
	*image << this->maxInt << endl;

	for(int fils = 0; fils < this->height; fils++){
		for(int cols = 0; cols < this->width; cols++){
			*image << this->imagen[fils][cols] << endl;
		}
	}

	return *this;
}
