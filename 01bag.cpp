#include "stdafx.h"
#include <iostream> 
#include <stdlib.h>
using namespace std;
#define N 7    //N-1 is the number of objects
#define C 16   //container of the bag
int findMaxValue(int w[], int v[], int flag[]);   //01bag algorithem   

int main()
{
	int v[N] = { 0,6,4,3,2,8,1 };
	int w[N] = { 0,2,3,6,2,4,8 };
	int flag[N] = { 0 };
	cout << "��������Ϊ��" << C << endl;
	cout << "��Ʒ�ļ�ֵ�ֱ��ǣ�";
	for (int j = 1; j <= N - 1; j++)
	{
		cout << " " << v[j] << " ";
	}
	cout << endl;
	cout << "��Ʒ�������ֱ��ǣ�";
	for (int i = 1; i <= N - 1; i++)
	{
		cout << " " << w[i] << " ";
	}
	cout << endl;
	cout << "����ֵΪ��";
	cout << findMaxValue(w, v, flag) << endl;
	cout << "װ�뱳������Ʒ���Ϊ��";
	for (int j = 0; j <= N - 1; j++)
	{
		if (flag[j] == 1)
			cout << j << "�� ";
	}
	cout << endl;
	system("pause");
	return 0;
}

int findMaxValue(int w[], int v[], int flag[])
{
	int V[N][C + 1];
	int i;
	int j;

	//initialize column 0
	for (i = 0; i <= N - 1; i++) //��ʼ����0��  
	{
		V[i][0] = 0;
	}

	//initialize row 0
	for (j = 0; j <= C; j++) //��ʼ����0��  
	{
		V[0][j] = 0;
	}

	//calulate two-dimentional-array V
	for (i = 1; i <= N - 1; i++)
	{
		for (j = 1; j <= C; j++)
		{
			if (j < w[i])
				V[i][j] = V[i - 1][j];
			else
			{
				if (V[i - 1][j]  >(V[i - 1][j - w[i]] + v[i]))
				{
					V[i][j] = V[i - 1][j];
				}
				else
				{
					V[i][j] = V[i - 1][j - w[i]] + v[i];
				}
			}
		}
	}
	int k = C - 1; //��װ�뱳������Ʒ  
	for (i = N - 1; i > 0; i--)
	{
		if (V[i][k] > V[i - 1][k])
		{
			flag[i] = 1;
			k = k - w[i];
		}
	}
	return V[N - 1][C];  //���ر���ȡ�õ����ֵ 
}
