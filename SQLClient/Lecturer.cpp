#include "stdafx.h"
#include "Lecturer.h"

#include <iostream>

Lecturer::Lecturer()
{
	keys = new char*[keysCount];
}

Lecturer::Lecturer(const char* path) :
	Table(path)
{
	keysCount = 3;
	keys = new char*[keysCount];

	keys[0] = new char[5];
	keys[1] = new char[9];
	keys[2] = new char[4];

	strcpy(keys[0], "name");
	strcpy(keys[1], "lastName");
	strcpy(keys[2], "dep");
}


Lecturer::~Lecturer()
{
	for (int i = 0; i < keysCount; i++)
	{
		delete[] keys[i];
	}

	delete[] keys;
}

bool Lecturer::printData(vector<ExtString> conditions, vector<ExtString> fields)
{
	int n;
	readFile(n);

	Lecturer *rows = static_cast<Lecturer*>(data);

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
			else if (fields[j] == "lastName")
			{
				cout << rows[i].lastName;
			}
			else if (fields[j] == "dep")
			{
				cout << rows[i].dep;
			}

			cout << '\t';
		}

		cout << '\n';
	}

	return true;
}

bool Lecturer::checkConditions(vector<ExtString> conditions, Table *data)
{
	bool matching = true;
	Lecturer *ob = static_cast<Lecturer*>(data);

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
		else if (conditions[j].indexOf("lastName") == 0)
		{
			isEqual = str == ob->lastName;
		}
		else if (conditions[j].indexOf("dep") == 0)
		{
			isEqual = str == ob->dep;
		}

		if (mustEqual ^ isEqual != 0)
		{
			matching = false;
			break;
		}
	}

	return matching;
}

bool Lecturer::addData(vector<ExtString> data)
{
	Lecturer newItem;

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
		else if (data[i].indexOf("lastName") == 0)
		{
			strcpy(newItem.lastName, data[i].substring(data[i].indexOf('=') + 1).trim().toString());
		}
		else if (data[i].indexOf("dep") == 0)
		{
			newItem.dep = (int)data[i].substring(data[i].indexOf('=') + 1).trim();
		}
	}

	FILE *f = fopen(FILE_PATH, "ab");

	fwrite(&newItem, getSize(), 1, f);

	fclose(f);

	cout << "Done\n";

	return true;
}

size_t Lecturer::getSize()
{
	return sizeof(Lecturer);
}

Table* Lecturer::allocateMemory(int n)
{
	// return new Lecturer[n];
	return (Table*)malloc(getSize() * n);
}