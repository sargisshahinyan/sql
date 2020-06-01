#include "stdafx.h"
#include "Laboratory.h"

#include "stdafx.h"

#include <iostream>

Laboratory::Laboratory()
{
	keys = new char*[keysCount];
}

Laboratory::Laboratory(const char* path) :
	Table(path)
{
	keysCount = 2;
	keys = new char*[keysCount];

	keys[0] = new char[5];
	keys[1] = new char[11];

	strcpy(keys[0], "name");
	strcpy(keys[1], "roomNumber");
}


Laboratory::~Laboratory()
{
	for (int i = 0; i < keysCount; i++)
	{
		delete[] keys[i];
	}

	delete[] keys;
}

bool Laboratory::printData(vector<ExtString> conditions, vector<ExtString> fields)
{
	int n;
	readFile(n);

	Laboratory *rows = static_cast<Laboratory*>(data);

	for (int i = 0; i < fields.size(); ++i)
	{
		cout << fields[i] << '\t';
	}

	cout << endl << endl;

	for (int i = 0; i < n; ++i)
	{
		if (!checkConditions(conditions, rows + i))
		{
			continue;
		}

		for (int j = 0; j < fields.size(); ++j)
		{
			if (fields[j] == "name")
			{
				cout << rows[i].name;
			}
			else if (fields[j] == "roomNumber")
			{
				cout << rows[i].roomNumber;
			}

			cout << '\t';
		}

		cout << '\n';
	}

	return true;
}

bool Laboratory::checkConditions(vector<ExtString> conditions, Table *data)
{
	if (conditions.size() == 0)
		return true;

	Laboratory *ob = static_cast<Laboratory*>(data);

	for (int j = 0; j < conditions.size(); ++j)
	{
		conditions[j].trim();

		bool mustEqual = conditions[j].indexOf("!=") == -1;
		bool isEqual = mustEqual;

		ExtString str = conditions[j].substring(conditions[j].indexOf("=") + 1);
		str.trim();

		if (conditions[j].indexOf("name") == 0)
		{
			isEqual = str == ob->name;
		}
		else if (conditions[j].indexOf("roomNumber") == 0)
		{
			isEqual = str == ob->roomNumber;
		}

		if (mustEqual ^ isEqual != 0)
		{
			return false;
			break;
		}
	}

	return true;
}

bool Laboratory::addData(vector<ExtString> data)
{
	Laboratory newItem;

	if (data.size() != keysCount)
	{
		cout << "You need input " << keysCount << " fields, " << data.size() << " given\n";
		return false;
	}

	for (int i = 0; i < data.size(); ++i)
	{
		data[i].trim();

		bool isDataValid = false;

		for (int j = 0; j < keysCount; ++j)
		{
			if (data[i].indexOf(keys[j]) == 0 && data[i].indexOf('=') != -1)
			{
				isDataValid = true;
				break;
			}
		}

		if (!isDataValid)
		{
			cout << "Problem in data: " << data[i] << '\n';
			return false;
		}

		if (data[i].indexOf("name") == 0)
		{
			strcpy(newItem.name, data[i].substring(data[i].indexOf('=') + 1).trim().toString());
		}
		else if (data[i].indexOf("roomNumber") == 0)
		{
			newItem.roomNumber = (int)data[i].substring(data[i].indexOf('=') + 1).trim();
		}
	}

	FILE *f = fopen(FILE_PATH, "ab");

	fwrite(&newItem, getSize(), 1, f);

	fclose(f);

	cout << "Done\n";

	return true;
}

size_t Laboratory::getSize()
{
	return sizeof(Laboratory);
}

Table* Laboratory::allocateMemory(int n)
{
	// return new Lecturer[n];
	return (Table*)malloc(getSize() * n);
}

bool Laboratory::deleteData(vector<ExtString> conditions)
{
	int n;
	readFile(n);

	FILE *f = fopen(FILE_PATH, "wb");
	Laboratory *rows = static_cast<Laboratory*>(data);

	for (int i = 0; i < n; ++i)
	{
		if (checkConditions(conditions, rows + i))
		{
			--n;
			if (n != i)
			{
				memmove(rows + i, rows + i + 1, this->getSize());
				--i;
			}
		}
	}

	fwrite(data, this->getSize(), n, f);
	fclose(f);

	cout << "Done\n";

	return true;
}