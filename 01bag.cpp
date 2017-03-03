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
	cout << "背包容量为：" << C << endl;
	cout << "物品的价值分别是：";
	for (int j = 1; j <= N - 1; j++)
	{
		cout << " " << v[j] << " ";
	}
	cout << endl;
	cout << "物品的重量分别是：";
	for (int i = 1; i <= N - 1; i++)
	{
		cout << " " << w[i] << " ";
	}
	cout << endl;
	cout << "最大价值为：";
	cout << findMaxValue(w, v, flag) << endl;
	cout << "装入背包的物品序号为：";
	for (int j = 0; j <= N - 1; j++)
	{
		if (flag[j] == 1)
			cout << j << "号 ";
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
	for (i = 0; i <= N - 1; i++) //初始化第0列  
	{
		V[i][0] = 0;
	}

	//initialize row 0
	for (j = 0; j <= C; j++) //初始化第0行  
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
	int k = C - 1; //求装入背包的物品  
	for (i = N - 1; i > 0; i--)
	{
		if (V[i][k] > V[i - 1][k])
		{
			flag[i] = 1;
			k = k - w[i];
		}
	}
	return V[N - 1][C];  //返回背包取得的最大值 
}
