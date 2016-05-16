#ifndef __SLIST__
#define __SLIST__

#include "struct.h"
#include <iostream>

struct SNode
{
	Student* student;
	SNode* prev;
	SNode* next;
};
class SList
{
public:
	SList();
	void insert(Student* s);
	SNode* head;
	SNode* tail;
	unsigned int sz;
};
#endif