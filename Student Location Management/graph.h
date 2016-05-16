#ifndef __GRAPH__
#define __GRAPH__

#include "plist.h"
#include "rlist.h"
#include "slist.h"

#include <iostream>
#include <fstream>
using namespace std;

class Graph
{
public:
	Graph();
	Graph(char* filename);
	unsigned int addStu(int key, char *email);
	void printInfo(int key);
	void addRoad(int roadNum, int key1, int key2,int q);
	void deleteStu(int key);
	void deleteRoad(int roadNum);
	void printLinkedRoad(int key);
	void printRoad(int roadNum);
	void printStu(int key,int roadNum);
	void exist(int key1, int key2);

	int N, M;
	SList* slist;
	RList* rlist;
};
#endif