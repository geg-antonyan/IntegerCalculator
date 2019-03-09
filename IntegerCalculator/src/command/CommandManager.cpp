// CommandManager.h
#include "CommandManager.h"
#include "Command.h"

void CommandManager::commandExecute(Command * cmd)
{
	cmd->execute();
	undoStore_.push(cmd);
	while(!redoStore_.empty()) // почему не просто clear?? так как поле информации Command* и в случае clear мы будем иметь утечку памяти
	 delete redoStore_.pop(); 
}

void CommandManager::undo()
{
	if (undoStore_.empty()) return;
	Command* cmd = undoStore_.pop();
	cmd->undo();
	redoStore_.push(cmd);
}

void CommandManager::redo()
{
	if (redoStore_.empty()) return;
	Command* cmd = redoStore_.pop();
	cmd->execute();
	undoStore_.push(cmd);
}