#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"

#include <cstring>
#include <cctype>
#include <iostream>
#include <vector>

#include "ExtString.h"

ExtString::ExtString(const char str[])
{
	this->str = new char[strlen(str) + 1];
	strcpy(this->str, str);
}

ExtString::ExtString(const ExtString &object)
{
	str = new char[strlen(object.str) + 1];
	strcpy(str, object.str);
}

ExtString::ExtString()
{
	str = new char[1];
	str[0] = '\0';
}


ExtString::~ExtString()
{
	delete[] str;
}

ExtString ExtString::operator=(const char str[])
{
	char *new_string = new char[strlen(str) + 1];
	strcpy(new_string, str);

	delete[] this->str;
	this->str = new_string;

	return *this;
}

ExtString ExtString::operator=(ExtString obj)
{
	char *new_string = new char[strlen(obj.str) + 1];
	strcpy(new_string, obj.str);

	delete[] this->str;
	this->str = new_string;

	return *this;
}

ExtString ExtString::operator+(const char str[])
{
	char *new_string = new char[strlen(this->str) + strlen(str) + 1];
	strcpy(new_string, this->str);
	strcat(new_string, str);

	ExtString newStr = new_string;

	return newStr;
}

ExtString ExtString::operator+(ExtString &obj)
{
	char *new_string = new char[strlen(this->str) + strlen(obj.str) + 1];
	strcpy(new_string, this->str);
	strcat(new_string, obj.str);

	ExtString newStr = new_string;

	return newStr;
}

bool ExtString::operator==(const char str[])
{
	return strcmp(this->str, str) == 0;
}

bool ExtString::operator==(const int n)
{
	char numStr[12];
	sprintf(numStr, "%d", n);

	return *this == numStr;
}

bool ExtString::operator==(const ExtString &obj)
{
	return *this == obj.str;
}

bool ExtString::operator!=(const char str[])
{
	return !(*this == str);
}

bool ExtString::operator!=(const int n)
{
	return !(*this == n);
}

bool ExtString::operator!=(const ExtString &obj)
{
	return !(*this == obj.str);
}

ExtString::operator int() const
{
	int i;
	sscanf(str, "%d", &i);

	return i;
}

char ExtString::operator[](int i) const
{
	return this->str[i];
}

char & ExtString::operator[](int i)
{
	return this->str[i];
}

ExtString ExtString::trim()
{
	int start = 0, end = 0;

	if (!strlen(str))
	{
		return *this;
	}

	while (isspace(str[start])) start++;

	if (start == strlen(str))
	{
		*this = "";
		return *this;
	}

	while (isspace(str[strlen(str) - 1 - end])) end++;
	
	str += start;
	char *newString = new char[strlen(str) + 1 - end];
	
	strncpy(newString, str, strlen(str) - end);
	newString[strlen(str) - end] = '\0';

	str -= start;
	delete[] str;
	str = newString;

	return *this;
}

int ExtString::length()
{
	return strlen(str);
}

std::vector<ExtString> ExtString::split(const char delimeter)
{
	char str[2] = { delimeter, '\0' };
	return split(str);
}

std::vector<ExtString> ExtString::split(const char delimeter[])
{
	std::vector<ExtString> arr;
	int delimeterLength = strlen(delimeter), start = 0, end;
	char *pointer = str;

	while ((end = indexOf(delimeter, start)) != -1)
	{
		char *localStr = new char[end - start];
		strncpy(localStr, pointer, end - start);
		localStr[end - start] = '\0';
		ExtString item = localStr;
		arr.push_back(item);
		pointer += end - start + delimeterLength;
		start = end + delimeterLength;
	}

	if (strlen(pointer))
	{
		ExtString item = pointer;
		arr.push_back(item);
	}

	return arr;
}

int ExtString::indexOf(const char searchElement, int fromIndex)
{
	int len = strlen(str);

	if (fromIndex < 0)
	{
		fromIndex = 0;
	}

	for (int i = fromIndex; i < len; ++i)
	{
		if (str[i] == searchElement)
		{
			return i;
		}
	}

	return -1;
}

int ExtString::indexOf(const char *searchString, int fromIndex)
{
	int len = strlen(str);
	int searchLen = strlen(searchString);
	char *p = str;

	if (fromIndex < 0)
	{
		fromIndex = 0;
	}

	for (int i = fromIndex; i < len - searchLen + 1; ++i)
	{
		if (strncmp(p + i, searchString, searchLen) == 0)
		{
			return i;
		}
	}

	return -1;
}

int ExtString::indexOf(const ExtString &obj, int fromIndex)
{
	return indexOf(obj.str, fromIndex);
}

int ExtString::lastIndexOf(const char searchElement, int fromIndex)
{
	int len = strlen(str);

	if (fromIndex < 0 || fromIndex > len)
	{
		fromIndex = len;
	}

	for (int i = fromIndex - 1; i >= 0; --i)
	{
		if (str[i] == searchElement)
		{
			return i;
		}
	}

	return -1;
}

ExtString ExtString::substring(const int start, const int end)
{
	int len = strlen(str);
	ExtString result = "";

	if (start < 0 || end < 0 || start >= end ||  end > len) 
	{
		return result;
	}

	char *newStr = new char[strlen(str) + 1];

	strcpy(newStr, str);

	newStr += start;

	newStr[end - start] = '\0';

	result = newStr;

	return result;
}

ExtString ExtString::substr(const unsigned int start, const unsigned int count)
{
	ExtString result = "";

	if (start >= strlen(str) || count == 0)
	{
		return result;
	}

	char *new_string = new char[count + 1];

	strncpy(new_string, str + start, count);

	new_string[count] = '\0';

	result = new_string;

	return result;
}

ExtString ExtString::remove(const unsigned int start, const unsigned int count)
{
	if (count == 0)
	{
		return *this;
	}

	if (start + count > strlen(str))
	{
		*this = "";
		return *this;
	}

	char *newStr = new char[strlen(str) + 1 - count];

	strcpy(newStr, substring(0, start).str);
	strcat(newStr, substring(start + count).str);

	delete[] this->str;
	this->str = newStr;

	return *this;
}

ExtString ExtString::substring(const int start)
{
	return substring(start, strlen(str));
}

ostream &operator<<(ostream &output, const ExtString &obj)
{
	output << obj.str;

	return output;
}

istream &operator>>(istream &input, ExtString &obj)
{
	char str[255];
	cin.getline(str, 255, '\n');

	obj = str;

	return input;
}

ExtString operator+(const char *str1, ExtString &str2)
{
	ExtString new_string = str1;

	return new_string + str2;
}

void ExtString::toLowerCase()
{
	for (int i = 0; i < strlen(str); i++)
	{
		str[i] = tolower(str[i]);
	}
}

void ExtString::toUpperCase()
{
	for (int i = 0; i < strlen(str); i++)
	{
		str[i] = toupper(str[i]);
	}
}

const char* ExtString::toString()
{
	return str;
}
