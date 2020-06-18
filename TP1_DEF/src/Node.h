#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#ifndef NULL
#define NULL 0
#endif // NULL

template<class T>
class Node{
private:
	T data;
	Node<T> *next;

public:
	// Nodo inicializado con dato y siguiente nulo:
	Node(T);

	// Metodos Get:
	T getData();
	Node<T>* getNext();

	// Modificar Data
	void changeData(T);
	// Modificar Next
	void changeNext(Node<T>*);


};

template<class T>
Node<T>::Node(T data){
	this->data = data;
	this->next = NULL;
}

template<class T>
T Node<T>::getData(){
	return this->data;
}

template<class T>
Node<T>* Node<T>::getNext(){
	return this->next;
}

//changeData generico
template<class T>
void Node<T>::changeData(T newData){
	this->data = newData;
}

/*
//si el tipo de dato es un char*, habría que liberar memoria.
// [se pueden crear otros casos particulares]

template<>
void Node<char*>::changeData(char* newData){
	if(this->data)
		delete[] this->data;
	this->data = newData;
}
*/

template<class T>
void Node<T>::changeNext(Node<T>* newNext){
	this->next = newNext;
}

#endif // NODE_H_INCLUDED