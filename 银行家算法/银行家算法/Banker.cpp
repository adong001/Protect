#include"Banker.h"

void Init()
{
	int PcbNum, Source;
	int i, j, tmp;
	cout << "输入进程的个数：";
	cin >> PcbNum;
	cout << "输入资源的种类：";
	cin >> Source;

	cout << "输入系统剩余资源:";
	for (i = 0; i < Source; i++)
	{
		cin >> tmp;
		Available.push_back(tmp);
	}
	cout << endl<< endl;

	cout << "输入Allocation矩阵" << endl;

	for (i = 0; i < PcbNum; i++)
	{
		Allocation.push_back(vector<int>());
		Max.push_back(vector<int>());

		for (j = 0; j < Source; j++)
		{
			cin >> tmp;
			Allocation[i].push_back(tmp);
			Max[i].push_back(tmp);
		}
	}
	cout << endl << endl;

	cout << "输入Need矩阵" << endl;

	for (i = 0; i < PcbNum; i++)
	{
		Need.push_back(vector<int>());
		
		for (j = 0; j < Source; j++)
		{
			cin >> tmp;
			Need[i].push_back(tmp);
			Max[i][j] += tmp;
		}
	}
	cout << "输入完毕!\n";


}
//
//void Display()
//{
//	char Name[10] = "ABCDEFGH";
//	cout << "资源分配情况：" << endl;
//	printf("|  \\资源|   %15Max|  %15Allocation| %15Need | %15Available|\n");
//	cout << "|进程\\情况|";
//	for (int j = 0; j < 4; j++)
//	{
//		for (int i = 0; i < Available.size(); i++)
//		{
//			printf("%3d",Name[i]);
//		}
//		cout << "|";
//	}
//
//}
Status Requset()//进程请求资源
{
	return SECURITY;
}

Status AlgoBanker()//银行家算法,传入进程Id和请求分配大小
{
	return SECURITY;
}

Status Security()//安全性算法
{
	return SECURITY;
}