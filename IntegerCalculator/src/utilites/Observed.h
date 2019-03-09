/* *** Observed ***
	����������� ��� ��������. ����� ��������������� �� �� �� ���� ��� ��� ����� �������� �� ������ ����� ���������
	�� ���������� ����������. �������� ����������� �������� �������, ��������� � ������� ������������, � ���������
	�������. ������ ������� ����������� ������� ��� ��� ����������� � ���� ���������� ������� ��� �������� �� ���
	���� ������ ��� ��� ��������������� ��� �� ������ �� ����� ������������ ��������. ����� ���� ������� ������
	���������� ��������� ��� ����� ������ ������������ ������������ ������������� � ������� ������� ������ �������
	��� ��� STL ����������� �� � � ������� ������ List � pair ���������� ���� ���� ��������� ����� �� ��������
	��� ����� ��������� ��� ���� �������� ������ ���� �������� �������� unitObserver � �����.
	��� ������� �������� ������. ���� � ���� ��������� ����� ��������� �� ���� ���� �� ��� ������������� � ��� ���
	��� ���� ��� ���� ������ � Observed ��������� ���� ������� ���� �������� ��������� � ��������. � ���� ����
	�������� ������� � ������ ��� ������������.

	����������. � ��� ������ ��� ������ � ����� ������������ ����� ������������ ��� ��������� ��� ������ ���
	���������� �� ���������� ��� ������� ���������� � ����������� ��������� ���� ������� � ���� ���� �������� 
	��� � ��������������� �����. 
*/
#ifndef OBSERVED_H
#define OBSERVED_H


#include "List.h"

#include <string>

class Observer;

class Event;

class Observed
{
public:
	Observed() { }
	void registerEvent(const std::string& eventName);
	void addObserver(const std::string &eventName, Observer*);
	bool removeObserver(const std::string& eventName, std::string observerName);
	
	List<std::string> eventList();

protected:
	virtual ~Observed() { }
	void raise(const std::string& eventName, Event*);

private:
	using unitObserver = pair<std::string, Observer*>;
	using ObserverList = List< unitObserver >;
	using unitEvent = pair<std::string, ObserverList>;
	using Events = List< pair<std::string, ObserverList> >;

	Events events_;

	bool findKey(const std::string& name);
};



#endif // !OBSERVED_H







