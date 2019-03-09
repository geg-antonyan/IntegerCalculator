/* *** Command.h ***
	class Command это абстрактынй класс выпол¤нет роль интерфейса прадестовал¤ 3 метода. 1) execute() выпол¤н¤ть
	2) undo() отмен¤ть и 3) clon() возврашает указатель на такую же команды. имеет приватные виртуальные методы
	checkPreconditionsImpl(), executeImpl(), undoImpl() и clonImpl() кторые вызываютс¤ в методах интерфейса и
	которые переопредел¤ют наледники.  опирование и присвоение в —амом классе и в наследниках приватны то есть 
	запрешены. есть еще и абстрактные классы BinaryCommand и UnaryCommand которые переопредел¤ют executeImpl()
	undoImpl(), checkPreconditionsImpl() остовл¤¤ производным уже конечным классм переопредел¤ть соответсвено
	binaryOperation и unaryOperation ну и еще cloneImpl(). все остолные классы довольно просты так как они в
	соответсвии с функционала берут числа из Data сохран¤ют их дл¤ undo а затавм новый результат записывают в Data

–еализаци¤ в Command.cpp
	¬ Command.cpp находитс¤ функци¤ которо¤ регистрирует кобанды в CommandRepository
*/


//#pragma once
#ifndef COMMAND_H
#define COMMAND_H

#include "../data/Integer.h"
#include "../utilites/Stack.h"
#include "../utilites/List.h"

class Command
{
public:
	virtual ~Command() { }
	void execute();
	void undo();
	Command* clone() const;
	const char* helpMessage() const;

protected:
	Command() { }

private:
	virtual void checkPreconditionsImpl() = 0;
	virtual Command* cloneImpl() const = 0;
	virtual void executeImpl() = 0;
	virtual void undoImpl() = 0;
	virtual const char* helpMessageImpl() const = 0;

	Command(const Command&) { }
	Command(Command&&) = delete;
	Command& operator=(const Command&) = delete;
	Command& operator=(Command&&) = delete;
};


class UnaryCommand : public Command
{ // дл¤ синус, косинус, корень, квадрат ....
public:
	virtual ~UnaryCommand() { }

protected:
	UnaryCommand() { }

private:
	void executeImpl() override;
	void undoImpl() override;
	void checkPreconditionsImpl() override;
	virtual Integer unaryOperation(Integer&) = 0;

	Integer top_;

	UnaryCommand(const UnaryCommand&) = delete;
	UnaryCommand(UnaryCommand&&) = delete;
	UnaryCommand& operator=(const UnaryCommand&) = delete;
	UnaryCommand& operator=(UnaryCommand&&) = delete;
};


class BinaryCommand : public Command
{
public:
	virtual ~BinaryCommand() { }

protected:
	BinaryCommand() { }

private:
	void executeImpl() override;
	void undoImpl() override;
	void checkPreconditionsImpl() override;
	virtual Integer binaryOperation(Integer& next, Integer& top) = 0;

	Integer top_;
	Integer next_;

	BinaryCommand(const BinaryCommand&) = delete;
	BinaryCommand(BinaryCommand&&) = delete;
	BinaryCommand& operator=(const BinaryCommand&) = delete;
	BinaryCommand& operator=(BinaryCommand&&) = delete;
};

class SwapTopElements : public Command
{
public:
	SwapTopElements() {}
	~SwapTopElements() { }
private:
	void checkPreconditionsImpl() override;
	SwapTopElements* cloneImpl() const override;
	void executeImpl() override;
	void undoImpl() override;
	const char* helpMessageImpl() const override;

	SwapTopElements(const SwapTopElements&) = delete;
	SwapTopElements(SwapTopElements&&) = delete;
	SwapTopElements& operator=(const SwapTopElements&) = delete;
	SwapTopElements& operator=(SwapTopElements&&) = delete;
};

class SortHighToLow : public Command
{
public:
	SortHighToLow() {}
	~SortHighToLow() { }
private:
	void checkPreconditionsImpl() override;
	SortHighToLow* cloneImpl() const override;
	void executeImpl() override;
	void undoImpl() override;
	const char* helpMessageImpl() const override;



	Stack<Integer> stack_;

	SortHighToLow(const SortHighToLow&) = delete;
	SortHighToLow(SortHighToLow&&) = delete;
	SortHighToLow& operator=(const SortHighToLow&) = delete;
	SortHighToLow& operator=(SortHighToLow&&) = delete;
};

class SortLowToHigh : public Command
{
public:
	SortLowToHigh() {}
	~SortLowToHigh() { }
private:
	void checkPreconditionsImpl() override;
	SortLowToHigh* cloneImpl() const override;
	void executeImpl() override;
	void undoImpl() override;
	const char* helpMessageImpl() const override;


	Stack<Integer> stack_;

	SortLowToHigh(const SortLowToHigh&) = delete;
	SortLowToHigh(SortLowToHigh&&) = delete;
	SortLowToHigh& operator=(const SortLowToHigh&) = delete;
	SortLowToHigh& operator=(SortLowToHigh&&) = delete;
};



class ClearData : public Command
{
public:
	ClearData() { }
	~ClearData() { }

private:
	void executeImpl() override;
	void undoImpl() override;
	ClearData* cloneImpl() const override;
	void checkPreconditionsImpl() override;
	const char* helpMessageImpl() const override;
	Stack<Integer> stack_;

	ClearData(const ClearData&) { }
	ClearData(ClearData&&) = delete;
	ClearData& operator=(const ClearData&) = delete;
	ClearData& operator=(ClearData&&) = delete;
};

class EnterNumber : public Command
{
public:
	EnterNumber() { }
	EnterNumber(Integer i);
	~EnterNumber() { }

private:
	void executeImpl() override;
	void undoImpl() override;
	void checkPreconditionsImpl() override { } // так как чтобы добавить число не надо проверок
	EnterNumber* cloneImpl() const override;
	const char* helpMessageImpl() const override;

	Integer number_;

	EnterNumber(const EnterNumber&) { }
	EnterNumber(EnterNumber&&) = delete;
	EnterNumber& operator=(const EnterNumber&) = delete;
	EnterNumber& operator=(EnterNumber&&) = delete;
};

class ChangeNumeralSystem : public Command
{
public:
	ChangeNumeralSystem() { }
	ChangeNumeralSystem(int numSys);
	~ChangeNumeralSystem() { }

private:
	void executeImpl() override;
	void undoImpl() override;
	void checkPreconditionsImpl() override;
	ChangeNumeralSystem* cloneImpl() const override;
	const char* helpMessageImpl() const override;

	int numSystem;
	int lastNumSystem;
	ChangeNumeralSystem(const ChangeNumeralSystem&) { }
	ChangeNumeralSystem(ChangeNumeralSystem&&) = delete;
	ChangeNumeralSystem& operator=(const ChangeNumeralSystem&) = delete;
	ChangeNumeralSystem& operator=(ChangeNumeralSystem&&) = delete;
};

class Pow : public UnaryCommand
{
public:
	Pow() { }
	~Pow() { }

private:
	Pow* cloneImpl() const override;
	Integer unaryOperation(Integer& top) override;
	const char* helpMessageImpl() const override;

	Pow(const Pow&) = delete;
	Pow(Pow&&) = delete;
	Pow& operator=(const Pow&) = delete;
	Pow& operator=(Pow&&) = delete;
};


class Add : public BinaryCommand
{
public:
	Add() { }
	~Add() { }

private:
	Add* cloneImpl() const override;
	Integer binaryOperation(Integer& next, Integer& top)  override;
	const char* helpMessageImpl() const override;

	Add(const Add&) = delete;
	Add(Add&&) = delete;
	Add& operator=(const Add&) = delete;
	Add& operator=(Add&&) = delete;
};



class Subtrac : public BinaryCommand
{
public:
	Subtrac() { }
	~Subtrac() { }

private:
	Subtrac* cloneImpl() const override;
	Integer binaryOperation(Integer& next, Integer& top)  override;
	const char* helpMessageImpl() const override;

	Subtrac(const Subtrac&) = delete;
	Subtrac(Subtrac&&) = delete;
	Subtrac& operator=(const Subtrac&) = delete;
	Subtrac& operator=(Subtrac&&) = delete;
};

class Mult : public BinaryCommand
{
public:
	Mult() { }
	~Mult() { }
private:
	Mult* cloneImpl() const override;
	Integer binaryOperation(Integer& next, Integer& top) override;
	const char* helpMessageImpl() const override;

	Mult(const Mult&) = delete;
	Mult(Mult&&) = delete;
	Mult& operator=(const Mult&) = delete;
	Mult& operator=(Mult&&) = delete;
};

class Divide : public BinaryCommand
{
public:
	Divide() {}
	~Divide() { }
private:
	Divide* cloneImpl() const override;
	Integer binaryOperation(Integer& next, Integer& top) override;
	const char* helpMessageImpl() const override;

	Divide(const Divide&) = delete;
	Divide(Divide&&) = delete;
	Divide& operator=(const Divide&) = delete;
	Divide& operator=(Divide&&) = delete;
};

class DivisionByRemainder : public BinaryCommand
{
public:
	DivisionByRemainder() { }
	~DivisionByRemainder() { }
private:
	DivisionByRemainder* cloneImpl() const override;
	Integer binaryOperation(Integer& next, Integer& top) override;
	const char* helpMessageImpl() const override;

	DivisionByRemainder(const DivisionByRemainder&) = delete;
	DivisionByRemainder(DivisionByRemainder&&) = delete;
	DivisionByRemainder& operator=(const DivisionByRemainder&) = delete;
	DivisionByRemainder& operator=(DivisionByRemainder&&) = delete;
};



class UserInterface;
void RegisterCommands(UserInterface& ui);





#endif // !COMMAND_H






