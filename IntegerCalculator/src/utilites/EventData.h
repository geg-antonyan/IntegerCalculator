/* *** EventData.h ***
	����� Event ��� ������� ����������� ����. ����� ������ ������ ��������� ������� �������� ��� ��������
	��������(������) � �������� �� ��� �� � ���� ����� CommnadDispatcher ��� ���������� ���������

*/
#ifndef EVENT_H
#define EVENT_H

#include <string>

class Event
{
public:
	virtual ~Event() { }
protected:
	Event() { }
};


class CommandEnteredEvent : public Event
{
public:
	CommandEnteredEvent(std::string& command) : command_(command)
	{ }
	const std::string command() const { return command_; }
private:
	std::string command_;
};

#endif // EVENT_H






