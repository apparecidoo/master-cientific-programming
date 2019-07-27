#include <iostream>
#include "linked_list.h"

#ifndef QUEUE_DYNAMIC_H
#define QUEUE_DYNAMIC_H

using namespace std;

template <class T>
class DynamicQueue : public LinkedList<T> {
public:
	DynamicQueue();
	~DynamicQueue();

	void enqueue(T value); // insert a value in the queue
	T dequeue(); // remove the last value in the queue
	void test() override;
	void print() override;
};

template <class T>
DynamicQueue<T>::DynamicQueue()
{
}

template <class T>
DynamicQueue<T>::~DynamicQueue()
{
}

template <class T>
void DynamicQueue<T>::enqueue(T value)
{
	this->addLast(value);
}

template <class T>
T DynamicQueue<T>::dequeue()
{
	T value = this->removeFirst();

	return value;
}

template <class T>
void DynamicQueue<T>::test()
{
	
}

template <class T>
void DynamicQueue<T>::print()
{

}


#endif