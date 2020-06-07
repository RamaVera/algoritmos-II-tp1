#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include "Node.h"
/* IMPLEMENTACIÓN DE LISTA CON CURSOR */

template<class T>
class List{
private:
	Node<T>* first;
	unsigned int size;
	Node<T>* cursor;

public:
	//Post: Lista vacía
	List();
	//Post: Lista copiada
	List(List<T> & otherList);
	//Post: Libera los recursos asociados a la Lista
	~List();

	//Post: Devuelve True si está vacía
	bool isEmpty();
	//post: Devuelve la cantidad de elementos que tiene la lista
	unsigned int count();

	//post: Agrega elemento al final de la lista
	// posición: count() + 1
	void append(T item);
	//post: Agrega elemento al inicio de la lista
	// posición: 1
	void prepend(T item);
	//post: Agrega elemento en la posición solicitada
	// posición: conjunto [1, size]
	void insert(T item, unsigned int pos);
	//post: Agrega todos los elementos de otherList al final de la lista
	// posición: count() + 1
	void extend(List<T> & otherList);

	//pre: posición pertenece al intervalo [1, size]
	//post: devuelve el elemento en la posición indicada
	T get(unsigned int pos);
	//pre: posición pertenece al intervalo [1, size]
	//post: cambia elemento de posición indicada por elemento nuevo
	void change(T item, unsigned int pos);
	//pre: posición pertenece al intervalo [1, size]
	//post: remueve de la List el elemento en la posición indicada
	void remove(unsigned int pos);

	//CURSOR:
	//post: deja cursor de List preparado para hacer un nuevo recorrido
	void initCursor();
	/* El siguiente meotdo permite moverse de un nodo al siguiente usando el cursor */
	//pre: se ha iniciado el recorrido mediante el método initCursor()
	//post: El valor de retorno indica si el cursor quedó posicionado sobre un elemento o no
	//		(en caso de que la List esté vacía o no existan más elementos por recorrer.)
	bool moveCursor();
	//Pre: El cursor está posicionado sobre un elemento de la lista
	//Post: Devuelve el elemento en la posición del cursor
	T getCursor();

private:
	//pre: posición pertenece al intervalo [1, size]
	//post: devuelve el nodo en la posición indicada
	Node<T>* getNode(unsigned int pos);

};

template<class T> 
List<T>::List(){
	this->first=NULL;
	this->size=0;
	this->cursor=NULL;
}

template<class T>
List<T>::List(List<T> & otherList){
	this->primero=NULL;
	this->size=0;
	this->cursor=NULL;

	//copiamos elementos
	this->extend(otherList);
}

template<class T>
List<T>::~List(){
	//mientras siga habiendo un elemento, eliminar el nodo
	while(this->first != NULL){
		Node<T>* removed = this->first;
		this->first = removed->getNext();
		delete removed;
	}
}

template<class T>
bool List<T>::isEmpty(){
	return(this->size == 0);
}

template<class T>
unsigned int List<T>::count(){
	return this->size;
}

template<class T>
void List<T>::append(T item){
	this->insert(item, this->size + 1);
}

template<class T>
void List<T>::prepend(T item){
	this->insert(item, 1);
}

template<class T>
void List<T>::insert(T item, unsigned int pos){
	//si la posición es válida
	if((pos > 0) && (pos <= this->size + 1)){
		Node<T>* newNode = new Node<T>(item);
		//Se verifica si hay que insertar al principio
		if(pos == 1){
			newNode->changeNext(this->first);
			this->first=newNode;
		}
		else{
			Node<T>* previous = this->getNode(pos-1);
			newNode->changeNext(previous->getNext());
			previous->changeNext(newNode);
		}

		//aumenta el tamanio
		this->size++;
		
		//cualquier recorrido del cursor queda invalidado
		this->initCursor();
	}
}

template<class T>
void List<T>::extend(List<T> & otherList){
	// Inicializamos cursor de otherList en NULL
	otherList.initCursor();

	// Mientras exista un nodo apuntado por el cursor, se agrega al final el dato del nodo apuntado
	while(otherList.moveCursor()){
		this->append(otherList.getCursor());
	}
}

template<class T>
T List<T>::get(unsigned int pos){
	T item;
	//si la pos es válida, obtener data del nodo ubicado en la posición
	if((pos>0) && (pos <= this->size))
		item = this->getNode(pos)->getData();

	return item;
}

template<class T>
void List<T>::change(T item, unsigned int pos){
	if((pos>0) && (pos <= this->size))
		this->getNode(pos)->changeData(item);
}

template<class T>
void List<T>::remove(unsigned int pos){
	if((pos>0) && (pos <= this->size)){
		Node<T>* removed;

		if(pos==1){
			removed = this->first;
			this->first=removed->getNext();
		}
		else{
			Node<T>* previous = this->getNode(pos-1);
			removed = previous->getNext();
			previous->changeNext(removed->getNext());
		}

		//se elimina el nodo removido y se reduce el tamanio de la lista
		delete removed;
		this->size--;

		//se invalida cualquier movimiento del cursor
		this->initCursor();
	}
}

template<class T>
void List<T>::initCursor(){
	this->cursor=NULL;
}

template<class T>
bool List<T>::moveCursor(){
	//si está en null, moverlo al primero.
	// en caso contrario, moverlo al siguiente nodo.
	if(this->cursor == NULL)
		this->cursor=this->first;
	else
		this->cursor=this->cursor->getNext();

	return (this->cursor != NULL);
}

template<class T>
T List<T>::getCursor(){
	T item;

	if(this->cursor != NULL)
		item = this->cursor->getData();

	return item;
}

template<class T>
Node<T>* List<T>::getNode(unsigned int pos){
	Node<T>* current = this->first;

	//recorro secuencialmente la lista
	for(unsigned int i = 1; i < pos; i++)
		current = current->getNext();

	return current;
}

#endif // LIST_H_INCLUDED