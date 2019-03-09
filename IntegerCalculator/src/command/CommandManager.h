/* *** CommandManager.h ***
	CommandManager это класс кторый управл€ет комадамы: выполн€€-cummandExecute(Command*), назад(отмена) undo()
	и redo() повторное выполнение отмененных комманд( при выполнении новой команды(commandExecute) stack с командами
	redo очищаетс€. CommandManager имееит аттрибуы undoStore_ и redoStore_. когда команда выполн€тетс€(commandExecute)
	эатем это каманда зранитс€ в undoStore_ котора€ сама знает как отменить свою же комманду. и когда команда омен€тес€
	она удал€етс€ с undoStor_ и хранитс€ в redoStore_ и наооборот при redo() но когда заного вызываетс€ commandExecute
	redoStore_ очищаетс€ дл€ корректной работы

*/

//#pragma once
#ifndef COMMAND_MANAGER_H
#define COMMAND_MANAGER_H


#include "../utilites/Stack.h"

class Command;

class CommandManager
{
public:
	CommandManager() { }
	~CommandManager() { }

	void commandExecute(Command* cmd);
	void undo();
	void redo();

private:
	Stack<Command*> undoStore_;
	Stack<Command*> redoStore_;

	CommandManager(const CommandManager&) = delete;
	CommandManager(CommandManager&&) = delete;
	CommandManager& operator=(CommandManager&) = delete;
	CommandManager& operator=(CommandManager&&) = delete;
};


#endif // !COMMAND_MANAGER_H





