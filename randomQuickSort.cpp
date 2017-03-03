#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#define MAX_SIZE 100000
using namespace std;

void swap(int & i, int & j)
{
	int temp = i;
	i = j;
	j = temp;
}

void RandomQuickSort(int *array, int start, int end)
{
	if (start >= end) 
		return;

	int ram = (int)(rand() % (end - start + 1)) + start;
	swap(array[ram],array[end]);

	int x = array[end];
	int i = start - 1;
	for (int j = start; j < end; j++)
	{
		if (array[j] <= x)
		{
			i++;
			swap(array[i], array[j]);
		}
	}
	swap(array[i+1], array[end]);
	RandomQuickSort(array, start, i);
	RandomQuickSort(array, i + 2, end);
}

void QuickSort(int *array, int start, int end)
{
	if (start >= end) 
		return;
	int x = array[end];
	int i = start - 1;
	for (int j = start; j < end; j++)
	{
		if (array[j] <= x)
		{
			i++;
			swap(array[i], array[j]);
		}
	}
	swap(array[i+1], array[end]);

	QuickSort(array, start, i);
	QuickSort(array, i + 2, end);
}

int main()
{
	int array[MAX_SIZE];
	int backup[MAX_SIZE];
	int ibeg, iend;
	int n;
	cout << "请输入要排序的数字的个数（最大为 " << MAX_SIZE << " ): " <<endl;
	cin >> n;

	for (int j = 0; j < 10; j++)
	{
		srand(time(NULL));

		for (int i = 0; i < n; i++)
		{
			array[i] = rand() % (j+1000);
			backup[i] = array[i];
		}
		
		ibeg = clock();
		RandomQuickSort(backup, 0, n - 1);
		iend = clock();
		cout << "一共排序" << n << "个数，随机快排耗时 " << iend - ibeg << " ms，";

		ibeg = clock();
		QuickSort(array, 0, n-1);
		iend = clock();
		cout << " 普通快排耗时 " << iend - ibeg << " ms \n";
	}
	return 0;
}


