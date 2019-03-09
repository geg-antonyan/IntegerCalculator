#include "CommandDispatcher.h"
#include "../utilites/UserInterface.h"
#include "Command.h"
#include "CommandRepository.h"
#include "../data/Data.h"

#include <algorithm>
#include <sstream>


using std::string;
using std::stringstream;

using std::string;

bool isNum(const string& command, int n = 17);

int get_int(char symbol);



CommandDispatcher::CommandDispatcher(UserInterface& ui) : ui_(ui)
{
}

CommandDispatcher::~CommandDispatcher()
{
}

void CommandDispatcher::commandEntered(const string& commandName)
{
	try
	{
		int numSys = Data::Instance().getNumSystem();
		if (isNum(commandName, numSys))
		{
			EnterNumber *enterNumer = new EnterNumber(Integer(commandName.c_str(), numSys));
			manager_.commandExecute(enterNumer);
		}
		else if (commandName == "undo")
			manager_.undo();
		else if (commandName == "redo")
			manager_.redo();
		else if (commandName == "help")
			printHelp();
		else if ((commandName.size() == 8  || commandName.size() == 9) && commandName.substr(0, 6) == "change"
			&& isNum(commandName.substr(7, commandName.size() - 7), 10) && commandName.substr(7, 1) != "-")
		{
			string ch = commandName.substr(7, commandName.size() - 7);
			ChangeNumeralSystem* change = new ChangeNumeralSystem(atoi(ch.c_str()));
			manager_.commandExecute(change);
		}
		else
		{
			Command* cmd = CommandRepository::Instance().allocateCommand(commandName);
			if (!cmd)
			{
				string errorName = "Комманда \"" + commandName + "\" не найдена";
				ui_.postMessage(errorName);
			}
			else
				manager_.commandExecute(cmd);
		}
	}
	catch (Exception& ex)
	{
		ui_.postMessage(ex.what());
	}
}

void CommandDispatcher::printHelp()
{
	List<string> allCommands = CommandRepository::Instance().getCommandsName();
	stringstream ss;
	for (List<string>::iterator it = allCommands.begin(); it != nullptr; incrPstf(it))
	{
		ss << **it << " :\t";
		CommandRepository::Instance().printeHelp((**it), ss);
		ss << "\n";
	}
	ui_.postMessage(ss.str());
}

bool isNum(const string& command, int n)
{
	if (command.empty()) return false;
	if (command.length() == 1 && command[0] == '-') return false;
	
	string digits = "0123456789ABCEDF-";
	string actualDigits = digits.substr(0, n) + '-';
	
	string actualStr = command;
	transform(actualStr.begin(), actualStr.end(), actualStr.begin(), toupper);
	
	for (unsigned int i = 0; i < actualStr.length(); i++)
	{
		string::size_type k = actualDigits.find_first_of(actualStr[i]);
		if (k == string::npos)
			return false;
		else if (actualDigits[k] == '-' && actualStr[0] != '-')
			return false;
	}
	return true;
}

int get_int(char symbol)
{
	switch (symbol)
	{
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
		return atoi(&symbol);
	case 'A': case 'a': return 10;
	case 'B': case 'b': return 11;
	case 'C': case 'c': return 12;
	case 'D': case 'd': return 13;
	case 'E': case 'e': return 14;
	case 'F': case 'f': return 15;
	default: throw Exception("ERROR::NUMBER::INPUT _invalid_value");
	}
}