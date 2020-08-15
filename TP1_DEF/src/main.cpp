//============================================================================
// Name        : main.cpp
// Author      : Nacachian, Urquiza, Vera
// Version     : 1.1.1
// Description : Trabajo Practico Nro. 1
//============================================================================


#include <iostream>
#include "cmdline.h"
#include "Images.h"
#include "Complejo.h"
#include "ComplexPlane.h"
#include "ComplexTransform.h"

using namespace std;


/*=====================================================================================*/
// 									PROTOTIPOS
/*=====================================================================================*/


static void opt_input(string const &);
static void opt_output(string const &);
static void opt_function(string const &);
static void opt_help(string const &);
void transformar_imagen(const Images & origen, Images & destino);
static bool openOutputFile();
 

/*=====================================================================================*/
// 								ELEMENTOS GLOBALES
/*=====================================================================================*/

static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{1, "f", "function", NULL, opt_function, OPT_MANDATORY},
	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
	{0, },
};
//typedef enum token_functions {EXPZ, Z}; //, COSZ, SINZ };
const string functions[] = {"exp(z)", "z"}; //, "cos(z)", "sin(z)" };

static istream* iss = 0;
static ostream* oss = 0;
static fstream ifs;
static fstream ofs;

static string outputFileName;



/*====================================================================================*/
//									MAIN
/*====================================================================================*/


int main(int argc, char * const argv[]){

	//------Valido Argumentos ------//
	cmdline cmdl(options);
	cmdl.parse(argc, argv);

	//------Creo Imagenes de origen y destino ------//
	Images origen;

	std::cout << "Procesando imagen..." << std::endl;	
	if(iss == &cin)
		std::cout << "Ingrese la imagen por consola:" << std::endl;

	//------Cargo la imagen de entrada ------//
	if(!origen.loadFile(iss)){

		// Si en el proceso hubo algun error inesperado (ie. la entrada es cin, la salida es un archivo
		// y lo que se ingresa no es tipo pgm)
		//
		ifs.close();
		ofs.close();
			
		return 1;

	} else {

		//------SI la entrada es pgm valida ------//

		Images destino(origen);

		//------Trasnformo y guardo ------//
		transformar_imagen(origen,destino);

		//------Se abre en funcion si el archivo es PGM o no ------//
		if(!openOutputFile())
			return 1;

		std::cout << "Guardando imagen..." << std::endl;
		destino.saveFile(oss);

	}

	ifs.close();
	ofs.close();

	std::cout << "La transformacion fue exitosa." << std::endl;

	return 0;
}



/*====================================================================================*/
// 						FUNCIONES INVOCADAS EN EL MAIN
/*====================================================================================*/


void transformar_imagen(const Images & origen, Images & destino){

	if(&origen == &destino)
		return;

	Complejo z_aux(0,0);
	ComplexPlane plano(origen);
	ComplexTransform transformada;

	int ancho = origen.getWidth();
	int altura = origen.getHeight();

	for(int i = 0; i < altura; i++){
		for(int j = 0; j < ancho; j++){
			//guarda la coordenada en forma de num complejo
			plano.index2Comp(i, j); 
			z_aux = plano.getComp();

			//calcula la anti transformada
			transformada.fun(z_aux);
			z_aux = transformada.getOutput();
	
			//guarda los indices del pixel del origen
			plano.comp2Index(z_aux);

			//guarda vacío si algun subindice es negativo; caso contrario, guarda el pixel
			if(plano.getRow() < 0 || plano.getCol() < 0)
				destino(i,j)=0; 
			else
				destino(i,j) = origen(plano.getRow(),plano.getCol());

		}
	}

	return;
}

//------------------ Callbacks de CMDLINE ------------------------------//

static void
opt_input(string const &arg)
{
	// Si el nombre del archivos es "-", usaremos la entrada
	// est?dar. De lo contrario, abrimos un archivo en modo
	// de lectura.
	//
	if (arg == "-") {
		iss = &cin;		// Establezco la entrada estandar cin como flujo de entrada
		cout<<"La direccion del archivo Origen es : Cin (Entrada Standar)" <<endl;

	}
	else {
		ifs.open(arg.c_str(), ios::in); // c_str(): Returns a pointer to an array that contains a null-terminated
										// sequence of characters (i.e., a C-string) representing
										// the current value of the string object.
		iss = &ifs;
		cout<<"La direccion del archivo Origen es :"<< arg.c_str() <<endl;

	}

	// Verificamos que el stream este OK.
	//
	if (!iss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		std::abort();
	}
}

static void
opt_output(string const &arg)
{

	// Si el nombre del archivos es "-", usaremos la salida
	// est?dar. De lo contrario, abrimos un archivo en modo
	// de escritura.
	//
	outputFileName = arg.c_str();

	if (arg == "-") {
		//oss = &cout;	// Establezco la salida estandar cout como flujo de salida
		cout<< "La direccion del archivo Destino es: Cout (Salida Standar)" << endl;
	} else {
		//ofs.open(arg.c_str(), ios::out);
		//oss = &ofs;
		cout<< "La direccion del archivo Destino es: "<< arg.c_str() <<endl;
	}

}

static void
opt_function(string const &arg)
{
	stringstream iss(arg);
	cout<< "La transformacion elegida es f(z)= " <<arg.c_str() <<endl;

	// Intentamos extraer el factor de la l?ea de comandos.
	// Para detectar argumentos que ?nicamente consistan de
	// n?meros enteros, vamos a verificar que EOF llegue justo
	// despu? de la lectura exitosa del escalar.
	//
	string transformString;
	//iss >> transformString;
	transformString = iss.str();
	if (iss.bad()) {
		cerr << "cannot read integer factor."
			 << endl;
		std::abort();
	}

	TransformStatus Status = ComplexTransform::isGoodExpresion(transformString);
	switch(Status)
	{
	case TransformStatus::funtionIsOk:
		{
		cout << "La funcion se ingreso correctamente "<< endl;
		string parsedString = ComplexTransform::parseExpresion(transformString);
		//cout<< "La transformacion elegida es f(z)= " << parsedString <<endl;
		ComplexTransform::setTransform(parsedString);
		break;
		}
	case TransformStatus::functionIsNotBalanced:
		cerr << "La funcion ingresada no esta balanceada "<< endl;
		std::abort();
		break;
	case TransformStatus::functionHasOperatorError:
		cerr <<" La funcion ingresada tiene un error de sintaxis debido a un caracter "<< endl;
		std::abort();
		break;
	default:
		cerr <<" Error desconocido "<< endl;
		std::abort();
	}
}

static void
opt_help(string const &arg)
{
	cout << "cmdline [-f function] [-i file] [-o file]" << endl;
	cout << "Funciones Admitidas: exp, Re, Im, log, cos, sen " << endl;
	cout << "Las expresiones matematicas no deben tener espacios en blanco " << endl;
	std::abort();
}


static bool
openOutputFile(){


	if(outputFileName == "-")
	{
		oss = & cout;
	}
	else{ 
		ofs.open(outputFileName.c_str(), ios::out);
		oss = &ofs;	

	}
	// Verificamos que el stream este OK.
	//
	if (!oss->good()) {
		cerr << "cannot open "
		<< outputFileName
		<< "."
		<< endl;

		ifs.close();
		return false;

	}	

	return true;

}