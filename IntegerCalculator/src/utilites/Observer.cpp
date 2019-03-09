#include "Observer.h"
#include "UserInterface.h"
#include "EventData.h"
#include "../command/CommandDispatcher.h"

DataUpdatedObserver::DataUpdatedObserver(UserInterface& ui)
	: Observer("dataUpdate") , ui_(ui)
{
	
}

void DataUpdatedObserver::handleEventImpl(Event *)
{
	ui_.dataChanged();
}

CommandIssuedObserver::CommandIssuedObserver(CommandDispatcher & cd) : 
	Observer("CommandIssued"),
	cd_(cd)
{
}

void CommandIssuedObserver::handleEventImpl(Event* eventData)
{
	CommandEnteredEvent* cmd = dynamic_cast<CommandEnteredEvent*>(eventData);
	if (!cmd)
		throw Exception("Ќе получилось ковертировать CommandEnteredEvent в команду");
	else
		cd_.commandEntered(cmd->command());
}
