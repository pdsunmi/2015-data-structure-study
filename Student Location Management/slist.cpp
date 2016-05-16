#include "slist.h"

SList::SList()
{
	head = NULL;
	tail = NULL;
	sz = 0;
}
void SList::insert(Student *s)
{
	if (sz == 0)
	{
		head = s->snode;
		tail = s->snode;
		s->snode->prev = NULL;
		s->snode->next = NULL;
		s->snode->student = s;
		sz++;
	}
	else
	{
		tail->next = s->snode;
		s->snode->next = NULL;
		s->snode->prev = tail;
		tail = s->snode;
		s->snode->student = s;
		sz++;
	}
}