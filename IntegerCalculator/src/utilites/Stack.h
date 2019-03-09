/*  *** Stack.h ***
	 Шаблонный класс Stack имеет возможность добовлении в голову удалении из головы ... и другие стандартые 
	 методы для стека. Node реализован внутри класс в приват секции так как доступ из вне не придусмотрен(точнее
	 не надо вообще)
	 Определение методов в самом файле Stack.h так как класс шаблонный
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
		T inf; // уничтожается деструтором стека
		Node<T>* next; // уничтожается деструтором стека
	};

	int size_;
	Node<T>* head;

	// в программе мне это не понадобился и я решил закрыть так как при копировании и присвоении просто бутут
	// переданы указатели а это черевато проблемамы. если надо будет то можно будет легко реализвать как сделана в
	// List. хотя и там я не использовал но по задании есть писать двусвязной лист и поэтому я это дополнял там
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








