#pragma once
#include "MyString.h"

class SQL
{
private:
	char keys[3][20];
	bool getData(MyString&);
	bool addData(MyString&);
public:
	SQL();
	~SQL();
	bool query(MyString&);
};