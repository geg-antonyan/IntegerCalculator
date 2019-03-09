/* *** Data.h
	Data ýòî Singleton class êîòîðûé õðàíèò äàííûå(÷èñëà) â ïðîöåññå ââîäà ÷èñåë è îïåðàöèè íàä íèìè
	èìååò ìåòîäû êîòîðûå ÷à÷èòóþ ðåàëèçóþòñÿ êîíòåéíåðîì ãäå õðàíÿòñÿ ñàìû ÷èñëû. è åñëè íàì íàäî áóäåò
	ìåíÿòü êîíòåéíåð òî ñàì èíòåðôåéñ êëàññà îñòàíåòñÿ íåçàòðîíóòûì. Data êàê è UserInterfac ÿâëÿåòñÿ èçäàòåëåì 
	ñîáûòèè ïîýòó 
	Ðåàëèçàöèÿ â Data.cpp
*/
//#pragma once

#ifndef DATA_H
#define DATA_H


#include "../utilites/List.h"
#include "../utilites/Observed.h"

#include <string>

class Integer;

class Data : protected Observed
{
public:
	static Data& Instance();

	void push(Integer, bool raiseEvent = true);
	Integer pop(bool raiseEvent = true);
	Integer top();
	void swapTop();
	void clear(bool raiseEvent = true);
	bool empty();
	int size();
	List<Integer> getElements(int n);
	void changeNumSystem(int);
	int getNumSystem() { return numSystem; }
	using Observed::addObserver;
	using Observed::removeObserver;

	static const std::string dataChanged;

private:
	List<Integer> data_;

	static int numSystem;
	

	Data();
	~Data() { }
	Data(const Data&) = delete;
	Data(Data&&) = delete;
	Data& operator=(const Data&) = delete;
	Data& operator=(const Data&&) = delete;
};


#endif // !DATA_H








