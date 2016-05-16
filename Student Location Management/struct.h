#ifndef __STRUCT__
#define __STRUCT__

class PList;
struct SNode;
struct RNode;
struct PNode;

struct Student
{
	int key;
	char email[41];
	SNode* snode;
	PList* plist;
};
struct Road
{
	int roadNum;
	int key1;
	int key2;
	RNode* rnode;
	Student* prestu;
	Student* nextstu;
	PNode* prepnode;
	PNode* nextpnode;
};

#endif