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
	// �Ҽ��� ��°�ڸ����� �ݿø� ǥ��
	cout << fixed << setprecision(2);

	// ���� ����
	ifstream f(filename, ios::in);
	f >> N >> M >> q;  // N: ���̺�ũ��, M: ������ ��, q: �Ҽ�(<N)
	
	// �ؽ����̺� ���� �� �ʱ�ȭ
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
		
		// 1�� �ؽ� �� ���� �ִٸ� 
		if (student[h1].key != NULL)
		{
			// �������� �Ѿ ��
			while (student[(h1 + h2) % N].key != NULL)
			{
				h1 = (h1 + h2) % N;
			}
			// ���ϴٰ� NULL�� ������ ����
			student[(h1 + h2) % N].key = k;
			student[(h1 + h2) % N].score = s;
			strcpy(student[(h1 + h2) % N].email, e);

		}
		// 1�� �ؽ� �� ���� �����ٸ� ����
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
	M++;		//M�� hash table�� ����� ȸ���� ��
	cout << probe << " " << (double)M/N << endl;		//probe�� loadfactor = (ȸ���� / ���̺� ũ��) ���
}

void HashTable::addScore(int key, int score)
{
	int h1 = key % N;
	int h2 = q - key % q;
	probe = 1;

	// 1�� �ؽ� �� ���� NULL�̸� Table�� ������ ����
	if (student[h1].key == NULL)
	{
		cout << probe << " Not found" << endl;
		return;
	}
	// 1�� �ؽ� �� key�� �ٸ��ٸ�
	else if (student[h1].key != key)
	{
		probe++;
		// ���� �ؽ� �� key ���� ���ϴ°� �ƴ� ���
		while (student[(h1 + h2) % N].key != key&& student[(h1 + h2) % N].key != NULL)
		{
			h1 = (h1 + h2) % N;
			probe++;
		}
		// ���� �ؽ� �� key ���� NULL�� ���
		if (student[(h1 + h2) % N].key == NULL)
		{
			cout << probe << " Not found" << endl;
			return;
		}
		// ���� �ؽ� �� key ���� ���� ���
		else
		{ 
			// �߰� �� ������ ��� ���
			if (student[(h1 + h2) % N].score + score > 24)
			{
				cout << probe<< " Exceeded" << endl;
				return;
			}
			student[(h1 + h2) % N].score += score;
			cout << probe << " " << student[(h1 + h2) % N].score << endl;
		}
	}
	// 1�� �ؽ� �� key�� ���ٸ� 
	else
	{
		// �߰� �� ������ ��� ���
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