/*
	Простая реализация класса для Искючении констуктор принимает строку(string или const char*)
	и хранит в аттрибуте errorStr и  what() возврощает эту строку
*/

//#pragma once
#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>

class Exception
{
public:
	Exception(std::string error) : errorStr(error) { }
	Exception(const char* error) : errorStr((std::string)error) { }
	std::string what() { return this->errorStr; }

private:
	const std::string errorStr;
};

#endif // !EXCEPTION_H



