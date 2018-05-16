#include "ExtString.h"
#include "Address.h"

using namespace std;

class SQLClient
{

private:
	char keys[4][20];

	vector<ExtString> getConditions(ExtString&);
	bool checkConditions(vector<ExtString>&, const Address&);
	Address* readFile(int &);

	bool selectData(ExtString&);
	bool insertData(ExtString&);
	bool deleteData(ExtString&);

public:
	SQLClient();
	~SQLClient();
	bool exec(ExtString&);

};