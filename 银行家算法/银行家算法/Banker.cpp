#include"Banker.h"

void Init()
{
	int PcbNum, Source;
	int i, j, tmp;
	cout << "������̵ĸ�����";
	cin >> PcbNum;
	cout << "������Դ�����ࣺ";
	cin >> Source;

	cout << "����ϵͳʣ����Դ:";
	for (i = 0; i < Source; i++)
	{
		cin >> tmp;
		Available.push_back(tmp);
	}
	cout << endl<< endl;

	cout << "����Allocation����" << endl;

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

	cout << "����Need����" << endl;

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
	cout << "�������!\n";


}
//
//void Display()
//{
//	char Name[10] = "ABCDEFGH";
//	cout << "��Դ���������" << endl;
//	printf("|  \\��Դ|   %15Max|  %15Allocation| %15Need | %15Available|\n");
//	cout << "|����\\���|";
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
Status Requset()//����������Դ
{
	return SECURITY;
}

Status AlgoBanker()//���м��㷨,�������Id����������С
{
	return SECURITY;
}

Status Security()//��ȫ���㷨
{
	return SECURITY;
}