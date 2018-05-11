#pragma once
#include "MyString.h"
#include "Lecturer.h"

#include <vector>

using namespace std;

class SQL
{
private:
	char keys[3][20];

	vector<MyString> getConditions(MyString&);
	bool checkConditions(vector<MyString>&, const Lecturer&);
	Lecturer* readFile(int &);

	bool getData(MyString&);
	bool addData(MyString&);
	bool removeData(MyString&);

	
public:
	SQL();
	~SQL();
	bool query(MyString&);
};