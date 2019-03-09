#ifndef CLI_H
#define CLI_H

#include "../utilites/UserInterface.h"

class Cli : public UserInterface
{
public:
	Cli(std::istream&, std::ostream&);
	~Cli();

	void execute();

private:
	std::istream& in_;
	std::ostream& out_;

	void postMessage(const std::string& m) override;
	void dataChanged() override;

	void startMessage();
	void headerMessage();

	Cli(const Cli&) = delete;
	Cli(Cli&&) = delete;
	Cli& operator = (const Cli&) = delete;
	Cli& operator = (Cli&&) = delete;
};


#endif // !CLI_H
