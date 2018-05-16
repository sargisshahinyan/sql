#include "stdafx.h"
#include <iostream>

#include "ExtString.h"
#include "SQLClient.h"

using namespace std;

int main()
{
	char str[200];

	while (true)
	{
		cout << "SQLClient:~ arobert$ ";
		cin.getline(str, 200, '\n');

		SQLClient sql;
		ExtString query = str;

		bool result = sql.exec(query);

		if (!result)
		{
			cout << "Query is not falid\n";
		}
	}

	return 0; 
}