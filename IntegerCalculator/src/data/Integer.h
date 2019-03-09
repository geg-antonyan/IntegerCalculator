/* ***Integer.h***
	Класс integer универсальный класс для чисел разных систем счислении. практический пригоден для любых систем счислении
	но в программе ограничивается от 2 до 16. имеет три конструктора один по умолчанию создает пустое число с 10 системой счислении
	, второй конструктор принимает как аргумент систему счислении и создает так же пустое число(длина = 0) а третый
	принмает строковое число и систему счислении(по умолчанию 10) и соответсвенно проверяя при не соответсви бросая в исключени.
	не допускается ввод несколько нолей в начале или -0. ноль принимается если он не в начале или в начале но единственный
	в процессе всех задач выполняктся проверка MAX_LENGTH так как я не неашел способ как переопредилить сому оператор [] массива
	int. Наверника будет это вшито в c++ но я не стал искать. в програме перегрудены все операторы по задании.
	Реализация класса в Integer.cpp. Коечно все операции легче было бы перевести числа на int сделать операцию и потов вернуть
	в нужное систему счислении, но так как в задаче условии хранить числа в разрядах массива то и все операции выполняютс с
	разрядами алгоритм которого известен всем со школы. хотя и код немного длинный но дает возможность сделать операции 
	числами с большимы разрядами. в програме 64 разряда. следует быть осторожным в случе перевода чисел скажем с 16 по 2
	так как для 2 число разрядом может не хватать и будет перехват исключении. конечно можно было бы сделать какое то значении
	максимальным скаже для двочного который занимает все разряди и кажды раз перед инициализации проверять числа чтобы не пере
	вишал это значении, но тога для 16 числе использывалось намного бы меньше бита.
*/
#ifndef INTEGER_H
#define INTEGER_H



#include <fstream>


typedef int NumeralSystem;
typedef const char* Digits;
enum Sig { Pos = 1, Neg = -1 };

class Integer
{

public:
	Integer();
	Integer(NumeralSystem);
	Integer(Digits, NumeralSystem numSystem = 10);
	~Integer();

	Integer operator + (const Integer&) const;
	Integer operator - (const Integer&) const;
	Integer operator * (const Integer&) const;
	Integer operator / (const Integer&) const;
	Integer operator % (const Integer&) const;

	Integer operator++(int);
	Integer operator++();
	Integer operator--(int);
	Integer operator--();

	void operator +=   (const Integer&);
	void operator -=   (const Integer&);
	void operator *=   (const Integer&);
	void operator /=   (const Integer&);
	void operator %=   (const Integer&);

	bool operator <    (const Integer&) const;
	bool operator >    (const Integer&) const;
	bool operator >=   (const Integer&) const;
	bool operator <=   (const Integer&) const;
	bool operator ==   (const Integer&) const;
	bool operator !=   (const Integer&) const;

	Integer changeNumSystem(NumeralSystem) const;
	Integer modul() const;
	Integer getDec() const;
	
	int size() const;

	friend std::ostream& operator<< (std::ostream& os, Integer& integer);
private:

	static const int MAX_LENGTH = 64;
	int arrDigit[MAX_LENGTH];
	int length;
	Sig sig;
	NumeralSystem numSystem;

	std::string getString() const;
};

#endif // !INTEGER_H



