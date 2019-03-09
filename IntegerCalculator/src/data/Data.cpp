#include "Data.h"
#include "Integer.h"

const std::string Data::dataChanged = "dataChanged";
int Data::numSystem = 10;

Data::Data()
{
	registerEvent(dataChanged); // регистрируем событие
}

Data & Data::Instance()
{
		static Data instance;
		return instance;
}

void Data::push(Integer num, bool raiseEvent)
{
	data_.push_back(num);
	if (raiseEvent)
		raise(dataChanged, nullptr);
}

Integer Data::pop(bool raiseEvent)
{
	Integer i = data_.pop_back();
	if (raiseEvent)
		raise(dataChanged, nullptr);
	return i;
	
}

Integer Data::top()
{
	return (**data_.end());
}

void Data::swapTop()
{
	Integer frist = data_.pop_back();
	Integer second = data_.pop_back();
	data_.push_back(frist);
	data_.push_back(second);
	raise(dataChanged, nullptr);
}

void Data::clear(bool raiseEvent)
{
	data_.clear();
	if (raiseEvent)
		raise(dataChanged, nullptr);
}

bool Data::empty()
{
	return data_.empty();
}

int Data::size()
{
	return data_.size();
}

List<Integer> Data::getElements(int n)
{
	if (n > data_.size()) n = data_.size();
	List<Integer> tmp;
	for (List<Integer>::iterator it = data_.end(); n--; decrPstf(it))
		tmp.push_back(**it);
	return tmp;
}

void Data::changeNumSystem(int numSm)
{
	if (numSm < 2 || numSm > 16)
		throw Exception("Систем сесления \"" + std::to_string(numSm) + "\" не поддерживается");
	numSystem = numSm;
	for (List<Integer>::iterator it = Data::Instance().data_.begin(); it != nullptr; incrPstf(it))
	{
		(**it) = (**it).changeNumSystem(numSystem);
	}
	raise(Data::dataChanged, nullptr);
}


