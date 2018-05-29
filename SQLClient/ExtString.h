#pragma warning(disable: 4996)
#pragma once

#include <iostream>
#include <vector>

using namespace std;

class ExtString
{
private:
	char *str;
	friend ostream &operator<<(ostream &, const ExtString &);
	friend istream &operator>>(istream &, ExtString &);
	friend ExtString operator+(const char *, ExtString &);
public:
	ExtString();
	ExtString(const char str[]);
	ExtString(const ExtString&);
	~ExtString();

	ExtString operator=(const char[]);
	ExtString operator=(ExtString obj);
	ExtString operator+(const char[]);
	ExtString operator+(ExtString &obj);
	bool operator==(const char[]);
	bool operator==(const int);
	bool operator==(const ExtString&);
	bool operator!=(const char[]);
	bool operator!=(const int);
	bool operator!=(const ExtString&);
	operator int() const;
	char operator [](int i) const;
	char &operator [](int i);

	int length();
	ExtString trim();
	vector<ExtString> split(const char);
	vector<ExtString> split(const char[]);

	int indexOf(const char, int = 0);
	int indexOf(const char*, int = 0);
	int indexOf(const ExtString&, int = 0);
	int lastIndexOf(const char, int = -1);

	ExtString substring(const int);
	ExtString substring(const int, const int);
	ExtString substr(const unsigned int, const unsigned int);
	ExtString remove(const unsigned int, const unsigned int);

	void toLowerCase();
	void toUpperCase();

	const char* toString();

};

