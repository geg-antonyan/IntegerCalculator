/* *** List.h ***
	class List ��� ��������� ���������� ������ � ��������������� ������������ ��������. ����������� ���
	class pair � ���� ��������� ������������� ��� �������� ���� (��������� ������� � ��������) � CommandRepository
	� Observed � ��� ���� ����� ��� ����� �� ����� ����������� �������� == � � ���� ���� ���������������� find.
	���� ���� ������ �� ������������ �� � ��������� � ������ ����� ��� �� ������������ � � �������� 
	��������� ����� ����� ������������ map. �� ��� ������� 1 � ��� �� ������� STL �����������

*/



#ifndef LIST_H
#define LIST_H


#include "Exception.h"


template <typename T, typename S>
class pair
{
public:
	pair(T first, S second) : first(first), second(second) { }
	pair() {}
	~pair() { }
	bool operator==(const T& p) { return this->first == p; }
	T first;
	S second;
};


template <typename T>
class List
{
	template <typename T>
	class Node;

public:
	using iterator = Node<T>*; // ��� ������� ����� :: � ����������� �������� ��������
	using const_iterator = const Node<T>*; // ��� ������� ����� :: ��� ������������ �������� ��������

	List() : head(nullptr), tail(nullptr), size_(0) { } // ����������� �� ���������
	List(int count, T args, ...); // ����������� � ����������(count) ������ ���������� 

	List(const List<T>&); // ����������� �����������(��� ���� ����� �������� �� ��������� � ���������� ��������)
	List<T> operator= (const List<T>&);
	~List<T>() { clear(); } // ����������

	void push_back(const T&);
	void push_front(const T&);


	Node<T>* begin() { return this->head; }
	Node<T>* end() { return this->tail; }

	T pop_back();
	T pop_front();

	Node<T>* insert(iterator, const T&);
	Node<T>* find(const T&) const;

	template <typename F>
	Node<T>* find(const F& value) const; // ��� ������ �� �����

	void erase(const iterator);
	void clear();

	bool empty() const;
	int size() const { return size_; }

	T& operator [] (int);

private:
	Node<T>* head;
	Node<T>* tail;
	int size_;

	// ���� ������ ������ ������ ����� List<T>::iterator(const_iterator) ����� ������ ������ �������� ����� operator*
	template <typename T>
	class Node
	{
	public:
		Node() : next(nullptr), prev(nullptr) { }
		T& operator*() { return val; }
	
	private:
		T val;
		Node<T>* next;
		Node<T>* prev;

	private:
		friend class List<T>; // ��� ��� � ����� ���� ���� using iterator = Node<T>*. ����� ����� ������ � ����� Node �� �������������� ������ �� iterator
		friend Node<T>* incrPstf(Node<T>*& it) { it = it->next; return it; };
		friend Node<T>* incrPref(Node<T>*& it) { Node<T>* r = it; it = it->next; return r; };
		friend Node<T>* decrPstf(Node<T>*& it) { it = it->prev; return it; }
		friend Node<T>* decrPref(Node<T>*& it) { Node<T>* r = it; it = it->prev; return r; }
	};
};



template <typename T>
List<T>::List(int count, T args, ...) : List<T>()
{ // count ���������� ����������
	T* ptr = &args;
	while (count--)
	{
		push_back(*ptr);
		ptr++;
	}
}

template<typename T>
inline List<T>::List(const List<T>& list) :
	size_(0), head(nullptr), tail(nullptr)
{
	Node<T>* r = list.head;
	while (r)
	{
		this->push_back(r->val);
		r = r->next;
	}
}

template<typename T>
inline List<T> List<T>::operator=(const List<T>& list)
{
	this->clear();
	Node<T>* r = list.head;
	while (r)
	{
		this->push_back(r->val);
		r = r->next;
	}
	return List<T>(list);
}

template<typename T>
inline void List<T>::push_back(const T& value)
{
	Node<T>* r = new Node<T>;
	r->val = value;
	if (!head && !tail)
		head = r;
	else
	{
		tail->next = r;
		r->prev = tail;
	}
	tail = r;
	size_++;
}

template<typename T>
inline void List<T>::push_front(const T& value)
{
	Node<T>* r = new Node<T>;
	r->val = value;
	if (!head && !tail)
		tail = r;
	else
	{
		r->next = head;
		head->prev = r;
	}
	head = r;
	size_++;
}

template<typename T>
inline T List<T>::pop_back()
{
	if (!head && !tail) // ����� ������� � empty()
		throw Exception("List ������");

	T i = tail->val;
	Node<T>* r = tail;
	tail = tail->prev;
	if (tail)
		tail->next = nullptr;
	else
		head = nullptr;
	delete r;
	size_--;
	return i;
}

template<typename T>
inline T List<T>::pop_front()
{
	if (!head && !tail) // ����� ������� � empty()
		throw Exception("List ������");
	T i = head->val;
	Node<T>* r = head;
	head = head->next;
	if (head)
		head->prev = nullptr;
	else
		tail = nullptr;
	delete r;
	size_--;
	return i;
}

template<typename T>
inline List<T>::Node<T>* List<T>::insert(List<T>::iterator ptr, const T& value)
{
	if (!ptr) return nullptr;
	Node<T>* r = new Node<T>;
	r->val = value;
	size_++;
	if (ptr == tail)
	{
		tail->next = r;
		r->prev = tail;
		tail = r;
		return r;
	}
	ptr->next->prev = r;
	r->next = ptr->next;
	r->prev = ptr;
	ptr->next = r;
	return r;
}

template<typename T>
inline List<T>::Node<T>* List<T>::find(const T& value) const
{
	Node<T>* r = head;
	while (r)
	{
		if (r->val == value)
			return r;
		r = r->next;
	}
	return nullptr;
}

template<typename T>
template<typename F>
inline List<T>::Node<T>* List<T>::find(const F & value) const
{
	Node<T>* r = head;
	while (r)
	{
		if (r->val == value)
			return r;
		r = r->next;
	}
	return nullptr;
}



template<typename T>
inline void List<T>::erase(const iterator ptr)
{
	if (!ptr) return;
	if (ptr == head) { pop_front(); return; }
	if (ptr == tail) { pop_back(); return; }
	ptr->prev->next = ptr->next;
	ptr->next->prev = ptr->prev;
	size_--;
	delete ptr;
}

template<typename T>
inline void List<T>::clear()
{
	if (!head && !tail)
		return;
	while (head)
		pop_front();
}

template<typename T>
inline T & List<T>::operator[](int i)
{
	int j = 0;
	Node<T> *r;
	if (i <= size_ / 2)
	{
		r = head;
		while (r)
		{
			if (j == i)
				return r->val;
			r = r->next;
			j++;
		}
	}
	else
	{
		j = size_ - 1;
		r = tail;
		while (r)
		{
			if (j == i)
				return r->val;
			r = r->prev;
			j--;
		}
	}
	throw Exception("����� �� ������� List");
}



template<typename T>
inline bool List<T>::empty() const
{
	return !head && !tail;
}



#endif // !LIST_H







