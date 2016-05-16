#include "plist.h"

PList::PList()
{
	head = NULL;
	tail = NULL;
	sz = 0;
}
void PList::insert(PList *plist, Road *r, int q)
{
	if (q == 0)
	{
		if (sz == 0)
		{
			head = r->prepnode;
			tail = r->prepnode;
			r->prepnode->prev = NULL;
			r->prepnode->next = NULL;
			r->prepnode->road = r;
			sz++;
		}
		else
		{
			tail->next = r->prepnode;
			r->prepnode->next = NULL;
			r->prepnode->prev = tail;
			tail = r->prepnode;
			r->prepnode->road = r;
			sz++;
		}
	}
	else
	{
		if (sz == 0)
		{
			head = r->nextpnode;
			tail = r->nextpnode;
			r->nextpnode->prev = NULL;
			r->nextpnode->next = NULL;
			r->nextpnode->road = r;
			sz++;
		}
		else
		{
			tail->next = r->nextpnode;
			r->nextpnode->next = NULL;
			r->nextpnode->prev = tail;
			tail = r->nextpnode;
			r->nextpnode->road = r;
			sz++;
		}
	}
}