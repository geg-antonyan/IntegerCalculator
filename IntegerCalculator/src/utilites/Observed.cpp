#include "Observed.h"
#include "Exception.h"
#include "Observer.h"
#include "EventData.h"

using std::string;

void Observed::registerEvent(const string& eventName)
{
	if (findKey(eventName))
		throw Exception("событие под названием " + eventName + " уже зарегистрировано");
	ObserverList list;
	unitEvent tmp(eventName, list);
	events_.push_back(tmp);
}

void Observed::addObserver(const string& eventName, Observer* observer)
{
	if (!findKey(eventName))
		throw Exception("—обытие под названием " + eventName + " еще не зарегистрирована");
	List<unitEvent>::iterator it = events_.find(eventName);
	unitObserver tmp(observer->name(), observer);
	(**it).second.push_back(tmp);
}

bool Observed::removeObserver(const std::string& eventName, std::string observerName)
{
	if (!findKey(eventName)) return false;
	List<unitEvent>::iterator itEv = events_.find(eventName);
	List<unitObserver>::iterator itOb = (**itEv).second.find(observerName);
	if (itOb)
	{
		delete (**itOb).second; // так как Observer это указатель и надо очищать па€ть
		(**itEv).second.erase(itOb);
		return true;
	}
	return false;
}

void Observed::raise(const std::string& eventName, Event* eventData)
{
	if (!findKey(eventName))
		throw Exception("Ќе получилось подн€ть cобытие. под названием " + eventName + " не неайден: raise::error");
	List<unitEvent>::iterator itEv = events_.find(eventName);
	for (List<unitObserver>::iterator it = (**itEv).second.begin(); it != nullptr; incrPstf(it))
		(**it).second->handleEvent(eventData);
}

List<string> Observed::eventList()
{
	List<std::string> tmp;
	for (Events::iterator it = events_.begin(); it != nullptr; incrPstf(it))
		tmp.push_back((**it).first);
	
	return  tmp;
}

bool Observed::findKey(const std::string& name)
{
	return events_.find(name);
}
