#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "Node.h"
/* IMPLEMENTACIÓN DE STACK */
template<class T>
class Stack{
private:
	Node<T>* first;
	unsigned int size;

public:
	Stack();
	Stack(Stack<T> & otherStack);
	~Stack();

	bool isEmpty();
	unsigned int count();

	void push(T item);
	void pop();

	T top();

	void multiPush(Stack<T> & otherStack);
};

template<class T>
void copyReverse(Stack<T>& source, Stack<T>& dest){
	while(!source.isEmpty()){
		dest.push(source.top());
		source.pop();
	}
}

template<class T>
void copyReverse(Stack<T>& source, Stack<T>& dest1, Stack<T>& dest2){
	while(!source.isEmpty()){
		dest1.push(source.top());
		dest2.push(source.top());
		source.pop();
	}
}

template<class T>
Stack<T>::Stack(){
	this->first=NULL;
	this->size=0;
}

template<class T>
Stack<T>::~Stack(){
	while(this->first != NULL){
		Node<T>* removed = this->first;
		this->first = removed->getNext();
		delete removed;
	}
}

template<class T>
Stack<T>::Stack(Stack<T> & otherStack){
	this->first=NULL;
	this->size=0;

	//copiamos elementos
	this->multiPush(otherStack);
}

template<class T>
bool Stack<T>::isEmpty(){
	return(this->size == 0);
}

template<class T>
unsigned int Stack<T>::count(){
	return this->size;
}

template<class T>
void Stack<T>::push(T item){
	Node<T>* newNode = new Node<T>(item);
	newNode->changeNext(this->first);
	this->first=newNode;
	this->size++;
}

template<class T>
void Stack<T>::pop(){
	if(this->first != NULL){
		Node<T>* removed;
		removed = this->first;
		this->first=removed->getNext();

		delete removed;
		this->size--;
	}
}

template<class T>
T Stack<T>::top(){
	T item;
	
	if(this->first)
		item = this->first->getData();

	return item;
}

template<class T>
void Stack<T>::multiPush(Stack<T> & source){
	Stack tmp;
	copyReverse(source, tmp);
	copyReverse(tmp, source, *this);
}

#endif