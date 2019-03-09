// Все операции реолизованы простимы алгоритмами поэтом не стал комментировать каждую строку. пример оператор + алгоритм \
// который всем знаком из школы и все другие операции так же...

#include "Integer.h"
#include "../utilites/Stack.h"
#include "../utilites/Exception.h"

#include <fstream>
#include <string>
#include <cmath>

using std::string;
using std::to_string;

/***** Вспомогательные функции *****/

// char -> int
int to_int(char);

// int -> char
char to_char(int);

/************Конструткоры и Деструктор*************/

Integer::Integer()
{
	numSystem = 10;
	length = 0;
	for (int i = 0; i < MAX_LENGTH; i++)
		this->arrDigit[i] = 0;
	sig = Pos;

}

Integer::Integer(NumeralSystem numSystem)
{
	if (numSystem > 16 || numSystem < 2) throw Exception("Ошибка инициализации");
	this->numSystem = numSystem;
	length = 0;
	sig = Pos;

	for (int i = 0; i < MAX_LENGTH; i++)
		this->arrDigit[i] = 0;
}

// Конструктор с строковым аргументом system по умолчанию = 10
Integer::Integer(Digits str, NumeralSystem numSystem)
{ // в начале проверяем корректность ввода
	if (numSystem > 16 || numSystem < 2 || !strlen(str) || strlen(str) > MAX_LENGTH)
		throw Exception("Ошибка инициализации");

	if (strlen(str) > 1 && str[0] == '0')
		throw Exception("Ошибка инициализации");

	if (str[0] == '-' && strlen(str) == 1 || str[0] == '-' && str[1] == '0')
		throw Exception("Ошибка инициализации");
	// проверка на наличии отр. числа
	int pos = 0;
	if (str[0] == '-')
	{
		pos = 1; // чтобы пропустить -
		sig = Neg;
	}
	else sig = Pos;

	this->numSystem = numSystem;
	length = strlen(str);

	for (int i = 0; i < MAX_LENGTH; i++)
		arrDigit[i] = 0; // все разряды ноль

	for (int i = pos; i < length; i++)
	{
		if (to_int(str[i]) >= numSystem) // проверка на корректность текущей системы счислении
			throw Exception("Ошибка инициализации Integer");
		arrDigit[length - i - 1] = to_int(str[i]);
	}
	if (sig == Neg) length--; // так как знак хранится в переменной sig
}

Integer::~Integer() // в атрибутах Intgere не выделяется дин. память
{
}



/***** Арифметические операторы ****/

// Оператор +
Integer Integer::operator+(const Integer& integer) const
{ // реализована по принцыпу обычной сложении с перестоновкоми операндами из за знаков и больше или меньше для удобной операции
	// операторы + - могут использовать друг друга
	Integer int1 = *this, int2 = integer;
	Integer res;

	if (numSystem != integer.numSystem) throw Exception("В вырожении используются разные системы счисления");
	res.numSystem = numSystem;
	int maxSize = (length > integer.length) ? length : integer.length;
	res.length = maxSize;

	if (this->sig == integer.sig)
	{
		int i;
		int remainder = 0;
		for (i = 0; i < maxSize; i++)
		{
			int balance;
			int tempBalance = int1.arrDigit[i] + int2.arrDigit[i] + remainder;
			remainder = 0;
			if (tempBalance >= res.numSystem)
			{
				balance = tempBalance - res.numSystem;
				remainder = 1;
			}
			else
				balance = tempBalance;
			res.arrDigit[i] = balance;
		}
		if (remainder != 0)
		{
			res.arrDigit[i] = 1;
			res.length = i + 1;
			if (res.length > MAX_LENGTH) throw Exception("Размер числа не поддерживается программой");
		}
	}
	else
	{
		if (int1.sig == Neg)
		{
			int1.sig = Pos;
			std::swap(int1, int2);
		}
		else int2.sig = Pos;
		return int1 - int2;
	}
	res.sig = sig;
	return res;
}


// Оператор -
Integer Integer::operator-(const Integer& integer) const
{ // как и + реализована по обычному алгоритм вычитании
	if (numSystem != integer.numSystem) throw Exception("В вырожении используются разные системы счисления");
	Integer int1(*this), int2 = integer;
	Integer res;

	res.numSystem = numSystem;
	int maxSize = (length > integer.length) ? length : integer.length;
	res.length = maxSize;

	if (sig == Pos && integer.sig == Pos)
	{
		if (int1.modul() < int2.modul())
		{
			std::swap(int1, int2);
			res.sig = Neg;
		}
		else res.sig = Pos;
		for (int i = 0; i < maxSize; i++)
		{
			int balance = 0;
			int tempBalance = int1.arrDigit[i] - int2.arrDigit[i];
			if (tempBalance < 0)
			{
				int j = i + 1;
				if (j < maxSize)
				{
					while (int1.arrDigit[j] == 0) j++;
					int1.arrDigit[j] -= 1;
					j--;
					while (j > i) int1.arrDigit[j--] = res.numSystem - 1;
					int1.arrDigit[j] += res.numSystem;
					balance = int1.arrDigit[j] - int2.arrDigit[j];
				}
			}
			else
				balance = tempBalance;
			res.arrDigit[i] = balance;
		}
	}
	else
	{ // чтобы иметь возможность работать с цифрами со знаком и чтобы не повторять код тут operator- вызывает operator+ а тот в свою очередь при (-) - (-) вызывает operator-
		// здесь можно просто умножить -1 на b.sig но мне больше так понравился
		if (int1.sig == Pos && int2.sig == Neg) // (+) - (-)
			int2.sig = Pos;
		else if (int1.sig == Neg && int2.sig == Pos) // (-) - (+) 
			int2.sig = Neg;
		else // для (-) - (-) хотя можно было бы опустить но для боле ясного кода
			int2.sig = Pos;
		return int1 + int2;
	}
	int countZero = 0;
	for (int i = MAX_LENGTH - 1; i > 0 && res.arrDigit[i] == 0; i--)
		countZero++;
	res.length = MAX_LENGTH - countZero;
	return res;
}

// оператор *
Integer Integer::operator*(const Integer& integer) const
{ //реализована по обычному алгоритму умножении
	if (numSystem != integer.numSystem) throw Exception("В вырожении используются разные системы счисления");

	Stack<Integer> intStack;
	int pos = 0;
	if (pos >= MAX_LENGTH) throw Exception("Размер числе не поддерживается программой");
	for (int i = 0; i < length; i++)
	{
		Integer tmpInteger(numSystem);
		int k = pos;
		tmpInteger.length = pos++;
		int balance = 0;
		for (int j = 0; j < integer.length; j++)
		{
			int tmp = arrDigit[i] * integer.arrDigit[j];
			tmp += balance;
			if (k >= MAX_LENGTH) throw Exception("Размер числе не поддерживается программой");
			tmpInteger.arrDigit[k++] = tmp % numSystem;
			tmpInteger.length++;
			balance = tmp / numSystem;
		}
		if (balance)
		{
			if (k >= MAX_LENGTH) throw Exception("Размер числе не поддерживается программой");
			tmpInteger.arrDigit[k++] = balance;
			tmpInteger.length++;
		}
		intStack.push(tmpInteger);
	}
	Integer result(numSystem);
	while (!intStack.empty())
		result += intStack.pop();
	int znak = int(sig) * int(integer.sig);
	result.sig = (Sig)znak;
	return result;

}

// обычный алгоритм делении. примушество что как и + - * не завист от размера int так как все операции 
// выполняются с типом Integer
Integer Integer::operator/(const Integer& integer) const
{
	if (numSystem != integer.numSystem) throw Exception("В вырожении используются разные системы счисления");
	if (integer == Integer("0", numSystem)) throw Exception("Деление на ноль");
	if (*this == integer) return Integer("1", numSystem);

	string resStr, dividentStr;
	int posDiv = length - 1;

	for (int i = 0; i < integer.length && posDiv >= 0; i++)
		dividentStr += to_char(arrDigit[posDiv--]);
	if (Integer(dividentStr.c_str(), numSystem) < integer.modul() && posDiv >= 0)
		dividentStr += to_char(arrDigit[posDiv--]);

	bool firstIter = true;
	while (posDiv >= 0 || firstIter)
	{
		firstIter = false;
		bool addNull = false;
		while (Integer(dividentStr.c_str(), numSystem) < integer.modul() && posDiv >= 0)
		{
			if (dividentStr == "0") dividentStr.clear();
			dividentStr += to_char(arrDigit[posDiv--]);
			if (addNull)
				resStr += '0';
			addNull = true;
		}
		if (!dividentStr.empty())
		{
			Integer divident(dividentStr.c_str(), numSystem), resBit("0", numSystem);
			while (divident >= integer.modul())
			{
				divident -= integer.modul();
				resBit++;
			}
			for (int i = 0; i < resBit.length; i++)
				resStr += to_char(resBit.arrDigit[resBit.length - 1 - i]);
			dividentStr.clear();
			for (int i = 0; i < divident.length; i++)
				dividentStr += to_char(divident.arrDigit[divident.length - 1 - i]);
		}
	}
	if (resStr != "0")
	{
		int znak = (int)sig / (int)integer.sig;
		if (znak < 0) resStr = "-" + resStr;
	}
	return Integer(resStr.c_str(), numSystem);
}

// оператор % простая реализация
Integer Integer::operator%(const Integer& integer) const
{
	if (numSystem != integer.numSystem) throw Exception("В вырожении используются разные системы счисления");
	if (this->modul() == integer.modul()) return Integer("0", numSystem);

	return *this - ((*this / integer) * integer);
}

Integer Integer::operator++(int)
{
	Integer own("1", numSystem);
	Integer tmp = *this;
	*this += own;
	return tmp;
}

Integer Integer::operator++()
{
	Integer own("1", numSystem);
	*this += own;
	return *this;
}

Integer Integer::operator--(int)
{
	Integer own("1", numSystem);
	Integer tmp = *this;
	*this -= own;
	return tmp;
}

Integer Integer::operator--()
{
	Integer own("1", numSystem);
	*this -= own;
	return *this;
}

// операторы += -= *= /= %= c помошью уже перегруженных + - * / % 

void Integer::operator+=(const Integer& integer)
{
	*this = *this + integer;
}

void Integer::operator-=(const Integer& integer)
{
	*this = *this - integer;
}

void Integer::operator*=(const Integer& integer)
{
	*this = *this * integer;
}

void Integer::operator/=(const Integer& integer)
{
	*this = *this / integer;
}

void Integer::operator%=(const Integer& integer)
{
	*this = *this % integer;
}

/***********Логические операторы*************/

// оператор <
bool Integer::operator < (const Integer& integer) const
{
	if (sig < integer.sig) return true;
	for (int i = MAX_LENGTH - 1; i >= 0; i--)
	{
		if (arrDigit[i] * sig < integer.arrDigit[i] * integer.sig)
			return true;
		if (arrDigit[i] * sig > integer.arrDigit[i] * integer.sig)\
			return false;
	}
	return false;
}

// оператор >
bool Integer::operator > (const Integer& integer) const
{
	if (sig > integer.sig) return true;
	for (int i = MAX_LENGTH - 1; i >= 0; i--)
	{
		if (arrDigit[i] * sig > integer.arrDigit[i] * integer.sig)
			return true;
		if (arrDigit[i] * sig < integer.arrDigit[i] * integer.sig)
			return false;
	}
	return false;
}

// оператор ==
bool Integer::operator == (const Integer& integer) const
{
	if (sig != integer.sig) return false;
	for (int i = MAX_LENGTH - 1; i >= 0; i--)
		if (arrDigit[i] * sig != integer.arrDigit[i] * integer.sig)
			return false;
	return true;
}

bool Integer::operator!=(const Integer& integer) const
{
	return !(*this == integer);
}



// оператор >=
bool Integer::operator >= (const Integer& integer) const
{
	return (*this > integer || *this == integer);
}

// оператор <=
bool Integer::operator <= (const Integer& integer) const
{
	return (*this < integer || *this == integer);
}


/******************Методы класса Integer(функции члены)**********************/

// перевод между систем счислении -> dec -> нужную систему
Integer Integer::changeNumSystem(NumeralSystem numSys) const
{
	if (this->numSystem == numSys) return *this;
	Integer res(numSys);
	Integer dec = getDec().modul();
	Integer numS(to_string(numSys).c_str(), 10);
	for (int i = 0; i < MAX_LENGTH; i++)
		res.arrDigit[i] = 0;
	res.length = 0;
	res.sig = sig;
	int pos = 0;
	while (true)
	{
		if (dec < numS)
		{
			if (pos >= MAX_LENGTH) throw Exception("Размер числе не поддерживается программой");
			res.arrDigit[pos] = atoi(dec.getString().c_str());
			res.length++;
			break;
		}
		if (pos >= MAX_LENGTH) throw Exception("Размер числе не поддерживается программой");
		Integer remain = dec % numS;
		res.arrDigit[pos++] = atoi(remain.getString().c_str());
		res.length++;
		dec /= numS;
	}
	return res;
}

// возвращает десятичное число
Integer Integer::getDec() const
{
	Integer dec;
	Integer quadr("1", 10);
	Integer numS(to_string(numSystem).c_str(), 10);
	for (int i = 0; i < length; i++)
	{
		Integer bit(to_string(arrDigit[i]).c_str(), 10);
		if (i == 0)
			dec += bit * quadr;
		else
		{
			quadr *= numS;
			dec += bit * quadr;
		}
	}
	return dec;
}

// возарщает модуль
Integer Integer::modul() const
{
	Integer res = *this;
	res.sig = Pos;
	return res;
}

// количество использемых разраядов
int Integer::size() const
{
	return length;
}


// приватная
std::string Integer::getString() const
{
	string str;
	for (int i = 0; i < length; i++)
		str += to_char(arrDigit[length - 1 - i]);
	return str;
}

// дружественная функция перегрузка <<
std::ostream& operator<<(std::ostream & os, Integer & integer)
{
	if (integer.sig == Neg)  os << "-";
	for (int i = integer.length - 1; i >= 0; i--)
		os << to_char(integer.arrDigit[i]);
	return os;
}



/****** вспомогательные функции(свободные функции) *****/

int to_int(char symbol)
{
	switch (symbol)
	{
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
		return atoi(&symbol);
	case 'A': case 'a': return 10;
	case 'B': case 'b': return 11;
	case 'C': case 'c': return 12;
	case 'D': case 'd': return 13;
	case 'E': case 'e': return 14;
	case 'F': case 'f': return 15;
	default: throw Exception("Не подерживающиый символ");
	}
}

char to_char(int num)
{
	switch (num)
	{
	case 0: case 1: case 2: case 3: case 4:
	case 5: case 6: case 7: case 8: case 9:
		return num + '0';
	case 10: return 'A';
	case 11: return 'B';
	case 12: return 'C';
	case 13: return 'D';
	case 14: return 'E';
	case 15: return 'F';
	default: throw Exception("число не поддерживается как отдельная цифра");
	}
}