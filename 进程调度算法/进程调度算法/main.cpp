#define _CRT_SECURE_NO_WARNINGS 1
#include"PCB.h"
#include<iostream>
using namespace std;

//class Compare{
//public:
//	bool operator ()(int a, int b)
//	{
//		return 1<2;
//	}
//};

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
	//map<int, string> m;
	//m.insert(make_pair(3, "C"));
	//m.insert(make_pair(1, "A"));
	//m.insert(make_pair(2, "B"));
	//map<int, string, Compare> mm;
	//mm.insert(make_pair(3, "C"));
	//mm.insert(make_pair(1, "A"));
	//mm.insert(make_pair(2, "B"));
	//for (auto&e : mm)
	//{
	//	cout << e.first << " " << e.second << endl;
	//}
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