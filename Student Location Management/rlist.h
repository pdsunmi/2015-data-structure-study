#ifndef __RLIST__
#define __RLIST__

#include "struct.h"
#include <iostream>

struct RNode
{
	Road* road;
	RNode* prev;
	RNode* next;
};
class RList
{
public:
	RList();
	void insert(Road* r);
	RNode* head;
	RNode* tail;
	unsigned int sz;
};

#endif