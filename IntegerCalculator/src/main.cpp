
#include "ui/Cli.h"
#include "utilites/Observer.h"
#include "data/Data.h"

#include "command/Command.h"
#include "command/CommandDispatcher.h"




int main()
{
	setlocale(LC_ALL, "rus");
	Cli cli{ std::cin, std::cout };
	CommandDispatcher cd(cli);
	RegisterCommands(cli);
	CommandIssuedObserver* commandIssuedOb = new CommandIssuedObserver(cd);
	cli.addObserver(UserInterface::CommandEntered, commandIssuedOb);
	DataUpdatedObserver *dataUpdateOb = new DataUpdatedObserver(cli);
	Data::Instance().addObserver(Data::dataChanged, dataUpdateOb);
	cli.execute();
	return 0;
}