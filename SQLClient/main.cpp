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
		cout << "SQLClient: ";
		cin.getline(str, 200, '\n');
		
		ExtString query = str;
		SQLClient sql(query);

		if (query == "quit")
		{
			break;
		}

		bool result = sql.exec();

		if (!result)
		{
			cout << "Query is not falid\n";
		}
	}

	return 0; 
}