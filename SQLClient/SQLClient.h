#include "ExtString.h"
#include "Address.h"
#include "Table.h"

using namespace std;

class SQLClient
{

private:
	char keys[4][20];
	ExtString query = "";
	Table *table;

	vector<ExtString> getConditions();

	bool selectData();
	bool insertData();
	bool deleteData();

public:
	SQLClient(ExtString);
	~SQLClient();
	bool exec();

};