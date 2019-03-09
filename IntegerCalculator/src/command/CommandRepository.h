/* *** CommandRepository.h ***
	
	Command Repository это  Singleton класс котрый хранит список пар название команды и указатель на
	саму комманду Command* (Command.h). Так как класс имеет статический instance то он существует во все время
	программы и деструктор тоже приватный. Имеет методы
	1. commandRegister принимает в паринмает ссылку на строку название и указатель на Командну и добавлякт 
	   их в список (repository_) проверяя на наличии уже существовании такой команды и если команда с таким
	   названием уже есть бросает в исключение(таким образам исключая возможность существование одинаковых команд
	   и разных команд с одинаковими названиемы.
	2. deregisterCommand находит и удалят команду с назваинем который передается как аргумент но перед этим 
	   проверяя существует ли такая команда вообще. кроме как удалять саму пару (названеие, команда) еще и отдельно 
	   удаляет отдельно команду delete (**it).second. возвращает true если команда найдена и удалена в противно случае
	   false
	3. allocateCommand принимает параметром как аргумент название команды проверяет на наличии существовнии
	   такой команды и возвращает указатель на клона(копий) комады так как в программе есть повтор и отмена
	   комманд и команды которые с помошью этой функции создались хранятся в CommandManager. Если команды с таким
	   название нет то возврощается nullptr

	4. findkey вспомогательгная функция ктороя принимет как аргумент название комманды и возврощает
	   true если команда есть в противном слчае false

	Реадизация класса в CommandRepository.cpp
*/

//#pragma once
#ifndef COMMAND_REPOSITORY_H
#define COMMAND_REPOSITORY_H


#include "../utilites/List.h"

#include <string>
#include <fstream>

class Command;

class CommandRepository
{
public:
	static CommandRepository& Instance();
	void commandRegister(const std::string& name, Command* c);
	bool deregisterCommand(const std::string& name);
	Command* allocateCommand(const std::string& name) const;

	List<std::string> getCommandsName();
	void printeHelp(const std::string& name, std::ostream& oss);

private:
	using unitCommand = pair<std::string, Command*>;
	using Repository = List< unitCommand >;

	Repository repository_;

	bool findKey(const std::string& name) const;

	CommandRepository() { }
	~CommandRepository() { }
	CommandRepository(CommandRepository&) = delete;
	CommandRepository(CommandRepository&&) = delete;
	CommandRepository& operator=(CommandRepository&) = delete;
	CommandRepository& operator=(CommandRepository&&) = delete;
};



#endif // !COMMAND_REPOSITORY_H





