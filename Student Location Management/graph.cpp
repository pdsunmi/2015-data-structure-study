#include "graph.h"
#include <iostream>
using namespace std;

Graph::Graph()
{
	slist = NULL;
	rlist = NULL;
}
Graph::Graph(char *filename)
{
	ifstream f(filename, ios::in);
	
	f >> N >> M;

	slist = new SList;
	rlist = new RList;

	for (int i = 0; i < N; i++)
	{
		int key;
		char email[41];
		f >> key >> email;
		addStu(key, email);
	}
	for (int i = 0; i < M; i++)
	{
		int roadNum, key1, key2;
		f >> roadNum >> key1 >> key2;
		addRoad(roadNum, key1, key2, 0);	//0은 그래프 구축 도중에 함수를 불렀음을 나타냄
	}

	f.close();
}
unsigned int Graph::addStu(int key, char* email)
{
	Student *s = new Student;
	s->key = key;
	strcpy(s->email, email);
	s->plist = NULL;
	s->snode = new SNode;
	slist->insert(s);

	return slist->sz;
}
void Graph::addRoad(int roadNum, int key1, int key2,int q)
{	
	SNode* tmp = slist->head;
	Student* s1 = NULL;
	Student* s2 = NULL;

	while (tmp != NULL)
	{
		if (tmp->student->key == key1)
		{
			s1 = tmp->student;
			if (s2 != NULL)
				break;
		}
		if (tmp->student->key == key2)
		{
			s2 = tmp->student;
			if (s1 != NULL)
				break;
		}
		tmp = tmp->next;
	}
	if (s1 == NULL || s2 == NULL)
	{
		cout << rlist->sz << " Not found" << endl;
	}
	else
	{
		Road *r = new Road;
		r->roadNum = roadNum;
		r->key1 = key1;
		r->key2 = key2;
		r->prepnode = new PNode;
		r->nextpnode = new PNode;
		r->rnode = new RNode;
		rlist->insert(r);

		r->prestu = s1;
		r->nextstu = s2;

		if (r->prestu->plist == NULL)
		{
			PList *newplist = new PList;
			r->prestu->plist = newplist;
			newplist->insert(newplist, r, 0);	//0은 prestu의 newplist임을 나타냄
		}
		else
		{
			r->prestu->plist->insert(r->prestu->plist, r, 0);
		}

		if (r->nextstu->plist == NULL)
		{
			PList *newplist = new PList;
			r->nextstu->plist = newplist;
			newplist->insert(newplist, r, 1);	//1은 nextstu의 newplist임을 나타냄
		}
		else
		{
			r->nextstu->plist->insert(r->prestu->plist, r, 1);
		}
		if (q==1)	//q가 1이면 질의입력을 통해 함수를 실행한 것이므로 출력해줌
			cout << rlist->sz << endl;
	}
}
void Graph::printInfo(int key)
{
	SNode* tmp = slist->head;
	while (tmp != NULL)
	{
		if (tmp->student->key == key)
		{
			
			if (tmp->student->plist == NULL)
			{
				cout << tmp->student->email << " 0" << endl;
				break;
			}
			else
			{
				cout << tmp->student->email << " " << tmp->student->plist->sz << endl;
				break;
			}
		}
		tmp = tmp->next;
	}
	if (tmp == NULL)
	{
		cout << "Not found" << endl;
	}

}
void Graph::deleteStu(int key)
{
	SNode* tmp = slist->head;
	while (tmp != NULL)
	{
		if (tmp->student->key == key)
			break;
		tmp = tmp->next;
	}
	if (tmp == NULL)
	{
		cout << slist->sz << " " << rlist->sz <<" Not found" << endl;
	}
	else
	{
		Student* s = tmp->student;

		//snode 지우기
		if (tmp->next == NULL&&tmp->prev == NULL)
		{
			slist->head = NULL;
			slist->tail = NULL;
			delete tmp;
		}
		else if (tmp->next == NULL)
		{
			tmp->prev->next = NULL;
			slist->tail = tmp->prev;
			delete tmp;
		}
		else if (tmp->prev == NULL)
		{
			tmp->next->prev = NULL;
			slist->head = tmp->next;
			delete tmp;
		}
		else
		{
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
			delete tmp;
		}
		slist->sz--;

		if (s->plist == NULL)
		{
			cout << slist->sz << " " << rlist->sz << endl;
		}
		else
		{
			PNode* tmp = s->plist->head;
			while (tmp != NULL)
			{
				//인접학생의 pnode 지우기
				if (tmp->road->prestu->key == key)
				{
					//nextpnode 지우기
					PNode* tmp3 = tmp->road->nextpnode;
					PList* plist3 = tmp->road->nextstu->plist;
					plist3->sz--;
					if (tmp3->next == NULL&&tmp3->prev == NULL)
					{
						plist3->head = NULL;
						plist3->tail = NULL;
						delete tmp3;
					}
					else if (tmp3->next == NULL)
					{
						tmp3->prev->next = NULL;
						plist3->tail = tmp3->prev;
						delete tmp3;
					}
					else if (tmp3->prev == NULL)
					{
						tmp3->next->prev = NULL;
						plist3->head = tmp3->next;
						delete tmp3;
					}
					else
					{
						tmp3->prev->next = tmp3->next;
						tmp3->next->prev = tmp3->prev; delete tmp3;
					}
				}
				else if (tmp->road->nextstu->key == key)
				{
					//prepnode 지우기
					PNode* tmp2 = tmp->road->prepnode;
					PList* plist2 = tmp->road->prestu->plist;
					plist2->sz--;
					if (tmp2->next == NULL&&tmp2->prev == NULL)
					{
						plist2->head = NULL;
						plist2->tail = NULL;
						delete tmp2;
					}
					else if (tmp2->next == NULL)
					{
						tmp2->prev->next = NULL;
						plist2->tail = tmp2->prev;
						delete tmp2;
					}
					else if (tmp2->prev == NULL)
					{
						tmp2->next->prev = NULL;
						plist2->head = tmp2->next;
						delete tmp2;
					}
					else
					{
						tmp2->prev->next = tmp2->next;
						tmp2->next->prev = tmp2->prev;
						delete tmp2;
					}
				}

				//rnode 지우기
				RNode* tmp2 = tmp->road->rnode;
				if (tmp2->next == NULL&&tmp2->prev == NULL)
				{
					rlist->head = NULL;
					rlist->tail = NULL;
					delete tmp2;
				}
				else if (tmp2->next == NULL)
				{
					tmp2->prev->next = NULL;
					rlist->tail = tmp2->prev;
					delete tmp2;
				}
				else if (tmp2->prev == NULL)
				{
					tmp2->next->prev = NULL;
					rlist->head = tmp2->next;
					delete tmp2;
				}
				else
				{
					tmp2->prev->next = tmp2->next;
					tmp2->next->prev = tmp2->prev;
					delete tmp2;
				}
				rlist->sz--;

				//road 삭제
				delete tmp->road;
				tmp = tmp->next;
			}
			cout << slist->sz << " " << rlist->sz << endl;
		}

		//student의 plist 삭제
		delete s->plist;
		//student 삭제
		delete s;
		
	}
}
void Graph::deleteRoad(int roadNum)
{
	RNode *tmp = rlist->head;
	while (tmp != NULL)
	{
		if (tmp->road->roadNum == roadNum)
			break;
		tmp = tmp->next;
	}
	if (tmp == NULL)
	{
		cout << rlist->sz << " Not found" << endl;
	}
	else
	{
		//prepnode 지우기
		PNode* tmp2 = tmp->road->prepnode;
		PList* plist2 = tmp->road->prestu->plist;
		plist2->sz--;
		if (tmp2->next == NULL&&tmp2->prev == NULL)
		{
			plist2->head = NULL;
			plist2->tail = NULL;
			delete tmp2;
		}
		else if (tmp2->next == NULL)
		{
			tmp2->prev->next = NULL;
			plist2->tail = tmp2->prev;
			delete tmp2;
		}
		else if (tmp2->prev == NULL)
		{
			tmp2->next->prev = NULL;
			plist2->head = tmp2->next;
			delete tmp2;
		}
		else
		{
			tmp2->prev->next = tmp2->next;
			tmp2->next->prev = tmp2->prev;
			delete tmp2;
		}

		//nextpnode 지우기
		PNode* tmp3 = tmp->road->nextpnode;
		PList* plist3 = tmp->road->nextstu->plist;
		plist3->sz--;
		if (tmp3->next == NULL&&tmp3->prev == NULL)
		{
			plist3->head = NULL;
			plist3->tail = NULL;
			delete tmp3;
		}
		else if (tmp3->next == NULL)
		{
			tmp3->prev->next = NULL;
			plist3->tail = tmp3->prev;
			delete tmp3;
		}
		else if (tmp3->prev == NULL)
		{
			tmp3->next->prev = NULL;
			plist3->head = tmp3->next;
			delete tmp3;
		}
		else
		{
			tmp3->prev->next = tmp3->next;
			tmp3->next->prev = tmp3->prev; delete tmp3;
		}
		
		//road 지우기
		delete tmp->road; 

		//rnode 지우기
		if (tmp->next == NULL&&tmp->prev == NULL)
		{
			rlist->head = NULL;
			rlist->tail = NULL;
			delete tmp;
		}
		else if (tmp->next == NULL)
		{
			tmp->prev->next = NULL;
			rlist->tail = tmp->prev;
			delete tmp;
		}
		else if (tmp->prev == NULL)
		{
			tmp->next->prev = NULL;
			rlist->head = tmp->next;
			delete tmp;
		}
		else
		{
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
			delete tmp;
		}
		rlist->sz--;
		cout << rlist->sz << endl;
	}
}
void Graph::printLinkedRoad(int key)
{
	SNode *tmp = slist->head;
	while (tmp != NULL)
	{
		if (tmp->student->key == key)
			break;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		cout << "Not found" << endl;
	else if (tmp->student->plist == NULL)
		cout << "0" << endl;
	else
	{
		cout << tmp->student->plist->sz;
		PNode* p = tmp->student->plist->head;
		while (p != NULL)
		{
			cout << " "<<p->road->roadNum;
			p = p->next;
		}
		cout << endl;
	}
}
void Graph::printRoad(int roadNum)
{
	RNode* tmp = rlist->head;
	while (tmp != NULL)
	{
		if (tmp->road->roadNum == roadNum)
			break;
		tmp = tmp->next;
	}
	if (tmp == NULL)
	{
		cout << "Not found" << endl;
	}
	else if (tmp->road->prestu->key > tmp->road->nextstu->key)
	{
		cout << tmp->road->nextstu->key << " " << tmp->road->prestu->key << endl;
	}
	else
	{
		cout << tmp->road->prestu->key << " " << tmp->road->nextstu->key << endl;
	}
}
void Graph::printStu(int key, int roadNum)
{
	SNode* s = slist->head;
	while (s != NULL)
	{
		if (s->student->key == key)
			break;
		s = s->next;
	}
	if (s == NULL)
	{
		cout << "Not available" << endl;
	}
	else
	{
		PNode *p = s->student->plist->head;
		while(p != NULL)
		{
			if (p->road->roadNum == roadNum)
				break;
			p = p->next;
		}
		if (p == NULL)
		{
			cout << "Not available" << endl; 
		}
		else
		{
			if (p->road->prestu->key == key)
			{
				cout << p->road->nextstu->key << endl;
			}
			else
				cout << p->road->prestu->key << endl;
		}
	}
}
void Graph::exist(int key1, int key2)
{
	SNode *tmp = slist->head;
	SNode *s1 = NULL;
	SNode *s2 = NULL;
	while (tmp != NULL)
	{
		if (tmp->student->key == key1)
		{
			s1 = tmp;
			if (s2 != NULL)
				break;
		}
		if (tmp->student->key == key2)
		{
			s2 = tmp;
			if (s1 != NULL)
				break;
		}
		tmp = tmp->next;
	}
	if (s1 == NULL || s2 == NULL)
		cout << "Not found" << endl;
	else
	{
		if (s1->student->plist == NULL||s2->student->plist == NULL)
		{
			cout << "Not found" << endl;
		}
		else if (s1->student->plist->sz > s2->student->plist->sz)
		{
			PNode *p = s2->student->plist->head;
			while (p != NULL)
			{
				if (p->road->prestu->key == key1 || p->road->nextstu->key == key1)
				{
					cout << p->road->roadNum << endl;
					break;
				}
				p = p->next;
			}
			if (p == NULL)
				cout << "Not found" << endl;
		}
		else
		{
			PNode *p = s1->student->plist->head;
			while (p != NULL)
			{
				if (p->road->prestu->key == key2 || p->road->nextstu->key == key2)
				{
					cout << p->road->roadNum << endl;
					break;
				}
				p = p->next;
			}
			if (p == NULL)
				cout << "Not found" << endl;
		}
	}
}