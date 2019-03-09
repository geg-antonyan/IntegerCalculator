// CommandRepository.cpp
#include "CommandRepository.h"
#include "Command.h"

using std::string;
using std::ostream;

CommandRepository & CommandRepository::Instance()
{
	static CommandRepository instance;
	return instance;
}

void CommandRepository::commandRegister(const string & name, Command * c)
{
	if (findKey(name))
		throw Exception{ "Комманда под нозванием \"" + name + "\" уже существует" };
	unitCommand tmp(name, c);
	repository_.push_back(tmp);
}

bool CommandRepository::deregisterCommand(const string & name)
{
	if (findKey(name))
	{
		List<unitCommand>::iterator it = repository_.find(name);
		delete (**it).second; // так как second тут указатель( Command*)
		repository_.erase(it);
		return true;
	}
	return false;
}

Command* CommandRepository::allocateCommand(const string & name) const
{
	if (findKey(name))
		return (**repository_.find(name)).second->clone();
	return nullptr;
}

List<string> CommandRepository::getCommandsName()
{
	List<string> res;
	for (List<unitCommand>::iterator it = repository_.begin(); it != nullptr; incrPstf(it))
		res.push_back((**it).first);
	return res;
}

void CommandRepository::printeHelp(const string& name, ostream& oss)
{
	if (findKey(name))
		oss << (**repository_.find(name)).second->helpMessage();
}

bool CommandRepository::findKey(const std::string& name) const
{
	return repository_.find(name);
}
