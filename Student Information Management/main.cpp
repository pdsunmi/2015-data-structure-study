#include <iostream>
#include "student.h"

using namespace std;

int main()
{
	char database[20];
	cin >> database;				
	
	HashTable table(database);		// HashTable 생성

	char query;			// 질의를 나타내는 기호
	int k, s;			// key, score
	char e[41];			// email

	while (true)
	{
		cin >> query;
		switch (query)
		{
		case 'A':
			cin >> k >> e;
			table.put(k, e);
			break;
		case 'U':
			cin >> k >> s;
			table.addScore(k, s);
			break;
		case 'M':
			cin >> k >> e;
			table.changeEmail(k, e);
			break;
		case 'P':
			cin >> k;
			table.print(k);
			break;
		case 'Q':
			exit(0);
		default:
			break;
		}
	}
	return 0;
}