#include "stdafx.h"
#include <vector>

#include "SQLClient.h"
#include "ExtString.h"
#include "Address.h"
#include "Lecturer.h"
#include "FilePath.h"
#include "Laboratory.h"

using namespace std;

SQLClient::SQLClient(ExtString query)
{
	bool intoExists = query.indexOf("INTO") != -1;
	bool fromExists = query.indexOf("FROM") != -1;
	ExtString table;

	if (!(intoExists ^ fromExists))
	{
		return;
	}

	if (fromExists) 
	{
		//if (query.indexOf("SELECT") == -1 || query.indexOf("SELECT") > query.indexOf("FROM") || (query.indexOf("WHERE") != -1 && query.indexOf("FROM") > query.indexOf("WHERE")))
		//{
		//	return;
		//}

		int conditionsIndex = query.indexOf("WHERE");
		table = query.substring(query.indexOf("FROM") + 4, conditionsIndex != -1 ? conditionsIndex : query.length());
	}
	else
	{
		if (query.indexOf("ADD") == -1 || query.indexOf("ADD") > query.indexOf("INTO") || query.indexOf("INTO") > query.indexOf("VALUES"))
		{
			return;
		}

		table = query.substring(query.indexOf("INTO") + 4, query.indexOf("VALUES"));
	}

	table.trim();

	if (table == "Lecturer")
	{
		this->table = new Lecturer("lecturer.dat");
	}
	else if (table == "Laboratory")
	{
		this->table = new Laboratory("laboratory.dat");
	}
	else
	{
		return;
	}

	this->query = query;
}

SQLClient::~SQLClient()
{
	if (query.length())
	{
		delete table;
	}
}

bool SQLClient::exec()
{
	query.trim();

	if (!query.length())
	{
		return false;
	}

	if (query.indexOf("SELECT") == 0)
	{
		return selectData();
	}
	else if (query.indexOf("ADD") == 0)
	{
		return insertData();
	}
	else if (query.indexOf("DELETE") == 0)
	{
		return deleteData();
	}

	return false;
}

bool SQLClient::selectData()
{
	vector<ExtString> fields = query.substring(6, query.indexOf("FROM")).split(',');

	table->checkFields(fields);

	vector<ExtString> conditions;

	if (query.indexOf("WHERE") != -1)
	{
		conditions = getConditions();
	}

	return table->printData(conditions, fields);
}

bool SQLClient::insertData()
{
	vector<ExtString> data = query.substring(query.indexOf("VALUES") + 6).trim().split(',');
	
	return table->addData(data);
}

bool SQLClient::deleteData()
{
	vector<ExtString> conditions;

	if (query.indexOf("WHERE") != -1)
	{
		conditions = getConditions();
	}

	return table->deleteData(conditions);
}

vector<ExtString> SQLClient::getConditions()
{
	vector<ExtString> conditions = query.substring(query.indexOf("WHERE") + 5).split(',');
	vector<ExtString> fields;

	for (int i = 0; i < conditions.size(); ++i)
	{
		fields.push_back(conditions[i].substring(0, conditions[i].indexOf(conditions[i].indexOf("!=") != -1 ? "!=" : "=")));
	}

	if (!table->checkFields(fields))
	{
		exit;
	}

	return conditions;
}