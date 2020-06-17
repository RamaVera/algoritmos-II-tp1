
OBJECTS = Complejo.o main.o cmdline.o ComplexPlane.o ComplexTransform.o Images.o Token.o # Los archivos compilados individuales
PROGR = main.exe # Nombre del archivo ejecutable
CPPFLAGS = -g -Wall # -g opcion de g++ para debugear

# Compiladores #
CC = g++ -std=c++11 # Para linux
CCW = i686-w64-mingw32-g++ --static # Para windows (requiere mingw32)

$(PROGR) : $(OBJECTS)
	$(CC) $(CPPFLAGS) -o $(PROGR) $(OBJECTS)
main.o : main.cpp List.h Stack.h Node.h
	$(CC) $(CPPFLAGS) -c main.cpp
Complejo.o : Complejo.cpp Complejo.h
	$(CC) $(CPPFLAGS) -c Complejo.cpp
ComplexTransform.o : ComplexTransform.cpp ComplexTransform.h
	$(CC) $(CPPFLAGS) -c ComplexTransform.cpp
ComplexPlane.o : ComplexPlane.cpp ComplexPlane.h
	$(CC) $(CPPFLAGS) -c ComplexPlane.cpp
Images.o : Images.cpp Images.h
	$(CC) $(CPPFLAGS) -c Images.cpp
cmdline.o : cmdline.cpp cmdline.h
	$(CC) $(CPPFLAGS) -c cmdline.cpp
Token.o : Token.cpp Token.h
	$(CC) $(CPPFLAGS) -c Token.cpp

clean:
	rm -f core $(PROGR) $(OBJECTS)
all: main.exe
	$(CC) $(CPPFLAGS) -o $(PROGR) $(OBJECTS)
run : $(PROGR)
	valgrind --leak-check=yes ./$(PROGR)
