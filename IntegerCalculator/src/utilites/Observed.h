/* *** Observed ***
	Наблюдаемый или Издатель. Класс самодастоточный но из за того что сам класс отдельно не должен иметь экземляра
	то деструктор защищенный. Основные вщзможности добавить событие, добавлять и удалять наблюдателей, и поднимать
	событие. Классы которые наследуются получаю все эти возможности в свое усматрение открывя для клиентов ту или
	иные методы так как подрозумывается что от класса не будут наследоватся публично. можно было конечно сделав
	деструктор публичным тем самим вместо наследовании использовать агрегировании в классах которые издают событие
	так как STL запрещается то я с помошью своего List и pair попробовал боле мене аккцратно выйти из ситуации
	тем самим используя для этих структур данных боле понятные название unitObserver и далее.
	все функции довольно просты. хотя в моей программе такая структура не надо было но для расширяемости и так как
	это курс ООП самы данные в Observed следующее есть одельня пара название обсервера и обсервер. и есть пара
	название событии и списка его наблюдателей.

	Примичание. в тех местах где классы в самом загаловочном файле исполюзуются как указатели или ссылки без
	приминении их функционал для быстрой компиляции я использовал обявлении этих классов а саму файл подкючил 
	уже в испольнительном файле. 
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







