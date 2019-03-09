#include "Cli.h"

#include "../data/Data.h"
#include "../utilites/EventData.h"
#include "../data/Integer.h"
#include  <sstream>

using std::string;
using std::stringstream;
using std::istream;
using std::ostream;

Cli::Cli(istream& in, ostream& out)
	: in_(in), out_(out)
{

}

Cli::~Cli()
{
}

void Cli::execute()
{
	startMessage();
	headerMessage();
	for (string i; out_ << ">> ", getline(in_, i, '\n');)
	{

		if (i == "exit")
			return;
		else
		{
			CommandEnteredEvent* cmd = new CommandEnteredEvent(i);
			raise(CommandEntered, cmd);
		}
	}
}

void Cli::postMessage(const string& m)
{
	out_ << m << "\n";
}

void Cli::dataChanged()
{
	system("cls");
	headerMessage();
	stringstream sstr;
	sstr << "\n������� ������� ��������� " << Data::Instance().getNumSystem() << "";
	if (Data::Instance().empty())
		sstr << "\n���� ������ ����\n";
	else
	{
		List<Integer> elements = Data::Instance().getElements(5);
		if (Data::Instance().size() == 1)
			sstr << "\n� ����� ������ 1 �������\n";
		else if (Data::Instance().size() > 1 && Data::Instance().size() <= 4)
			sstr << "\n� ����� ������ " << Data::Instance().size() << " ��������\n";
		else if (Data::Instance().size() > 4)
			sstr << "\n� ����� ������ " << Data::Instance().size() << " ���������\n";
		for (List<Integer>::iterator it = elements.begin(); it != nullptr; incrPstf(it))
			sstr << **it << "\n";
	}
	postMessage(sstr.str());
}

void Cli::startMessage()
{
	out_ << "����� ���������� � ��������� \"Integer Calculator - �������� �������� �������\" \n"
		<< "������� ��������� �� ��������� 10\n";
}

void Cli::headerMessage()
{
	out_ << "*******\"Integer Calculator - �������� �������� �������\"**********\n"
		<< "'help'         ����� ������������ �� ������� �������\n"
		<< "'exit'         ��� ������ �� ���������\n"
		<< "'change x'     2 <= x <= 16(������� ���������)\n"
		<< "'undo'/'redo'  �����/������\n";
}
