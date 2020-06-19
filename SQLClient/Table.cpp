#include "stdafx.h"
#include "Table.h"

#include <cstring>
#include <cstdlib>

Table::Table()
{
	FILE_PATH = new char[1];
	strcpy(FILE_PATH, "");
}

Table::Table(const char* path)
{
	FILE_PATH = new char[strlen(path) + 1];
	strcpy(FILE_PATH, path);

	// Creating file if not exists
	FILE *f = fopen(FILE_PATH, "a");
	fclose(f);
}


Table::~Table()
{
	if (data != NULL)
	{
		// delete[] data; 
		free(data);
	}

	delete[] FILE_PATH;
}

bool Table::deleteData(vector<ExtString> conditions)
{
	return false;
	int n;
	readFile(n);

	FILE *f = fopen(FILE_PATH, "wb");

	for (int i = 0; i < n; ++i)
	{
		if (checkConditions(conditions, &data[i]))
		{
			--n;
			if (n != i)
			{
				memmove(data + i, data + i + 1, this->getSize());
				--i;
			}
		}
	}

	fwrite(data, this->getSize(), n, f);
	fclose(f);

	cout << "Done\n";

	return true;
}

void Table::readFile(int &n)
{
	FILE *f = fopen(FILE_PATH, "rb");

	fseek(f, 0, SEEK_END);
	int size = ftell(f);
	fseek(f, 0, SEEK_SET);

	n = size / getSize();

	data = allocateMemory(n);

	fread(data, getSize(), n, f);

	fclose(f);
}

bool Table::checkFields(vector<ExtString> &fields)
{
	for (int i = 0; i < fields.size(); i++)
	{
		fields[i].trim();

		bool isFiledValid = false;

		for (int j = 0; j < keysCount; j++)
		{
			if (fields[i] == keys[j])
			{
				isFiledValid = true;
				break;
			}
		}

		if (!isFiledValid)
		{
			cout << "Field is invalid: " << fields[i] << '\n';
			return false;
		}
	}

	return true;
}

size_t Table::getSize()
{
	return sizeof(Table);
}