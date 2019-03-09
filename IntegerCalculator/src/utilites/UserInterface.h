/* *** UserInterface.h ***
	� ����� ��������� ���������� ����� UserInterfac ������� ���������� �� Observed �� ���������,
	��� ��� ��� �� ������������ is - a. �� ��� ����� ��������� ������� Observed ����������� �������
	(� ����� ����� � ������������) . � ��� ��������� ����� ����� ����������� ������� �������,
	������� � �������� ������������. ������ 2 ������ postMessage � dataChanged. 
	Cli ����������� �� UserInteface, � ���������� ���� �������������� postMessage � dataChanged
	� ��������� ����� �������� ������ �������� execute �� � raise; addObserver; removeObserver;
	����������� ��������� Model-view-controller ������� ������������� ������ ������ Cli � Data
	�� ��� � �������� � ������ dataChanged
*/


#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "Observed.h"

#include <iostream>
#include <string>

class UserInterface : protected Observed
{
public:
	UserInterface() { registerEvent(CommandEntered); }
	virtual ~UserInterface() { }
	virtual void postMessage(const std::string& m) = 0;
	virtual void dataChanged() = 0;


	using Observed::addObserver;
	using Observed::removeObserver;

	static const std::string CommandEntered;
};


#endif // !USER_INTERFACE_H







