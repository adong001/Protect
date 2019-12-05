//
//#include <iostream>
//#include <fstream>
//#include <iomanip>
//using namespace std;
//
//#define MAXNUMBER 100
//static int PartitionNum;  //�ڴ��п��з����ĸ���
//static int ProcessNum; //��Ҫ����Ľ��̸���
//static int FreePartition[MAXNUMBER];  //���з�����Ӧ���ڴ�
//static int ProcessNeed[MAXNUMBER];  //��Ҫ����Ľ��̴�С
//
//static int LeftFreePartition[MAXNUMBER];
//static int LeftProcessNeed[MAXNUMBER];
//
//static char ProcessName[MAXNUMBER];
//static char NameProcessToPartition[MAXNUMBER][MAXNUMBER];
//
//typedef struct
//{
//	int partitionSize;
//	int id;
//}sortNeed;
//
//void readDataFunction();
//void display();
//void FirstFit();
//void NextFit();
//void BestFit();
//void WorstFit();
//void selectAlgorithm(int chooceAlgorithm);
//void display();
//
//void readDataFunction()
//{
//	ifstream readData;
//	readData.open("data.txt");
//
//	readData >> PartitionNum;
//	for (int i = 0; i<PartitionNum; i++)
//	{
//		readData >> FreePartition[i];
//	}
//
//	readData >> ProcessNum;
//	for (int i = 0; i<ProcessNum; i++)
//	{
//		readData >> ProcessName[i];
//	}
//	for (int i = 0; i<ProcessNum; i++)
//	{
//		readData >> ProcessNeed[i];
//	}
//}
//
//void initial()
//{
//	readDataFunction();   //��ȡԭʼ����
//	for (int i = 0; i<ProcessNum; i++)
//	{
//		for (int j = 0; j<PartitionNum; j++)
//		{
//			NameProcessToPartition[i][j] = NULL;
//			LeftFreePartition[j] = FreePartition[j];
//		}
//	}
//	for (int i = 0; i<ProcessNum; i++)
//	{
//		LeftProcessNeed[i] = ProcessNeed[i];
//	}
//}
//
//
//void FirstFit()
//{
//	cout << "***********�״���Ӧ�㷨***********" << endl;
//	initial();
//
//	int i, j;
//	for (i = 0; i<ProcessNum; i++)   //�������ÿ������
//	{
//		for (j = 0; j<PartitionNum; j++)   //ÿ�ζ��ӷ������׵�ַ��ʼ����
//		{
//			if (LeftProcessNeed[i] <= LeftFreePartition[j] && LeftFreePartition != 0)  //��ϵͳ�ڴ�����㹻���ʱ�򣬼������������Դ
//			{
//				LeftFreePartition[j] -= LeftProcessNeed[i];   //�۳���������̵���Դ
//				LeftProcessNeed[i] = 0;  //���ҽ���ϵͳ�ڴ�����㹻ʱ��ִ�У�����ǰ���̴�С��0
//
//				NameProcessToPartition[i][j] = ProcessName[i];  //�洢�����������ڵķ���λ��
//
//				break;   //!!!����Ҫ��һ�����̷������Ӧ������break��������һ�����̵��ж�
//			}
//		}
//	}
//
//	display();
//
//}
//
//void NextFit()
//{
//	cout << "***********ѭ���״���Ӧ�㷨***********" << endl;
//	initial();
//	int i, nextPoint = 0;
//	bool isWhile;
//	for (i = 0; i<ProcessNum; i++)
//	{
//		isWhile = true;
//		while (isWhile)     //ÿ�ζ��ӵ�ǰ��������һ��������ʼ����
//		{
//			if (LeftFreePartition[nextPoint] >= LeftProcessNeed[i])
//			{
//				LeftFreePartition[nextPoint] -= LeftProcessNeed[i];
//				LeftProcessNeed[i] = 0;
//				NameProcessToPartition[i][nextPoint] = ProcessName[i];
//				nextPoint++;
//				if (nextPoint > PartitionNum - 1)
//				{
//					nextPoint = 0;  //��j����������ĩβ��ʱ�򣬷�����λ��
//				}
//				isWhile = false;
//			}
//			else
//				nextPoint++;
//		}
//	}
//	display();
//}
//
//void BestFit()
//{
//	//˼�룺����ð������Է�����С�������򣬵����ı�ԭ������λ��
//	//����һ���ṹ�壬����������С������Ӧ��id����������У�ÿ�ı�˳��һ�Σ�id���Ÿı�
//	//�ؼ���ÿ�η�����һ�����̵��ڴ��С�󣬶�Ҫ��������
//	cout << "***********�����Ӧ�㷨***********" << endl;
//	initial();
//	int i, j, temp, tempID;
//
//	sortNeed best[MAXNUMBER];
//	for (i = 0; i<PartitionNum; i++)
//	{
//		//��ʼ���ṹ��
//		best[i].partitionSize = FreePartition[i];
//		best[i].id = i;
//	}
//
//	//int count2 = 0;
//
//	for (i = 0; i<ProcessNum; i++)
//	{
//		for (int s = PartitionNum - 1; s > 0; s--)   //ð������(ÿ�η�����һ�����̺󣬶���Ҫ��������)
//		{
//			for (int t = 0; t < s; t++)
//			{
//				if (best[s].partitionSize < best[t].partitionSize)
//				{
//					temp = best[s].partitionSize;
//					best[s].partitionSize = best[t].partitionSize;
//					best[t].partitionSize = temp;
//
//					tempID = best[s].id;
//					best[s].id = best[t].id;
//					best[t].id = tempID;
//				}
//			}
//		}
//
//		for (j = 0; j<PartitionNum; j++)
//		{
//			if (LeftProcessNeed[i] <= best[j].partitionSize)
//			{
//				best[j].partitionSize -= LeftProcessNeed[i];
//				LeftProcessNeed[i] = 0;
//
//				NameProcessToPartition[i][best[j].id] = ProcessName[i];
//				//count2++;
//				break;
//			}
//		}
//		LeftFreePartition[best[j].id] = best[j].partitionSize;
//	}
//	//cout<<count2<<endl;
//
//	display();
//}
//
//void WorstFit()
//{
//	cout << "***********���Ӧ�㷨***********" << endl;
//	initial();
//	int i, j, s, t, tempSize, tempID;
//	sortNeed Worst[MAXNUMBER];
//
//	for (i = 0; i<PartitionNum; i++)
//	{
//		Worst[i].partitionSize = FreePartition[i];
//		Worst[i].id = i;
//	}
//
//	for (i = 0; i<ProcessNum; i++)
//	{
//		for (s = PartitionNum - 1; s>0; s--)
//		{
//			for (t = 0; t<s; t++)
//			{
//				if (Worst[s].partitionSize > Worst[t].partitionSize)
//				{
//					tempSize = Worst[s].partitionSize;
//					Worst[s].partitionSize = Worst[t].partitionSize;
//					Worst[t].partitionSize = tempSize;
//
//					tempID = Worst[s].id;
//					Worst[s].id = Worst[t].id;
//					Worst[t].id = tempID;
//				}
//			}
//		}
//
//		for (j = 0; j<PartitionNum; j++)
//		{
//			if (LeftProcessNeed[i] <= Worst[j].partitionSize)
//			{
//				Worst[j].partitionSize -= LeftProcessNeed[i];
//				LeftProcessNeed[j] = 0;
//
//				NameProcessToPartition[i][Worst[j].id] = ProcessName[i];
//				break;
//			}
//		}
//		LeftFreePartition[Worst[j].id] = Worst[j].partitionSize;
//	}
//
//	display();
//
//}
//
//void selectAlgorithm(int chooseAlgorithm)
//{
//	switch (chooseAlgorithm)
//	{
//	case 0:break;
//	case 1:FirstFit(); break;
//	case 2:NextFit(); break;
//	case 3:BestFit(); break;
//	case 4:WorstFit(); break;
//	default:cout << "��������ȷ����ţ�" << endl;
//	}
//}
//
//void display()
//{
//	int i;
//	cout << "��Ҫ�����ڴ�Ľ�������" << setw(10);
//	for (i = 0; i<ProcessNum; i++)
//	{
//		cout << ProcessName[i] << setw(6);
//	}
//	cout << endl;
//	cout << "��Ҫ�����ڴ�Ľ��̷�����С��" << setw(4);
//	for (i = 0; i<ProcessNum; i++)
//	{
//		cout << ProcessNeed[i] << setw(6);
//	}
//	cout << endl;
//	cout << "��������" << endl;
//
//	cout << "�������:";
//	for (i = 0; i<PartitionNum; i++)
//	{
//		cout << "����" << i + 1 << " ";
//	}
//	cout << endl << "������С:";
//	for (i = 0; i<PartitionNum; i++)
//	{
//		cout << FreePartition[i] << "     ";
//	}
//	cout << endl << "ʣ���С:";
//	for (i = 0; i<PartitionNum; i++)
//	{
//		cout << LeftFreePartition[i] << "     ";
//	}
//	cout << endl << "����������:" << endl;
//	for (i = 0; i<PartitionNum; i++)
//	{
//		for (int j = 0; j<ProcessNum; j++)
//		{
//			if (NameProcessToPartition[j][i] != NULL)
//			{
//				cout << NameProcessToPartition[j][i] << ": (����" << i + 1 << ")" << endl;
//			}
//		}
//	}
//	cout << endl << "********����**********" << endl;
//}
//
//int main()
//{
//	int chooseAlgorithm = 5;
//	while (chooseAlgorithm)
//	{
//		cout << "��ѡ��ʵ�ֵ��㷨��" << endl;
//		cout << "*****  1 - �״���Ӧ�㷨     *****" << endl;
//		cout << "*****  2 - ѭ���״���Ӧ�㷨 *****" << endl;
//		cout << "*****  3 - �����Ӧ�㷨     *****" << endl;
//		cout << "*****  4 - ���Ӧ�㷨     *****" << endl;
//		cout << "*****  0 - ����             *****" << endl;
//
//		cout << "chooseAlgorithm = ";
//		cin >> chooseAlgorithm;
//		selectAlgorithm(chooseAlgorithm);
//	}
//	system("pause");
//	return 0;
//}
//
