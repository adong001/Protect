#include"内存分配算法.h"

int Partition::PartitionNum = 0;
int PCB::PCBNum = 0;
Partition* partition;
PCB* pcb;



void ReadData()//读入数据
{
	ifstream readData;
	readData.open("data.txt");

	readData >> Partition::PartitionNum;//读入分区数量
	partition = new Partition[Partition::PartitionNum];//开空间

	for (int i = 0; i < Partition::PartitionNum; i++)//读入分区号
	{
		readData >> partition[i].m_PartitionId;
	}
	for (int i = 0; i < Partition::PartitionNum; i++)//读入分区大小
	{
		readData >> partition[i].m_Capacity;
		partition[i].m_PartitionSize = partition[i].m_Capacity;
	}

	readData >> PCB::PCBNum;//读入进程数量
	pcb = new PCB[PCB::PCBNum];

	for (int i = 0; i < PCB::PCBNum; i++)//读入进程名称
	{
		readData >> pcb[i].m_PidName;
	}

	for (int i = 0; i < PCB::PCBNum; i++)//读入进程大小
	{
		readData >> pcb[i].m_PidSize;
	}
}

void FirstFit()//首次适应算法
{
	bool flag = false;
	int i, j;
	ReadData();

	Display_PCB();
	cout << "分配情况：" << endl;
	for (i = 0; i < PCB::PCBNum; i++)
	{
		for (j = 0; j < Partition::PartitionNum; j++)
		{
			if (pcb[i].m_PidSize <= partition[j].m_PartitionSize)
			{
				partition[j].m_PartitionSize -= pcb[i].m_PidSize;
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
			cout << "进程" << pcb[i].m_PidName << "分配到分区" << partition[j].m_PartitionId << endl;
		}
		else
		{
			cout << "进程" << pcb[i].m_PidName << "分配失败！" << endl;
		}
	}
	Display();
}

void NextFit()//循环首次适应算法
{
	int pos = 0;
	bool flag = false;
	int i, j;
	ReadData();

	Display_PCB();
	cout << endl << "分配情况：" << endl;
	for (i = 0; i < PCB::PCBNum; i++)
	{
		for (j = pos; j < Partition::PartitionNum; j++)
		{
			if (pcb[i].m_PidSize <= partition[j].m_PartitionSize)
			{
				partition[j].m_PartitionSize -= pcb[i].m_PidSize;
				if (partition[j].m_PartitionSize <= MIN)
				{
					partition[j].m_PartitionSize = 0;
				}
				flag = true;
				pos = j + 1;
				if (pos == Partition::PartitionNum)
				{
					pos = 0;
				}
				break;
			}
		}
		if (flag)
		{
			cout << "进程" << pcb[i].m_PidName << "分配到分区" << partition[j].m_PartitionId << endl;
		}
		else
		{
			cout << "进程" << pcb[i].m_PidName << "分配失败！" << endl;
		}
	}
	Display();

}
void BestFit()//最佳适应算法
{
	int pos = 0;
	bool flag = false;
	int i,j;
	multimap<int, Partition*> m;
	multimap<int, Partition*>::iterator ip;
	ReadData();

	Display_PCB();
	cout << endl << "分配情况：" << endl;
	for (i = 0; i < PCB::PCBNum; i++)
	{
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
				if (ip->second->m_PartitionSize <= MIN)
				{
					ip->second->m_PartitionSize = 0;
				}
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
			cout << "进程" << pcb[i].m_PidName << "分配到分区" << ip->second->m_PartitionId << endl;
		}
		else
		{
			cout << "进程" << pcb[i].m_PidName << "分配失败！" << endl;
		}
	}
	Display();
}
void WorstFit()//最坏适应算法
{
	int pos = 0;
	bool flag = false;
	int i,j;
	multimap<int, Partition*,greater<int>> m;
	multimap<int, Partition*>::iterator ip = m.begin();
	ReadData();
	Display_PCB();
	cout << endl << "分配情况：" << endl;
	for (i = 0; i < PCB::PCBNum; i++)
	{
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
				if (ip->second->m_PartitionSize <= MIN)
				{
					ip->second->m_PartitionSize = 0;
				}
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
			cout << "进程" << pcb[i].m_PidName << "分配到分区" << ip->second->m_PartitionId << endl;
		}
		else
		{
			cout << "进程" << pcb[i].m_PidName << "分配失败！" << endl;
		}
	}
	Display();
}
void Display()
{
	cout << endl << "分区id:  ";
	for (int i = 0; i < Partition::PartitionNum; i++)
	{
		printf("%3d  ", partition[i].m_PartitionId);

	}

	cout << endl << "分区大小:";
	for (int i = 0; i < Partition::PartitionNum; i++)
	{
		printf("%3d  ", partition[i].m_Capacity);
	}

	cout << endl << "剩余大小:";
	for (int i = 0; i < Partition::PartitionNum; i++)
	{
		printf("%3d  ", partition[i].m_PartitionSize);

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
		printf("%3d  ",pcb[i].m_PidSize);
	}
	cout << endl<<endl;
}