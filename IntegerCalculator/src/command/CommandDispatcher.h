#ifndef COMMAND_DISPETCHER_H
#define COMMAND_DISPETCHER_H

#include "CommandManager.h"

#include <string>


class UserInterface;


class CommandDispatcher
{
public:
	CommandDispatcher(UserInterface& ui);
	~CommandDispatcher();

	void commandEntered(const std::string& commandName);

private:
	UserInterface& ui_;
	CommandManager manager_;

	void printHelp();

	CommandDispatcher(const CommandDispatcher&) = delete;
	CommandDispatcher(CommandDispatcher&&) = delete;
	CommandDispatcher& operator=(const CommandDispatcher&) = delete;
	CommandDispatcher& operator=(CommandDispatcher&&) = delete;
};



#endif // !COMMAND_DISPETCHER_H


