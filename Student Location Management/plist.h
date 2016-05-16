#ifndef __PLIST__
#define __PLIST__

#include "struct.h"
#include <iostream>

struct PNode
{
	Road* road;
	PNode* prev;
	PNode* next;
};
class PList
{
public:
	PList();
	void insert(PList *plist, Road* r, int q);
	PNode* head;
	PNode* tail;
	unsigned int sz;
};
#endif