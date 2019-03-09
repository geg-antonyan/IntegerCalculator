/* *** Observer.h ***
	Паттеро Наблюатель. Имеет абстрактный класс Observer как интерфейс у которого наледники переопределяют
	чито виртуальную функцию приватную handleEventImpl(Event*) котроый в базовок классе вызывается hnadleEvent()
	так как данные событии могут быть разные( в случе ввода коммад) то обработчик событие аринмает как агумент 
	Event. при вызове когда просто изменяется стек то аргумент nullptr так как dataChanged прямо считывает 
	данные из Data

*/
#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>

class Event;

class UserInterface;

class CommandDispatcher;

class Observer
{
public:
	Observer(std::string name) : name_(name) { }
	const std::string& name() { return name_; }
	void handleEvent(Event* eventData) { handleEventImpl(eventData); }
	~Observer() { }
private:

	virtual void handleEventImpl(Event*) = 0;

	const std::string name_;
};

class DataUpdatedObserver : public Observer
{
public:
	DataUpdatedObserver(UserInterface& ui);
private:
	void handleEventImpl(Event*) override;

	UserInterface& ui_;
};

class CommandIssuedObserver : public Observer
{
public:
	CommandIssuedObserver(CommandDispatcher& cd);
private:
	void handleEventImpl(Event*) override;

	CommandDispatcher& cd_;
};



#endif // !OBSEVRVER_H








