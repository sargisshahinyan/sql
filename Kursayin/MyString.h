#pragma warning(disable: 4996)
#pragma once
#include <iostream>
#include <vector>
using std::ostream;
class MyString
{
private:
	char *str;
	friend ostream &operator<<(ostream &, const MyString &);
public:
	MyString();
	MyString(const char str[]);
	MyString(const MyString&);
	~MyString();

	MyString operator=(const char[]);
	MyString operator=(MyString &obj);
	bool operator==(const char[]);
	bool operator==(const int);
	bool operator==(const MyString&);
	bool operator!=(const char[]);
	bool operator!=(const int);
	bool operator!=(const MyString&);

	int length();
	MyString trim();
	std::vector<MyString> split(const char);
	std::vector<MyString> split(const char[]);

	int indexOf(const char, int = 0);
	int indexOf(const char*, int = 0);
	int indexOf(const MyString&, int = 0);
	int lastIndexOf(const char, int = -1);

	MyString substring(const int);
	MyString substring(const int, const int);

	void toLowerCase();
	void toUpperCase();

	char* toString();
};

