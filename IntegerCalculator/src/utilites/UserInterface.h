/* *** UserInterface.h ***
	В файле находится обстаркный класс UserInterfac который наледуется от Observed но защищенно,
	так как она не поддерживает is - a. Но сам класс нуждается методов Observed регистрируя событие
	(в нащем случе в конструкторе) . а вот клиетская часть имеет возможность поднять событие,
	удалять и добавить наблюдателей. имееит 2 метода postMessage и dataChanged. 
	Cli наследуется от UserInteface, в приватоном поле переопределяет postMessage и dataChanged
	в клиетской части оставляя только комманду execute ну и raise; addObserver; removeObserver;
	архитектура программы Model-view-controller который подрозумевает прямой доступ Cli к Data
	то что и делается в методе dataChanged
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







