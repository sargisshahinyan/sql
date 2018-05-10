#include "stdafx.h"
#include "SQL.h"
#include "MyString.h"
#include "Lecturer.h"

#include <vector>

#define FILE_PATH "C:\\Users\\shahi\\Desktop\\data.dat"

using namespace std;

SQL::SQL()
{
	strcpy(keys[0], "name");
	strcpy(keys[1], "lastName");
	strcpy(keys[2], "dep");
}

SQL::~SQL()
{
}

bool SQL::query(MyString &query)
{
	query.trim();

	if (query.indexOf("SELECT") == 0)
	{
		return getData(query);
	}
	else if (query.indexOf("ADD") == 0)
	{
		return addData(query);
	}

	return false;
}

bool SQL::getData(MyString &query)
{
	int conditionIndex = query.indexOf("WHERE");

	vector<MyString> fields = query.substring(query.indexOf("SELECT") + 6, conditionIndex != -1 ? conditionIndex : query.length()).split(',');

	for (int i = 0; i < fields.size(); ++i)
	{
		fields[i].trim();

		bool isFiledValid = false;

		for (int j = 0; j < 3; j++)
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

	vector<MyString> conditions;

	if (conditionIndex != -1)
	{
		conditions = query.substring(query.indexOf("WHERE") + 5).split(',');

		for (int i = 0; i < conditions.size(); ++i)
		{
			conditions[i].trim();

			bool isConditionValid = false;

			for (int j = 0; j < 3; ++j)
			{
				if (conditions[i].indexOf(keys[j]) == 0 && (conditions[i].indexOf("==") != -1 || conditions[i].indexOf("!=") != -1))
				{
					isConditionValid = true;
					break;
				}
			}

			if (!isConditionValid)
			{
				cout << "Problem in condition: " << conditions[i] << '\n';
				return false;
			}
		}
	}

	// Creating file if not exists
	FILE *f = fopen(FILE_PATH, "a");
	fclose(f);

	f = fopen(FILE_PATH, "rb");

	fseek(f, 0, SEEK_END);
	int size = ftell(f);
	fseek(f, 0, SEEK_SET);

	int n = size / sizeof(Lecturer);

	Lecturer *data = new Lecturer[n];

	fread(data, sizeof(Lecturer), n, f);

	fclose(f);

	cout << endl;

	for (int i = 0; i < fields.size(); ++i)
	{
		cout << fields[i] << '\t';
	}

	cout << endl << endl;

	for (int i = 0; i < n; ++i)
	{
		bool matching = true;

		for (int j = 0; j < conditions.size(); ++j)
		{
			bool mustEqual = conditions[j].indexOf("==") != -1;
			bool isEqual;

			MyString str = conditions[j].substring(conditions[j].indexOf(mustEqual ? "==" : "!=") + 2);
			str.trim();

			if (conditions[j].indexOf("name") == 0)
			{
				isEqual = str == data[i].name;
			}
			else if (conditions[j].indexOf("lastName") == 0)
			{
				isEqual = str == data[i].lastName;
			}
			else if (conditions[j].indexOf("dep") == 0)
			{
				isEqual = str == data[i].dep;
			}

			if (mustEqual ^ isEqual != 0)
			{
				matching = false;
				break;
			}
		}

		if (!matching)
		{
			continue;
		}

		for (int j = 0; j < fields.size(); ++j)
		{
			if (fields[j] == "name")
			{
				cout << data[i].name;
			}
			else if (fields[j] == "lastName")
			{
				cout << data[i].lastName;
			}
			else if (fields[j] == "dep")
			{
				cout << data[i].dep;
			}

			cout << '\t';
		}

		cout << '\n';
	}

	return true;
}


bool SQL::addData(MyString &query)
{
	vector<MyString> data = query.substring(query.indexOf("ADD") + 3).split(',');
	Lecturer newItem;

	if (data.size() != 3)
	{
		cout << "You need input 3 fields, " << data.size() << " given\n";
		return false;
	}

	for (int i = 0; i < data.size(); ++i)
	{
		data[i].trim();

		bool isDataValid = false;

		for (int j = 0; j < 3; ++j)
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
			char num[100];
			strcpy(num, data[i].substring(data[i].indexOf('=') + 1).trim().toString());

			int dec = 0, len;

			len = strlen(num);

			for (int i = 0; i < len; ++i) {
				dec = dec * 10 + (num[i] - '0');
			}

			newItem.dep = dec;
		}
	}

	FILE *f = fopen(FILE_PATH, "ab");

	fwrite(&newItem, sizeof(Lecturer), 1, f);

	fclose(f);

	cout << "Done\n";

	return true;
}