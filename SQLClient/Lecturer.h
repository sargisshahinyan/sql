#pragma once

#include "Table.h"

class Lecturer :
	public Table
{
private:
	char name[200];
	char lastName[200];
	int dep;
public:
	Lecturer();
	Lecturer(const char*);
	~Lecturer();

	bool printData(vector<ExtString>, vector<ExtString>);
	bool checkConditions(vector<ExtString>, Table*);
	bool addData(vector<ExtString>);
	size_t getSize();
	virtual Table* allocateMemory(int);
};

