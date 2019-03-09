/*  *** Stack.h ***
	 ��������� ����� Stack ����� ����������� ���������� � ������ �������� �� ������ ... � ������ ���������� 
	 ������ ��� �����. Node ���������� ������ ����� � ������ ������ ��� ��� ������ �� ��� �� ������������(������
	 �� ���� ������)
	 ����������� ������� � ����� ����� Stack.h ��� ��� ����� ���������
*/


//#pragma once
#ifndef STACK_H
#define STACK_H

#include "Exception.h"

template <typename T>
class Stack
{
public:
	Stack() : head(nullptr), size_(0) { }
	~Stack();
	void push(const T&);
	T pop();
	T top();
	void clear();
	bool empty();
	void reverse();
	int size();

private:
	template <typename T>
	class Node
	{
	public:
		Node() : next(nullptr) { }
		~Node() { }
		T inf; // ������������ ����������� �����
		Node<T>* next; // ������������ ����������� �����
	};

	int size_;
	Node<T>* head;

	// � ��������� ��� ��� �� ����������� � � ����� ������� ��� ��� ��� ����������� � ���������� ������ �����
	// �������� ��������� � ��� �������� ����������. ���� ���� ����� �� ����� ����� ����� ���������� ��� ������� �
	// List. ���� � ��� � �� ����������� �� �� ������� ���� ������ ���������� ���� � ������� � ��� �������� ���
	Stack(const Stack<T>&) = delete;
	Stack(Stack<T>&&) = delete;
	Stack<T>& operator=(const Stack<T>&) = delete;
	Stack<T>& operator=(Stack<T>&&) = delete;
};

template<typename T>
inline Stack<T>::~Stack()
{
	this->clear();
}

template<typename T>
inline void Stack<T>::push(const T& x)
{
	Node<T> * p = new Node<T>;
	p->inf = x;
	p->next = head;
	head = p;
	size_++;
}


template<typename T>
inline T Stack<T>::pop()
{
	if (empty()) throw Exception("STACK::ERROR::POP _ Stack is empty");
	T x = head->inf;
	Node<T> *p = head;
	head = head->next;
	delete p;
	size_--;
	return x;
}

template<typename T>
inline T Stack<T>::top()
{
	if (empty()) throw Exception("STACK::ERROR::TOP _ Stack is empty");
	return head->inf;
}

template<typename T>
inline void Stack<T>::clear()
{
	if (empty()) return;
	while (head)
		pop();
}

template<typename T>
inline bool Stack<T>::empty()
{
	return !head;
}

template<typename T>
inline void Stack<T>::reverse()
{
	int tempsize = size_;
	Node<T> *r = nullptr;
	while (head)
	{
		T x = pop();
		Node<T> * p = new Node<T>;
		p->inf = x;
		p->next = r;
		r = p;
	}
	head = r;
	size_ = tempsize;
}

template<typename T>
inline int Stack<T>::size()
{
	return size_;
}



#endif // !STACK_H








