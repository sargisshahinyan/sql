#pragma warning(disable: 4996)
#pragma once

#include <iostream>
#include <vector>

using std::ostream;

class ExtString
{

private:
	char *str;
	friend ostream &operator<<(ostream &, const ExtString &);

public:
	ExtString();
	ExtString(const char str[]);
	ExtString(const ExtString&);
	~ExtString();

	ExtString operator=(const char[]);
	ExtString operator=(ExtString &obj);
	bool operator==(const char[]);
	bool operator==(const int);
	bool operator==(const ExtString&);
	bool operator!=(const char[]);
	bool operator!=(const int);
	bool operator!=(const ExtString&);

	int length();
	ExtString trim();
	std::vector<ExtString> split(const char);
	std::vector<ExtString> split(const char[]);

	int indexOf(const char, int = 0);
	int indexOf(const char*, int = 0);
	int indexOf(const ExtString&, int = 0);
	int lastIndexOf(const char, int = -1);

	ExtString substring(const int);
	ExtString substring(const int, const int);

	void toLowerCase();
	void toUpperCase();

	char* toString();

};

