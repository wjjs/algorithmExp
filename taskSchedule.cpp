#include "stdafx.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;
#define n 7   //task number

class task
{
public:
	task()
	{
		;
	}
	int id; //id
	int d;  //deadline
	int w;  //weight
	void set(int id, int d, int w)
	{
		this->id = id;
		this->d = d;
		this->w = w;
	}
};

//initialize tasks
void init(task ta[])
{
	srand(time(NULL));
	for (int i = 0; i < n; i++)
	{
		ta[i].id = i;
		ta[i].d = 1 + rand() % 20;
		ta[i].w = rand() % 50;
	}
}
void iprint(task t)
{
	cout << "id= " << t.id << " task deadline= " << t.d << " task weight= " << t.w << endl;
}

//sort from ta[0] to ta[n-1] with ta.w decreasing
void sortW(task ta[])
{
	task temp;
	//bubble sort
	for (int i = n - 1; i > 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (ta[j].w < ta[j + 1].w)
			{
				temp = ta[j];
				ta[j] = ta[j + 1];
				ta[j + 1] = temp;
			}
		}
	}
}

//sort from ta[0] to ta[k] with ta.d increasing
void sortD(task ta[], int k)
{
	task temp;
	for (int i = k - 1; i > 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (ta[j].d > ta[j + 1].d)
			{
				temp = ta[j];
				ta[j] = ta[j + 1];
				ta[j + 1] = temp;
			}
		}
	}
}

//greedy algorithm,put early tasks in array a and return the number of early tasks
int greedy(task a[], task ta[])
{
	int max = 0, k = 0, i, j;
	int count = 0;

	//Nt[i] is the number of tasks whose deadline is smaller or equals to i
	int Nt[n + 1];
	sortW(ta);
	a[0] = ta[0];
	k = 1;
	for (i = 0; i <= n; i++)
	{
		if (i >= a[0].d)
			Nt[i] = 1;
		else
			Nt[i] = 0;
	}

	for (i = 1; i < n; i++)
	{
		for (j = ta[i].d; j <= n; j++)
		{
			//in this case ta[i] U a is not independent 
			if (Nt[j] + 1 > j)
				break;
		}
		//in this case, ta[i] U a is independent
		if (j >= n + 1)
		{
			a[k] = ta[i];
			k++;
			//update Nt
			for (j = ta[i].d; j <= n; j++)
			{
				Nt[j]++;
			}
		}
	}
	return k;
}

//get the punishment of late tasks
int getW(task a[], task ta[], int k)
{
	int i = 0;
	int sum1 = 0, sum2 = 0;
	for (i = 0; i < k; i++)
	{
		sum1 += a[i].w;
	}
	for (i = 0; i < n; i++)
	{
		sum2 += ta[i].w;
	}
	return sum2 - sum1;
}

int main()
{
	//array tasker stores all of the tasks
	task tasker[n];

	//array A stores the early tasks of tasker
	task A[n];

	//k stores the number of early tasks
	int k = 0; 
	init(tasker);

	/*
	tasker[0].set(1, 4, 70);
	tasker[1].set(2, 2, 60);
	tasker[2].set(3, 4, 50);
	tasker[3].set(4, 3, 40);
	tasker[4].set(5, 1, 30);
	tasker[5].set(6, 4, 20);
	tasker[6].set(7, 6, 10);
	*/

	for (int i = 0; i < n; i++)
	{
		iprint(tasker[i]);
	}
	k = greedy(A, tasker);

	//maxweg stores the maxium weight of tasks
	int maxweg = tasker[0].w;

	//sort the early tasks with deadline increasing
	sortD(A, k);
	cout << "最优调度方案的早任务为：" << endl;
	int i;
	for (i = 0; i < k; i++)
	{
		iprint(A[i]);
	}
	cout << "迟任务惩罚为：" << getW(A, tasker, k) << endl;

	//change weight wi to max{w1,w2,w3...wn}-wi
	for (i = 0; i < n; i++)
	{
		tasker[i].w = maxweg - tasker[i].w;
	}
	k = greedy(A, tasker);
	sortD(A, k);
	cout << "改变惩罚后最优调度方案的早任务为：" << endl;
	for (i = 0; i < k; i++)
	{
		iprint(A[i]);
	}
	cout << "改变后迟任务惩罚为：" << getW(A, tasker, k) << endl;
	return 0;
}

