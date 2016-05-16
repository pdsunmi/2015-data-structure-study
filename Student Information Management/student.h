#ifndef __STUDENT__
#define __STUDENT__

#include <iostream>
#include <fstream>
using namespace std;

struct Student
{
	int key;
	int score;
	char email[41];
};

class HashTable
{
public:
	HashTable();
	HashTable(char *filename);
	void put(int key, char *email);
	void addScore(int key, int score);
	void changeEmail(int key, char *email);
	void print(int key);

	int probe;			// probe�� Ƚ��
	int N, M, q;		// N: ���̺�ũ��, M: ������ ��, q: �Ҽ�(<N) 

	Student *student;	// Student ����ü �迭�� �����Ҵ� �ޱ����� ����
};
#endif