#include"�ڴ�����㷨.h"

int Partition::PartitionNum = 0;
int PCB::PCBNum = 0;
Partition* partition;
PCB* pcb;



void ReadData()//��������
{
	ifstream readData;
	readData.open("data.txt");

	readData >> Partition::PartitionNum;//�����������
	partition = new Partition[Partition::PartitionNum];//���ռ�

	for (int i = 0; i < Partition::PartitionNum; i++)//���������
	{
		readData >> partition[i].m_PartitionId;
	}
	for (int i = 0; i < Partition::PartitionNum; i++)//���������С
	{
		readData >> partition[i].m_Capacity;
		partition[i].m_PartitionSize = partition[i].m_Capacity;
	}

	readData >> PCB::PCBNum;//�����������
	pcb = new PCB[PCB::PCBNum];

	for (int i = 0; i < PCB::PCBNum; i++)//�����������
	{
		readData >> pcb[i].m_PidName;
	}

	for (int i = 0; i < PCB::PCBNum; i++)//������̴�С
	{
		readData >> pcb[i].m_PidSize;
	}
}

void FirstFit()//�״���Ӧ�㷨
{
	bool flag = false;
	int i, j;
	ReadData();

	Display_PCB();
	cout << "���������" << endl;
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
			cout << "����" << pcb[i].m_PidName << "���䵽����" << partition[j].m_PartitionId << endl;
		}
		else
		{
			cout << "����" << pcb[i].m_PidName << "����ʧ�ܣ�" << endl;
		}
	}
	Display();
}

void NextFit()//ѭ���״���Ӧ�㷨
{
	int pos = 0;
	bool flag = false;
	int i, j;
	ReadData();

	Display_PCB();
	cout << endl << "���������" << endl;
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
			cout << "����" << pcb[i].m_PidName << "���䵽����" << partition[j].m_PartitionId << endl;
		}
		else
		{
			cout << "����" << pcb[i].m_PidName << "����ʧ�ܣ�" << endl;
		}
	}
	Display();

}
void BestFit()//�����Ӧ�㷨
{
	int pos = 0;
	bool flag = false;
	int i,j;
	multimap<int, Partition*> m;
	multimap<int, Partition*>::iterator ip;
	ReadData();

	Display_PCB();
	cout << endl << "���������" << endl;
	for (i = 0; i < PCB::PCBNum; i++)
	{
		m.clear();
		for (j = 0; j < Partition::PartitionNum; j++)//����С��������
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
			cout << "����" << pcb[i].m_PidName << "���䵽����" << ip->second->m_PartitionId << endl;
		}
		else
		{
			cout << "����" << pcb[i].m_PidName << "����ʧ�ܣ�" << endl;
		}
	}
	Display();
}
void WorstFit()//���Ӧ�㷨
{
	int pos = 0;
	bool flag = false;
	int i,j;
	multimap<int, Partition*,greater<int>> m;
	multimap<int, Partition*>::iterator ip = m.begin();
	ReadData();
	Display_PCB();
	cout << endl << "���������" << endl;
	for (i = 0; i < PCB::PCBNum; i++)
	{
		m.clear();
		for (j = 0; j < Partition::PartitionNum; j++)//���Ӵ�С����
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
			cout << "����" << pcb[i].m_PidName << "���䵽����" << ip->second->m_PartitionId << endl;
		}
		else
		{
			cout << "����" << pcb[i].m_PidName << "����ʧ�ܣ�" << endl;
		}
	}
	Display();
}
void Display()
{
	cout << endl << "����id:  ";
	for (int i = 0; i < Partition::PartitionNum; i++)
	{
		printf("%3d  ", partition[i].m_PartitionId);

	}

	cout << endl << "������С:";
	for (int i = 0; i < Partition::PartitionNum; i++)
	{
		printf("%3d  ", partition[i].m_Capacity);
	}

	cout << endl << "ʣ���С:";
	for (int i = 0; i < Partition::PartitionNum; i++)
	{
		printf("%3d  ", partition[i].m_PartitionSize);

	}
	cout << endl << endl;

}


void Display_PCB()
{
	cout << endl << "����id:  ";
	for (int i = 0; i < PCB::PCBNum; i++)
	{
		printf("%3s  ", pcb[i].m_PidName.c_str());
	}
	cout << endl << "���̴�С:";
	for (int i = 0; i < PCB::PCBNum; i++)
	{
		printf("%3d  ",pcb[i].m_PidSize);
	}
	cout << endl<<endl;
}