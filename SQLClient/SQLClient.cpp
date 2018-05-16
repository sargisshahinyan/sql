#include "stdafx.h"
#include <vector>

#include "SQLClient.h"
#include "ExtString.h"
#include "Address.h"
#include "FilePath.h"

using namespace std;

SQLClient::SQLClient()
{
	strcpy(keys[0], "country");
	strcpy(keys[1], "city");
	strcpy(keys[2], "str");
	strcpy(keys[3], "apt");

	// Creating file if not exists
	FILE *f = fopen(FILE_PATH, "a");
	fclose(f);
}

SQLClient::~SQLClient()
{
}

bool SQLClient::exec(ExtString &query)
{
	query.trim();

	if (query.indexOf("SELECT") == 0)
	{
		return selectData(query);
	}
	else if (query.indexOf("ADD") == 0)
	{
		return insertData(query);
	}
	else if (query.indexOf("DELETE") == 0)
	{
		return deleteData(query);
	}

	return false;
}

bool SQLClient::selectData(ExtString &query)
{
	int conditionIndex = query.indexOf("WHERE");

	vector<ExtString> fields = query.substring(query.indexOf("SELECT") + 6, conditionIndex != -1 ? conditionIndex : query.length()).split(',');

	for (int i = 0; i < fields.size(); i++)
	{
		fields[i].trim();

		bool isFiledValid = false;

		for (int j = 0; j < _countof(keys); j++)
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

	vector<ExtString> conditions;

	if (conditionIndex != -1)
	{
		conditions = getConditions(query);
	}

	int n;
	Address *data = readFile(n);

	cout << endl;

	for (int i = 0; i < fields.size(); ++i)
	{
		cout << fields[i] << '\t';
	}

	cout << endl << endl;

	for (int i = 0; i < n; ++i)
	{
		if (!checkConditions(conditions, data[i]))
		{
			continue;
		}

		for (int j = 0; j < fields.size(); ++j)
		{
			if (fields[j] == "country")
			{
				cout << data[i].country;
			}
			else if (fields[j] == "city")
			{
				cout << data[i].city;
			}
			else if (fields[j] == "str")
			{
				cout << data[i].str;
			}
			else if (fields[j] == "apt")
			{
				cout << data[i].apt;
			}

			cout << '\t';
		}

		cout << '\n';
	}

	return true;
}


bool SQLClient::insertData(ExtString &query)
{
	vector<ExtString> data = query.substring(query.indexOf("ADD") + 3).split(',');
	Address newItem;

	if (data.size() != _countof(keys))
	{
		cout << "You need input " << _countof(keys) << " fields, " << data.size() << " given\n";
		return false;
	}

	for (int i = 0; i < data.size(); ++i)
	{
		data[i].trim();

		bool isDataValid = false;

		for (int j = 0; j < _countof(keys); ++j)
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

		if (data[i].indexOf("country") == 0)
		{
			strcpy(newItem.country, data[i].substring(data[i].indexOf('=') + 1).trim().toString());
		}
		else if (data[i].indexOf("city") == 0)
		{
			strcpy(newItem.city, data[i].substring(data[i].indexOf('=') + 1).trim().toString());
		}
		else if (data[i].indexOf("str") == 0)
		{
			strcpy(newItem.str, data[i].substring(data[i].indexOf('=') + 1).trim().toString());
		}
		else if (data[i].indexOf("apt") == 0)
		{
			char num[100];
			strcpy(num, data[i].substring(data[i].indexOf('=') + 1).trim().toString());

			int dec = 0, len;

			len = strlen(num);

			for (int i = 0; i < len; ++i) {
				dec = dec * 10 + (num[i] - '0');
			}

			newItem.apt = dec;
		}
	}

	FILE *f = fopen(FILE_PATH, "ab");

	fwrite(&newItem, sizeof(Address), 1, f);

	fclose(f);

	cout << "Done\n";

	return true;
}

bool SQLClient::deleteData(ExtString &query)
{
	vector<ExtString> conditions;

	if (query.indexOf("WHERE") != -1)
	{
		conditions = getConditions(query);
	}

	int n;
	Address *data = readFile(n);

	FILE *f = fopen(FILE_PATH, "wb");

	for (int i = 0; i < n; ++i)
	{
		if (checkConditions(conditions, data[i]))
		{
			--n;
			if (n != i)
			{
				memmove(data + i, data + i + 1, sizeof(Address));
				--i;
			}
		}
	}

	fwrite(data, sizeof(Address), n, f);
	fclose(f);

	delete[] data;

	cout << "Done\n";

	return true;
}

vector<ExtString> SQLClient::getConditions(ExtString &query)
{
	vector<ExtString> conditions = query.substring(query.indexOf("WHERE") + 5).split(',');

	for (int i = 0; i < conditions.size(); ++i)
	{
		conditions[i].trim();

		bool isConditionValid = false;

		for (int j = 0; j < _countof(keys); ++j)
		{
			if (conditions[i].indexOf(keys[j]) == 0 && conditions[i].indexOf("=") != -1)
			{
				isConditionValid = true;
				break;
			}
		}

		if (!isConditionValid)
		{
			cout << "Problem in condition: " << conditions[i] << '\n';
			exit;
		}
	}

	return conditions;
}

bool SQLClient::checkConditions(vector<ExtString> &conditions, const Address &data)
{
	bool matching = true;

	for (int j = 0; j < conditions.size(); ++j)
	{
		bool mustEqual = conditions[j].indexOf("!=") == -1;
		bool isEqual;

		ExtString str = conditions[j].substring(conditions[j].indexOf("=") + 1);
		str.trim();

		if (conditions[j].indexOf("country") == 0)
		{
			isEqual = str == data.country;
		}
		else if (conditions[j].indexOf("city") == 0)
		{
			isEqual = str == data.city;
		}
		else if (conditions[j].indexOf("str") == 0)
		{
			isEqual = str == data.str;
		}
		else if (conditions[j].indexOf("apt") == 0)
		{
			isEqual = str == data.apt;
		}

		if (mustEqual ^ isEqual != 0)
		{
			matching = false;
			break;
		}
	}

	return matching;
}

Address* SQLClient::readFile(int &n)
{
	FILE *f = fopen(FILE_PATH, "rb");

	fseek(f, 0, SEEK_END);
	int size = ftell(f);
	fseek(f, 0, SEEK_SET);

	n = size / sizeof(Address);

	Address *data = new Address[n];

	fread(data, sizeof(Address), n, f);

	fclose(f);

	return data;
}