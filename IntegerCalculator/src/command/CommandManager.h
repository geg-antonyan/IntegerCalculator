/* *** CommandManager.h ***
	CommandManager ��� ����� ������ ��������� ��������: ��������-cummandExecute(Command*), �����(������) undo()
	� redo() ��������� ���������� ���������� �������( ��� ���������� ����� �������(commandExecute) stack � ���������
	redo ���������. CommandManager ������ �������� undoStore_ � redoStore_. ����� ������� ������������(commandExecute)
	����� ��� ������� �������� � undoStore_ ������� ���� ����� ��� �������� ���� �� ��������. � ����� ������� ���������
	��� ��������� � undoStor_ � �������� � redoStore_ � ��������� ��� redo() �� ����� ������ ���������� commandExecute
	redoStore_ ��������� ��� ���������� ������

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





