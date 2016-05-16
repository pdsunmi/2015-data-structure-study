#include "rlist.h"

RList::RList()
{
	head = NULL;
	tail = NULL;
	sz = 0;
}
void RList::insert(Road *r)
{
	if (sz == 0)
	{
		head = r->rnode;
		tail = r->rnode;
		r->rnode->prev = NULL;
		r->rnode->next = NULL;
		r->rnode->road = r;
		sz++;
	}
	else
	{
		tail->next = r->rnode;
		r->rnode->next = NULL;
		r->rnode->prev = tail;
		tail = r->rnode;
		r->rnode->road = r;
		sz++;
	}
}