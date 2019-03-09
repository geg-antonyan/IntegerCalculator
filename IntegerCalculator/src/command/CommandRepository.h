/* *** CommandRepository.h ***
	
	Command Repository ���  Singleton ����� ������ ������ ������ ��� �������� ������� � ��������� ��
	���� �������� Command* (Command.h). ��� ��� ����� ����� ����������� instance �� �� ���������� �� ��� �����
	��������� � ���������� ���� ���������. ����� ������
	1. commandRegister ��������� � ��������� ������ �� ������ �������� � ��������� �� �������� � ��������� 
	   �� � ������ (repository_) �������� �� ������� ��� ������������� ����� ������� � ���� ������� � �����
	   ��������� ��� ���� ������� � ����������(����� ������� �������� ����������� ������������� ���������� ������
	   � ������ ������ � ����������� ����������.
	2. deregisterCommand ������� � ������ ������� � ��������� ������� ���������� ��� �������� �� ����� ���� 
	   �������� ���������� �� ����� ������� ������. ����� ��� ������� ���� ���� (���������, �������) ��� � �������� 
	   ������� �������� ������� delete (**it).second. ���������� true ���� ������� ������� � ������� � �������� ������
	   false
	3. allocateCommand ��������� ���������� ��� �������� �������� ������� ��������� �� ������� ������������
	   ����� ������� � ���������� ��������� �� �����(�����) ������ ��� ��� � ��������� ���� ������ � ������
	   ������� � ������� ������� � ������� ���� ������� ��������� �������� � CommandManager. ���� ������� � �����
	   �������� ��� �� ������������ nullptr

	4. findkey ���������������� ������� ������ �������� ��� �������� �������� �������� � ����������
	   true ���� ������� ���� � ��������� ����� false

	���������� ������ � CommandRepository.cpp
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





