#include "stdafx.h"
#include "MyString.h"
#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <cctype>
#include <iostream>
#include <vector>

MyString::MyString(const char str[])
{
	this->str = new char[strlen(str) + 1];
	strcpy(this->str, str);
}

MyString::MyString(const MyString &object)
{
	str = new char[strlen(object.str) + 1];
	strcpy(str, object.str);
}

MyString::MyString()
{
	str = new char[1];
	str[0] = '\0';
}


MyString::~MyString()
{
	delete[] str;
}

MyString MyString::operator=(const char str[])
{
	char *new_string = new char[strlen(str) + 1];
	strcpy(new_string, str);

	delete[] this->str;
	this->str = new_string;

	return *this;
}

MyString MyString::operator=(MyString &obj)
{
	*this = obj.str;
	return *this;
}

bool MyString::operator==(const char str[])
{
	return strcmp(this->str, str) == 0;
}

bool MyString::operator==(const int n)
{
	char numStr[12];
	sprintf(numStr, "%d", n);

	return *this == numStr;
}

bool MyString::operator==(const MyString &obj)
{
	return *this == obj.str;
}

bool MyString::operator!=(const char str[])
{
	return !(*this == str);
}

bool MyString::operator!=(const int n)
{
	return !(*this == n);
}

bool MyString::operator!=(const MyString &obj)
{
	return !(*this == obj.str);
}

MyString MyString::trim()
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

int MyString::length()
{
	return strlen(str);
}

std::vector<MyString> MyString::split(const char delimeter)
{
	char str[2] = { delimeter, '\0' };
	return split(str);
}

std::vector<MyString> MyString::split(const char delimeter[])
{
	std::vector<MyString> arr;
	int delimeterLength = strlen(delimeter), start = 0, end;
	char *pointer = str;

	while ((end = indexOf(delimeter, start)) != -1)
	{
		char *localStr = new char[end - start];
		strncpy(localStr, pointer, end - start);
		localStr[end - start] = '\0';
		MyString item = localStr;
		arr.push_back(item);
		pointer += end - start + delimeterLength;
		start = end + delimeterLength;
	}

	if (strlen(pointer))
	{
		MyString item = pointer;
		arr.push_back(item);
	}

	return arr;
}

int MyString::indexOf(const char searchElement, int fromIndex)
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

int MyString::indexOf(const char *searchString, int fromIndex)
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

int MyString::indexOf(const MyString &obj, int fromIndex)
{
	return indexOf(obj.str, fromIndex);
}

int MyString::lastIndexOf(const char searchElement, int fromIndex)
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

MyString MyString::substring(const int start, const int end)
{
	int len = strlen(str);
	MyString result = "";

	if (start >= end || start >= len - 1 || end > len) 
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

MyString MyString::substring(const int start)
{
	return substring(start, strlen(str));
}

ostream &operator<<(ostream &output, const MyString &c)
{
	output << c.str;

	return output;   //  enables cascaded calls
}

void MyString::toLowerCase()
{
	for (int i = 0; i < strlen(str); i++)
	{
		str[i] = tolower(str[i]);
	}
}

void MyString::toUpperCase()
{
	for (int i = 0; i < strlen(str); i++)
	{
		str[i] = toupper(str[i]);
	}
}

char* MyString::toString()
{
	char newStr[255];
	strcpy(newStr, str);

	return str;
}