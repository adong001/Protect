#include"内存分配算法.h"

int Partition::PartitionNum = 0;
int PCB::PCBNum = 0;
Partition* partition;
PCB* pcb;
int MIN;


void ReadData()//读入数据
{
	ifstream readData;
	readData.open("data.txt");

	readData >> Partition::PartitionNum;//读入分区数量
	partition = new Partition[Partition::PartitionNum];//开空间

	for (int i = 0; i < Partition::PartitionNum; i++)//读入分区起始地址
	{
		readData >> partition[i].m_PartitionId;
		partition[i].m_BlockId = partition[i].m_PartitionId;
	}
	for (int i = 0; i < Partition::PartitionNum; i++)//读入分区大小
	{
		readData >> partition[i].m_PartitionSize;
	}

	//readData >> PCB::PCBNum;//读入进程数量
	//pcb = new PCB[PCB::PCBNum];

	//for (int i = 0; i < PCB::PCBNum; i++)//读入进程名称
	//{
	//	readData >> pcb[i].m_PidName;
	//}

	//for (int i = 0; i < PCB::PCBNum; i++)//读入进程大小
	//{
	//	readData >> pcb[i].m_PidSize;
	//}
	//readData.close();
}

void FirstFit()//首次适应算法
{
	bool flag = false;
	int i, j;
	string choose;
	ReadData();
	//cout << "输入MIN:";
	//cin >> MIN;
	//Display_PCB();
	do
	{
		Display_Partition();
		pcb = (PCB*)realloc(pcb, sizeof(PCB)*(PCB::PCBNum + 1));
		cout << "输入进程名称：";
		cin >> pcb[PCB::PCBNum - 1].m_PidName;
		cout << "输入进程大小:";
		cin >> pcb[PCB::PCBNum - 1].m_PidSize;

		i = PCB::PCBNum - 1;

		for (j = 0; j < Partition::PartitionNum; j++)
		{
			if (pcb[i].m_PidSize <= partition[j].m_PartitionSize)
			{
				partition[j].m_PartitionSize -= pcb[i].m_PidSize;
				partition[j].m_BlockId += partition[j].m_PartitionSize;
				if (partition[j].m_PartitionSize <= MIN)
				{
					partition[j].m_PartitionSize = 0;
				}
				flag = true;
				break;
			}
		}
		if (flag)
		{
			flag = false;
			cout << "进程" << pcb[i].m_PidName << "分配到分区" << partition[j].m_PartitionId << endl;
		}
		else
		{
			cout << "进程" << pcb[i].m_PidName << "分配失败！" << endl;
		}
		Display1();
		cout << "继续分配按Y" << endl;
		cin >> choose;

	} while (choose == "Y");
}
void NextFit()//循环首次适应算法
{
	int pos = 0;
	bool flag = false;
	int i, j;
	string choose;
	ReadData();
	//Display_PCB();
	/*cout << "输入MIN:";
	cin >> MIN;*/
	do
	{

		Display_Partition();
		pcb = (PCB*)realloc(pcb, sizeof(PCB)*(PCB::PCBNum+1));
		cout << "输入进程名称：";
		cin >> pcb[PCB::PCBNum - 1].m_PidName;
		cout << "输入进程大小:";
		cin >> pcb[PCB::PCBNum - 1].m_PidSize;
		i = PCB::PCBNum - 1;

		for (j = pos;; j++)
		{
			if (pos >= PCB::PCBNum)
			{
				pos = 0;
			}
			if (pcb[i].m_PidSize <= partition[j].m_PartitionSize)
			{
				partition[j].m_PartitionSize -= pcb[i].m_PidSize;
				partition[j].m_BlockId += partition[j].m_PartitionSize;
				if (partition[j].m_PartitionSize <= MIN)
				{
					partition[j].m_PartitionSize = 0;
				}
				flag = true;
				pos = j + 1;
				if (pos == PCB::PCBNum)
				{
					pos = 0;
				}
				break;
			}
		}
		if (flag)
		{
			flag = false;
			cout << "进程" << pcb[i].m_PidName << "分配到分区" << partition[j].m_PartitionId << endl;
		}
		else
		{
			cout << "进程" << pcb[i].m_PidName << "分配失败！" << endl;
		}
		Display1();
		cout << "继续分配按Y" << endl;
		cin >> choose;

	} while (choose == "Y");

}
void BestFit()//最佳适应算法
{
	int pos = 0;
	bool flag = false;
	int i, j;
	multimap<int, Partition*> m;
	multimap<int, Partition*>::iterator ip;
	string choose;
	ReadData();
	//Display_PCB();
	/*cout << "输入MIN:";
	cin >> MIN;*/
	do
	{
		Display_Partition();
		pcb = (PCB*)realloc(pcb, sizeof(PCB)*(PCB::PCBNum + 1));
		cout << "输入进程名称：";
		cin >> pcb[PCB::PCBNum - 1].m_PidName;
		cout << "输入进程大小:";
		cin >> pcb[PCB::PCBNum - 1].m_PidSize;
		i = PCB::PCBNum - 1;

		m.clear();
		for (j = 0; j < Partition::PartitionNum; j++)//按从小带大排序
		{
			m.insert(make_pair(partition[j].m_PartitionSize, partition + j));
		}

		for (ip = m.begin(); ip != m.end();)
		{
			if (pcb[i].m_PidSize <= ip->first)
			{
				ip->second->m_PartitionSize -= pcb[i].m_PidSize;
				ip->second->m_BlockId += ip->second->m_PartitionSize;
				/*if (ip->second->m_PartitionSize <= MIN)
				{
				ip->second->m_PartitionSize = 0;
				}*/
				flag = true;
				break;
			}
			else
			{
				ip++;
			}
		}
		if (flag)
		{
			flag = false;
			cout << "进程" << pcb[i].m_PidName << "分配到分区" << ip->second->m_PartitionId << endl;
		}
		else
		{
			cout << "进程" << pcb[i].m_PidName << "分配失败！" << endl;
		}
		Display();
		cout << "继续分配按Y" << endl;
		cin >> choose;

	} while (choose == "Y");
}
void WorstFit()//最坏适应算法
{
	int pos = 0;
	bool flag = false;
	int i, j;
	multimap<int, Partition*, greater<int>> m;
	multimap<int, Partition*>::iterator ip = m.begin();
	string choose;
	ReadData();
	//Display_PCB();
	/*cout << "输入MIN:";
	cin >> MIN;*/
	do
	{
		Display_Partition();
		pcb = (PCB*)realloc(pcb, sizeof(PCB)*(PCB::PCBNum + 1));
		cout << "输入进程名称：";
		cin >> pcb[PCB::PCBNum - 1].m_PidName;
		cout << "输入进程大小:";
		cin >> pcb[PCB::PCBNum - 1].m_PidSize;
		i = PCB::PCBNum - 1;

		m.clear();
		for (j = 0; j < Partition::PartitionNum; j++)//按从大到小排序
		{
			m.insert(make_pair(partition[j].m_PartitionSize, partition + j));
		}

		for (ip = m.begin(); ip != m.end();)
		{
			if (pcb[i].m_PidSize <= ip->first)
			{
				ip->second->m_PartitionSize -= pcb[i].m_PidSize;
				ip->second->m_BlockId += ip->second->m_PartitionSize;
				/*if (ip->second->m_PartitionSize <= MIN)
				{
				ip->second->m_PartitionSize = 0;
				}*/
				flag = true;
				break;
			}
			else
			{
				ip++;
			}
		}
		if (flag)
		{
			flag = false;
			cout << "进程" << pcb[i].m_PidName << "分配到分区" << ip->second->m_PartitionId << endl;
		}
		else
		{
			cout << "进程" << pcb[i].m_PidName << "分配失败！" << endl;
		}
		Display();
		cout << "继续分配按Y" << endl;
		cin >> choose;

	} while (choose == "Y");
}
void Display()
{
	int i;
	set<int> s;
	for (i = 0; i < Partition::PartitionNum; i++)
	{
		s.insert(partition[i].m_PartitionSize);
	}

	cout << "空白分区链:";
	for (auto& e : s)
	{
		cout << e << "->";
	}
	cout << "NULL";
	cout << endl;
}

void Display1()
{
	int i;
	map<int, Partition*> m;
	for (i = 0; i < Partition::PartitionNum; i++)
	{
		m.insert(make_pair(partition[i].m_PartitionId, partition + i));
	}

	cout << "空白分区链:";
	for (auto& e : m)
	{
		if (e.second->m_PartitionSize != 0)
		{
			cout << e.second->m_PartitionSize << "->";
		}
	}
	cout << "NULL";
	cout << endl;
}
void Display_Partition()
{
	cout << endl << "分区起始地址 ";
	for (int i = 0; i < Partition::PartitionNum; i++)
	{
		printf("%-d  ", partition[i].m_PartitionId);
	}
	cout << endl << "分区大小:   ";
	for (int i = 0; i < Partition::PartitionNum; i++)
	{

		printf("%-d  ", partition[i].m_PartitionSize);

	}
	cout << endl << endl;
}

void Display_PCB()
{
	cout << endl << "进程id:  ";
	for (int i = 0; i < PCB::PCBNum; i++)
	{
		printf("%3s  ", pcb[i].m_PidName.c_str());
	}
	cout << endl << "进程大小:";
	for (int i = 0; i < PCB::PCBNum; i++)
	{
		printf("%3d  ", pcb[i].m_PidSize);
	}
	cout << endl << endl;
}