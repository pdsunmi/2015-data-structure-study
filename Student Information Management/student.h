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

	int probe;			// probe의 횟수
	int N, M, q;		// N: 테이블크기, M: 데이터 수, q: 소수(<N) 

	Student *student;	// Student 구조체 배열을 동적할당 받기위해 선언
};
#endif