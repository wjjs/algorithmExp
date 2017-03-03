#include "stdafx.h"
#include <iostream>
#define MAX_SIZE 1000
using namespace std;

class Obj
{
public:
	int v; // value
	int w; // weight
	double av; // value per weight
	double num; //number of objects being carried out 
	Obj();
	Obj(int v, int w, double n);
};

Obj::Obj()
{

}

Obj::Obj(int v, int w, double n)
{

	this->v = v;
	this->w = w;
	this->av = v / (double)w;
	this->num = n;
}


void sortItem(Obj objs[], int size)
{
	Obj tmpObj;
	for (int i = 0; i < size; i++)
	{
		double max = objs[i].av;
		int index = i;
		for (int j = i + 1; j < size; j++)
		{
			if (objs[j].av > max)
			{
				index = j;
				max = objs[j].av;
			}
		}
		if (index != i)
		{
			tmpObj = objs[i];
			objs[i] = objs[index];
			objs[index] = tmpObj;
		}
	}
}

int maxValue(Obj objs[], int n, int c)
{
	int sumValue = 0;
	for (int i = 0; i < n; i++)
	{
		if (c <= 0)
			break;
		Obj item = objs[i];
		if (item.w <= c)
		{
			sumValue += item.v;
			c -= item.w;
			objs[i].num = 1;
		}
		else
		{
			double k = c / item.w;
			sumValue += k * item.v;
			objs[i].num = k;
			break;
		}
	}
	return sumValue;
}

int main()
{
	int c = 0; // bag container
	int n = 0; // objects number
	Obj objs[MAX_SIZE];

	cout << "Please input the bag container:";
	cin >> c;
	cout << endl;
	cout << "Please input the objects number:";
	cin >> n;
	cout << endl;

	for (int i = 0; i < n; i++)
	{
		cout << "Please input value and weight of object " << i << " :\n";
		cin >> objs[i].v;
		cin >> objs[i].w;
		objs[i].av = (objs[i].v*1.0) / objs[i].w;
		objs[i].num = 0;
	}
	cout << "����֮ǰ, ÿ����Ʒ�ĵ�λ������ֵΪ��" << endl;
	for (int i = 0; i<n; i++)
	{
		cout << objs[i].av << " ";
	}

	sortItem(objs, n);

	cout << "\n����֮��, ÿ����Ʒ�ĵ�λ������ֵΪ��" << endl;
	for (int i = 0; i<n; i++)
	{
		cout << objs[i].av << " ";
	}

	cout << "\n��ʱ����ܻ�õļ�ֵ��: ";
	cout << maxValue(objs, n, c) << endl;

	cout << "����֮��ÿ����Ʒ����������Ϊ��";
	for (int i = 0; i < n; i++)
	{
		cout << objs[i].num << " ";
	}
	return 0;

}


