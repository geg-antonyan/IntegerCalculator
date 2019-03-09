/* ***Integer.h***
	����� integer ������������� ����� ��� ����� ������ ������ ���������. ������������ �������� ��� ����� ������ ���������
	�� � ��������� �������������� �� 2 �� 16. ����� ��� ������������ ���� �� ��������� ������� ������ ����� � 10 �������� ���������
	, ������ ����������� ��������� ��� �������� ������� ��������� � ������� ��� �� ������ �����(����� = 0) � ������
	�������� ��������� ����� � ������� ���������(�� ��������� 10) � ������������� �������� ��� �� ���������� ������ � ���������.
	�� ����������� ���� ��������� ����� � ������ ��� -0. ���� ����������� ���� �� �� � ������ ��� � ������ �� ������������
	� �������� ���� ����� ����������� �������� MAX_LENGTH ��� ��� � �� ������ ������ ��� �������������� ���� �������� [] �������
	int. ��������� ����� ��� ����� � c++ �� � �� ���� ������. � �������� ����������� ��� ��������� �� �������.
	���������� ������ � Integer.cpp. ������ ��� �������� ����� ���� �� ��������� ����� �� int ������� �������� � ����� �������
	� ������ ������� ���������, �� ��� ��� � ������ ������� ������� ����� � �������� ������� �� � ��� �������� ���������� �
	��������� �������� �������� �������� ���� �� �����. ���� � ��� ������� ������� �� ���� ����������� ������� �������� 
	������� � �������� ���������. � �������� 64 �������. ������� ���� ���������� � ����� �������� ����� ������ � 16 �� 2
	��� ��� ��� 2 ����� �������� ����� �� ������� � ����� �������� ����������. ������� ����� ���� �� ������� ����� �� ��������
	������������ ����� ��� �������� ������� �������� ��� ������� � ����� ��� ����� ������������� ��������� ����� ����� �� ����
	����� ��� ��������, �� ���� ��� 16 ����� �������������� ������� �� ������ ����.
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



