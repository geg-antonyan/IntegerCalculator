// Command.cpp
#include "Command.h"
#include "../data/Data.h"
#include "../utilites/Exception.h"
#include "../utilites/UserInterface.h"
#include "CommandRepository.h"

#include <string>

void insertSort(List<Integer>& list);

//Command
void Command::execute()
{
	checkPreconditionsImpl();
	executeImpl();
}

void Command::undo()
{
	undoImpl();
}

Command* Command::clone() const
{
	return cloneImpl();
}

const char * Command::helpMessage() const
{
	return helpMessageImpl();
}

// UnaryCommand
void UnaryCommand::executeImpl()
{
	top_ = Data::Instance().pop();
	Data::Instance().push(unaryOperation(top_));
}

void UnaryCommand::undoImpl()
{
	Data::Instance().pop();
	Data::Instance().push(top_);
}

void UnaryCommand::checkPreconditionsImpl()
{
	if (Data::Instance().empty())
		Exception("для операции требуется хотябы один элемент");
}


// BinaryCommand
void BinaryCommand::executeImpl()
{
	top_ = Data::Instance().pop(false);
	next_ = Data::Instance().pop(false);
	Data::Instance().push(binaryOperation(next_, top_));
	
}

void BinaryCommand::undoImpl()
{
	Data::Instance().pop(false);
	Data::Instance().push(next_, false);
	Data::Instance().push(top_);
}

void BinaryCommand::checkPreconditionsImpl()
{
	if (Data::Instance().size() < 2) 
		throw Exception("Для бинарной операции нужен минимум 2 числа");
}

// SwapTopElements
void SwapTopElements::checkPreconditionsImpl()
{
	if (Data::Instance().size() < 2)
		throw Exception("Для операции нужны 2 элемента");
}

SwapTopElements * SwapTopElements::cloneImpl() const
{
	return new SwapTopElements;
}

void SwapTopElements::executeImpl()
{
	Data::Instance().swapTop();
}

void SwapTopElements::undoImpl()
{
	Data::Instance().swapTop();
}

const char * SwapTopElements::helpMessageImpl() const
{
	return "Заменяет местами 2 элемента из вершины стека данных";
}


// SortHighToLow
void SortHighToLow::checkPreconditionsImpl()
{
	if (Data::Instance().empty())
		throw Exception("Стек данных пуст");
}

SortHighToLow* SortHighToLow::cloneImpl() const
{
	return new SortHighToLow;
}

void SortHighToLow::executeImpl()
{
	List<Integer> list;
	while (!Data::Instance().empty())
		list.push_back(Data::Instance().pop(false));
	for (List<Integer>::iterator it = list.begin(); it != nullptr; incrPstf(it))
		stack_.push((**it));
	insertSort(list);
	while (list.size() > 1)
		Data::Instance().push(list.pop_front(), false);
	Data::Instance().push(list.pop_front(), true);
}

void SortHighToLow::undoImpl()
{
	Data::Instance().clear(false);
	while (stack_.size() > 1)
		Data::Instance().push(stack_.pop(), false);
	Data::Instance().push(stack_.pop(), true);
}

const char* SortHighToLow::helpMessageImpl() const
{
	return "Сортирует элементы по убыванию от вершины стека данных";
}


// SortLowToHigh
void SortLowToHigh::checkPreconditionsImpl()
{
	if (Data::Instance().empty())
		throw Exception("Стек данных пуст");
}

SortLowToHigh* SortLowToHigh::cloneImpl() const
{
	return new SortLowToHigh;
}

void SortLowToHigh::executeImpl()
{
	List<Integer> list;
	while (!Data::Instance().empty())
		list.push_back(Data::Instance().pop(false));
	for (List<Integer>::iterator it = list.begin(); it != nullptr; incrPstf(it))
		stack_.push((**it));
	insertSort(list);
	while (list.size() > 1)
		Data::Instance().push(list.pop_back(), false);
	Data::Instance().push(list.pop_back(), true);
}

void SortLowToHigh::undoImpl()
{
	Data::Instance().clear(false);
	while (stack_.size() > 1)
		Data::Instance().push(stack_.pop(), false);
	Data::Instance().push(stack_.pop(), true);
}

const char* SortLowToHigh::helpMessageImpl() const
{
	return "Сортирует элементы по возростанию от вершины стека данных";
}




//Clear Data
void ClearData::checkPreconditionsImpl()
{
	if (Data::Instance().empty())
		throw Exception("Стек данных не содержит элементов\n");
}

const char * ClearData::helpMessageImpl() const
{
	return "Очишает стек данных";
}

void ClearData::executeImpl()
{
	while (Data::Instance().size() > 1)
		stack_.push(Data::Instance().pop(false));
	stack_.push(Data::Instance().pop(true)); // для поднятии событии
}

void ClearData::undoImpl()
{
	while (stack_.size() > 1)
		Data::Instance().push(stack_.pop(), false);
	Data::Instance().push(stack_.pop(), true);
}

ClearData* ClearData::cloneImpl() const
{
	return new ClearData;
}


// EnterNumber
EnterNumber::EnterNumber(Integer i) : number_(i)
{
}

void EnterNumber::executeImpl()
{
	Data::Instance().push(number_);
}

void EnterNumber::undoImpl()
{
	if (Data::Instance().empty()) return;
	Data::Instance().pop();
}

EnterNumber* EnterNumber::cloneImpl() const
{
	return new EnterNumber(number_); // хотя в программе это не пользуется( просто))))
}

const char * EnterNumber::helpMessageImpl() const
{
	return "Добавляет число в стек данных";
}

// ChangeNumeralSystem
ChangeNumeralSystem::ChangeNumeralSystem(int numSys) : numSystem(numSys)
{
	
}

void ChangeNumeralSystem::executeImpl()
{
	lastNumSystem = Data::Instance().getNumSystem();
	Data::Instance().changeNumSystem(numSystem);
}

void ChangeNumeralSystem::undoImpl()
{
	Data::Instance().changeNumSystem(lastNumSystem);
}

void ChangeNumeralSystem::checkPreconditionsImpl()
{
	if (numSystem < 2 || numSystem > 16)
		throw Exception("Система счисления " + std::to_string(numSystem) + " не поддерживется");
}

ChangeNumeralSystem* ChangeNumeralSystem::cloneImpl() const
{
	return new ChangeNumeralSystem(numSystem);
}

const char * ChangeNumeralSystem::helpMessageImpl() const
{
	return "изменяет систем счисления в стеке данных";
}

//Pow
Pow* Pow::cloneImpl() const
{
	return new Pow;
}

Integer Pow::unaryOperation(Integer& top)
{
	return top * top;
}

const char * Pow::helpMessageImpl() const
{
	return "Возводит в квадрат число находящий в вершине стека данных";
}

// Add
Add * Add::cloneImpl() const
{
	return new Add;
}

Integer Add::binaryOperation(Integer& next, Integer& top)
{
	return next + top;
}

const char * Add::helpMessageImpl() const
{
	return "сумирует два числа из вершины стека данных";
}

// Subtac 
Subtrac* Subtrac::cloneImpl() const
{
	return new Subtrac;
}

Integer Subtrac::binaryOperation(Integer& next, Integer& top)
{
	return next - top;
}

const char * Subtrac::helpMessageImpl() const
{
	return "Вычитает два числа из вершины данных";
}

// Mult
Mult* Mult::cloneImpl() const
{
	return new Mult;
}

Integer Mult::binaryOperation(Integer& next, Integer& top)
{
	return next * top;
}

const char * Mult::helpMessageImpl() const
{
	return "умножает два числа из вершины данных";
}

// Divide
Divide * Divide::cloneImpl() const
{
	return new Divide;
}

Integer Divide::binaryOperation(Integer& next, Integer& top)
{
	return next / top;
}

const char * Divide::helpMessageImpl() const
{
	return "Деление двух чисел из вершины данных";
}

// DivisionByRemainder
DivisionByRemainder* DivisionByRemainder::cloneImpl() const
{
	return new DivisionByRemainder;
}

Integer DivisionByRemainder::binaryOperation(Integer& next, Integer& top)
{
	return next % top;
}

const char * DivisionByRemainder::helpMessageImpl() const
{
	return "Остаток от делении двух числа из вершины данных";
}



void RegisterCommands(UserInterface& ui)
{
	try
	{
		Command* add = new Add;
		Command* sub = new Subtrac;
		Command* mult = new Mult;
		Command* divide = new Divide;
		Command* divByRem = new DivisionByRemainder;
		Command* pow_ = new Pow;
		
		Command* swap_ = new SwapTopElements;
		Command* clearData = new ClearData;
		Command* sortHighToLow = new SortHighToLow;
		Command* sortLowToHigh = new SortLowToHigh;

		CommandRepository::Instance().commandRegister("+", add);
		CommandRepository::Instance().commandRegister("-", sub);
		CommandRepository::Instance().commandRegister("*", mult);
		CommandRepository::Instance().commandRegister("/", divide);
		CommandRepository::Instance().commandRegister("%", divByRem);
		CommandRepository::Instance().commandRegister("^", pow_);
		CommandRepository::Instance().commandRegister("clear", clearData);
		CommandRepository::Instance().commandRegister("swap", swap_);
		CommandRepository::Instance().commandRegister("sort>", sortHighToLow);
		CommandRepository::Instance().commandRegister("sort<", sortLowToHigh);
		
	}
	catch (Exception& ex)
	{
		ui.postMessage(ex.what());
	}
}


// свободные функции
void insertSort(List<Integer>& list)
{ // Хотя и в листе я опредили доступ через оператор [] но это довольно медленно, поэтому сорт. по указателям
	List<Integer>::iterator itfirst = list.begin(), it = list.begin();
	incrPstf(it);
	for (; it != nullptr; incrPstf(it))
	{
		List<Integer>::iterator itj = it;
		List<Integer>::iterator itk = itj;
		decrPstf(itk);
		while (itj != itfirst && (**itj) < (**itk))
		{
			Integer tmp = (**itj);
			(**itj) = (**itk);
			(**itk) = tmp;
			decrPstf(itj);
			decrPstf(itk);
		}
	}
}