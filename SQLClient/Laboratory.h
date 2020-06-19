#pragma once
#include "Table.h"
class Laboratory :
	public Table
{
private:
	char name[200];
	int roomNumber;
public:
	Laboratory();
	Laboratory(const char*);
	~Laboratory();

	bool printData(vector<ExtString>, vector<ExtString>);
	bool checkConditions(vector<ExtString>, Table*);
	bool addData(vector<ExtString>);
	bool deleteData(vector<ExtString>);
	size_t getSize();
	virtual Table* allocateMemory(int);
};
