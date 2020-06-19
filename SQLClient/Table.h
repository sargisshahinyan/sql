#pragma once

#include "ExtString.h"
#include <vector>

using namespace std;

class Table
{
protected:
	char* FILE_PATH = NULL;
	char **keys = NULL;
	int keysCount = 0;
	Table *data = NULL;
	virtual void readFile(int &);
public:
	Table();
	Table(const char*);
	virtual ~Table();

	virtual bool printData(vector<ExtString>, vector<ExtString>) = 0;
	virtual bool checkConditions(vector<ExtString>, Table*) = 0;
	virtual bool deleteData(vector<ExtString>)=0;
	virtual bool addData(vector<ExtString>) = 0;
	virtual bool checkFields(vector<ExtString>&);
	virtual size_t getSize();
	virtual Table* allocateMemory(int) = 0;
};