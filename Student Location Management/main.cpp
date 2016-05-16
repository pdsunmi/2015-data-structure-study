#include <iostream>
#include "graph.h"
using namespace std;

int main()
{
	char database[20];
	cin >> database;

	Graph graph(database);
	int key, key1, key2, roadNum;
	char email[41];
	char query;
	while (true)
	{
		cin >> query;
		switch (query)
		{
		case 'A':
			cin >> key >> email;
			cout << graph.addStu(key, email) << endl;
			break;
		case 'P':
			cin >> key;
			graph.printInfo(key);
			break;
		case 'I':
			cin >> roadNum >> key1 >> key2;
			graph.addRoad(roadNum, key1, key2,1);
			break;
		case 'X':
			cin >> key;
			graph.deleteStu(key);
			break;
		case 'Z':
			cin >> roadNum;
			graph.deleteRoad(roadNum);
			break;
		case 'L':
			cin >> key;
			graph.printLinkedRoad(key);
			break;
		case 'F':
			cin >> roadNum;
			graph.printRoad(roadNum);
			break;
		case 'O':
			cin >> key >> roadNum;
			graph.printStu(key, roadNum);
			break;
		case 'K':
			cin >> key1 >> key2;
			graph.exist(key1, key2);
			break;
		case 'Q':
			exit(0);
		default:
			break;
		}
	}
	return 0;
}