#define _CRT_SECURE_NO_WARNINGS 1
#include"PCB.h"
#include<iostream>
using namespace std;

int main()
{

	/*int ar[] = { 1, 2, 3, 4, 5 };
	list<int> l;
	for (auto&e : ar)
	{
		l.push_back(e);
	}
	auto ip = l.begin();
	ip++;
	ip++;
	ip++;
	ip++;
	ip++;
	cout << *ip << endl;*/

	int chose;
	while (1)
	{
		cout << "-------进程调度算法-------" << endl << endl << endl;
		cout << "------1.FCFS" << endl;
		cout << "------2.SJF" << endl;
		cout << "------3.RR" << endl;
		cin >> chose;
		switch (chose)
		{
		case 1:FCFS();
			break;
		case 2:SJF();
			break;
		case 3:RR();
			break;
		default:
			cout << "输入错误！！!" << endl;
		}
	}

	system("pause");
	return 0;
}