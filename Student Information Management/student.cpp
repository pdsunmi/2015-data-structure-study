#include <iomanip>
#include <iostream>
#include "student.h"

using namespace std;

HashTable::HashTable()
{
	probe = 0;
}
HashTable::HashTable(char *filename)
{
	// 소수점 셋째자리에서 반올림 표현
	cout << fixed << setprecision(2);

	// 파일 오픈
	ifstream f(filename, ios::in);
	f >> N >> M >> q;  // N: 테이블크기, M: 데이터 수, q: 소수(<N)
	
	// 해시테이블 생성 및 초기화
	student = new Student[N];
	for (int i = 0; i < N; i++)
		student[i].key = NULL;

	int k, s;	 // key, score
	char e[41];  // email
	for (int i = 0; i < M; i++)
	{
		f >> k >> s >> e;

		int h1 = k % N;
		int h2 = q - k % q;
		
		// 1차 해싱 시 값이 있다면 
		if (student[h1].key != NULL)
		{
			// 다음으로 넘어가 비교
			while (student[(h1 + h2) % N].key != NULL)
			{
				h1 = (h1 + h2) % N;
			}
			// 비교하다가 NULL이 나오면 대입
			student[(h1 + h2) % N].key = k;
			student[(h1 + h2) % N].score = s;
			strcpy(student[(h1 + h2) % N].email, e);

		}
		// 1차 해싱 시 값이 없었다면 대입
		else
		{
			student[h1].key = k;
			student[h1].score = s;
			strcpy(student[h1].email, e);
		}
	}
	f.close();
}
void HashTable::put(int key, char *email)
{
	int h1 = key%N;
	int h2 = q - key%q;
	probe = 1;

	if (student[h1].key != NULL)
	{
		probe++;
		while (student[(h1 + h2) % N].key != NULL)
		{
			h1 = (h1 + h2) % N;
			probe++;
		}
		student[(h1 + h2) % N].key = key;
		student[(h1 + h2) % N].score = 0;
		strcpy(student[(h1 + h2) % N].email, email);
		
	}
	else
	{
		student[h1].key = key;
		student[h1].score = 0;
		strcpy(student[h1].email, email);
	}
	M++;		//M은 hash table에 저장된 회원의 수
	cout << probe << " " << (double)M/N << endl;		//probe와 loadfactor = (회원수 / 테이블 크기) 출력
}

void HashTable::addScore(int key, int score)
{
	int h1 = key % N;
	int h2 = q - key % q;
	probe = 1;

	// 1차 해싱 시 값이 NULL이면 Table에 정보가 없음
	if (student[h1].key == NULL)
	{
		cout << probe << " Not found" << endl;
		return;
	}
	// 1차 해싱 시 key와 다르다면
	else if (student[h1].key != key)
	{
		probe++;
		// 다음 해싱 한 key 값이 원하는게 아닐 경우
		while (student[(h1 + h2) % N].key != key&& student[(h1 + h2) % N].key != NULL)
		{
			h1 = (h1 + h2) % N;
			probe++;
		}
		// 다음 해싱 한 key 값이 NULL일 경우
		if (student[(h1 + h2) % N].key == NULL)
		{
			cout << probe << " Not found" << endl;
			return;
		}
		// 다음 해싱 한 key 값이 맞을 경우
		else
		{ 
			// 추가 시 범위를 벗어날 경우
			if (student[(h1 + h2) % N].score + score > 24)
			{
				cout << probe<< " Exceeded" << endl;
				return;
			}
			student[(h1 + h2) % N].score += score;
			cout << probe << " " << student[(h1 + h2) % N].score << endl;
		}
	}
	// 1차 해싱 시 key와 같다면 
	else
	{
		// 추가 시 범위를 벗어날 경우
		if (student[h1].score + score > 24)
		{
			cout << probe << " Exceeded" << endl;
			return;
		}
		student[h1].score += score;
		cout << probe << " " << student[h1].score << endl;
	}
}
void HashTable::changeEmail(int key, char *email)
{
	int h1 = key % N;
	int h2 = q - key % q;
	probe = 1;

	if (student[h1].key == NULL)
	{
		cout << probe << " Not found" << endl;
		return;
	}
	else if (student[h1].key != key)
	{
		probe++;
		while (student[(h1 + h2) % N].key != NULL && student[(h1 + h2) % N].key != key)
		{
			h1 = (h1 + h2) % N;
			probe++;
		}
		if (student[(h1 + h2) % N].key == NULL)
		{
			cout << probe << " Not found" << endl;
			return;
		}
		else
		{
			strcpy(student[(h1 + h2) % N].email,email);
			cout << probe << endl;
			return;
		}
	}
	else
	{
		strcpy(student[h1].email, email);
		cout << probe << endl;
	}
}
void HashTable::print(int key)
{
	int h1 = key%N;
	int h2 = q - key%q;
	probe = 1;

	if (student[h1].key == NULL)
	{
		cout << probe<< " Not found" << endl;
		return;
	}
	else if (student[h1].key != key)
	{
		probe++;
		while (student[(h1 + h2) % N].key != key&& student[(h1 + h2) % N].key != NULL)
		{
			h1 = (h1 + h2) % N;
			probe++;
		}
		if (student[(h1 + h2) % N].key == NULL)
		{
			cout << probe << " Not found" << endl;
			return;
		}
		else
		{
			cout << probe << " " << student[(h1 + h2) % N].key << " " << student[(h1 + h2) % N].score << " " << student[(h1 + h2) % N].email << endl;
			return;
		}
	}
	else
	{
		cout << probe << " " << student[h1].key << " " << student[h1].score << " " << student[h1].email << endl;
	}
}