#include"PCB.h"

float PCB::m_s_AverTurnaround = 0;//ƽ����תʱ��
float PCB::m_s_AverWeighted = 0;//ƽ����Ȩ��תʱ��
int PCB::m_s_Num = 0;//��������
PCB *Pid;

void ReadData()//��������
{
	ifstream readData;
	readData.open("data.txt");

	readData >> PCB::m_s_Num;//�����������	
	Pid = new PCB[PCB::m_s_Num];//���ռ�

	for (int i = 0; i < PCB::m_s_Num; i++)//�����������
	{
		readData >> Pid[i].m_PidName;
	}

	for (int i = 0; i < PCB::m_s_Num; i++)//������̵���ʱ��
	{
		readData >> Pid[i].m_Arrival;
	}

	for (int i = 0; i < PCB::m_s_Num; i++)//�����������ʱ��
	{
		readData >> Pid[i].m_Server;
	}
	readData.close();
}


void PCB::OutputPid(PCB* P, int num)
{
	printf("\n%-5s %-5s %-5s %-5s %-5s %-5s %-5s %-5s\n\n", "������", "����ʱ��", "����ʱ��", "���ʱ��", "��תʱ��", "��Ȩ��תʱ��", "ƽ����תʱ��", "ƽ����Ȩ��תʱ��");
	for (int i = 0; i < num; i++)
	{
		cout << P[i].m_PidName << "\t  " << P[i].m_Arrival << "\t  " << P[i].m_Server << "\t    " << P[i].m_Finish << "\t    " << P[i].m_Turnaround << "\t    " << P[i].m_Weighted;
		if (i + 1 == num)
		{
			printf(" \t\t%3.2f\t  %3.2f\n\n", PCB::m_s_AverTurnaround, PCB::m_s_AverWeighted);
		}
		cout << endl;
	}
}


void FCFS()
{
	int num, T;
	cout << "-------------FCFS�㷨-------------\n\n\n";
	ReadData();

	num = PCB::m_s_Num;
	multimap<int, PCB*> m;
	for (int i = 0; i < num; i++)
	{
		m.insert(make_pair(Pid[i].m_Arrival, Pid + i));
	}
	T = Pid[0].m_Arrival;
	for (auto& ip = m.begin(); ip != m.end();)
	{
		PCB* tmp = ip->second;
		if (T >= tmp->m_Arrival)//��һ�����̽�������������Ѿ������ڴ�
		{
			tmp->m_Finish = T + tmp->m_Server;
			T += tmp->m_Server;
		}

		else//map��Ľ��̿��ˣ�ֱ��ִ����һ����TҪ���ϵȴ�ʱ��(m_Arrival - T)
		{
			tmp->m_Finish = T + tmp->m_Server + (tmp->m_Arrival - T);
			T += tmp->m_Server + (tmp->m_Arrival - T);
		}
		tmp->m_Turnaround = tmp->m_Finish - tmp->m_Arrival;
		tmp->m_Weighted = (float)tmp->m_Turnaround / (float)tmp->m_Server;
		PCB::m_s_AverTurnaround += tmp->m_Turnaround;
		PCB::m_s_AverWeighted += tmp->m_Weighted;
		cout << "ʱ��" << T << ",����" << tmp->m_PidName << "��ɣ��˳�" << endl;
		ip = m.erase(ip);
	}
	PCB::m_s_AverTurnaround /= (float)num;
	PCB::m_s_AverWeighted /= (float)num;
	PCB::OutputPid(Pid, num);
}



void SJF()
{
	int num, T;
	cout << "-------------SJF�㷨-------------\n\n\n";
	ReadData();

	num = PCB::m_s_Num;
	multimap<int, PCB*> ma;//ma--������ʱ������
	for (int i = 0; i < num; i++)
	{
		ma.insert(make_pair(Pid[i].m_Arrival, Pid + i));//���Ƚ���ʱ��
	}

	T = ma.begin()->second->m_Arrival;//��ʼʱ�����ȵ�����Ǹ����̵ĵ���ʱ��

	for (auto& ip = ma.begin(); !ma.empty();)//����������m2Ϊ��
	{
		PCB* tmp = ip->second;//��¼ip->second��ֵ�����ٴ��������,�����ip�ı䣬����ʹ��tmp
		if (T >= tmp->m_Arrival)//���̵���
		{
			auto ip1 = ip;
			int MinServer1 = ip->second->m_Server;
			ip++;
			while (ip != ma.end() && T >= ip->second->m_Arrival)//�ҵ��ѵ�������е���С����ʱ��
			{
				if (ip->second->m_Server < MinServer1)
				{
					MinServer1 = ip->second->m_Server;
					ip1 = ip;
				}
				else
				{
					ip++;
				}
			}
			ip = ip1;
			tmp = ip->second;//��¼ip->second��ֵ�����ٴ��������
			tmp->m_Finish = T + tmp->m_Server;
			T += tmp->m_Server;
		}
		else
			//���������A֮���������̻�δ����ȴ�����������������С����ʱ��
		{
			auto ip2 = ip;
			int MinServer2 = ip->second->m_Server;
			int t = ip->second->m_Arrival;
			ip++;
			while (ip != ma.end() && t == ip->second->m_Arrival)//�ҵ��ѵ�������е���С����ʱ��
			{
				if (ip->second->m_Server < MinServer2)
				{
					MinServer2 = ip->second->m_Server;
					ip2 = ip;
				}
				else
				{
					ip++;
				}
			}
			ip = ip2;
			tmp = ip->second;//��¼ip->second��ֵ�����ٴ��������
			tmp->m_Finish = T + tmp->m_Server + (tmp->m_Arrival - T);
			//���ʱ�������һ�����̵����ʱ��+Ҫ�ȴ���ʱ��(tm->m_Arrival-T)+��Ҫ���е�ʱ��
			T += tmp->m_Server + (tmp->m_Arrival - T);//ʱ��TҲҪ���ϵȴ�ʱ��
		}
		tmp->m_Turnaround = tmp->m_Finish - tmp->m_Arrival;
		tmp->m_Weighted = (float)tmp->m_Turnaround / (float)tmp->m_Server;
		PCB::m_s_AverTurnaround += tmp->m_Turnaround;
		PCB::m_s_AverWeighted += tmp->m_Weighted;
		cout << "ʱ��" << T << ",����" << tmp->m_PidName << "��ɣ��˳�" << endl;
		ip = ma.erase(ip);
		ip = ma.begin();//ÿ�δ�ma��ͷ��(�����ȵ���Ľ�������)
	}
	PCB::m_s_AverTurnaround /= (float)num;
	PCB::m_s_AverWeighted /= (float)num;
	PCB::OutputPid(Pid, num);
}

void RR()
{
	int q = 0;
	int num, T;
	queue<PCB*> qu;
	PCB* cur;
	typedef struct
	{
		int Arrival;
		int Server;
	}tmp;
	map<string, tmp*> ma;
	cout << "-------------RR�㷨-------------\n\n\n";
	ReadData();

	num = PCB::m_s_Num;
	tmp * t = new tmp[num];
	cout << "����ʱ��Ƭ:";
	cin >> q;

	for (int i = 0; i < num; i++)//��ʹ���н��̴��ڵȴ�״̬
	{
		t[i].Arrival = Pid[i].m_Arrival;
		t[i].Server = Pid[i].m_Server;
		ma.insert(make_pair(Pid[i].m_PidName,t + i));//�����е���ʱ�䱣�棬�ڽ�������ʱ���޸ģ����������¸���ȥ
		Pid[i].m_Status = WAITING;
	}
	T = Pid[0].m_Arrival;//ȡ��һ�������ڴ�Ľ���p
	qu.push(Pid);

	while (!qu.empty())//maΪ�գ���ת���
	{
		cur = qu.front();
		cur->m_Status = RUNNING;//�õ�ʱ��Ƭ״̬��־λ�ı�ΪRUNNING
		if (cur->m_Server - q == 0)//�պü���
		{
			T += q;
			cout << "ʱ��" << T << ",����" << cur->m_PidName << "��ɣ��˳�" << endl;
			cur->m_Finish = T;
			cur->m_Turnaround = cur->m_Finish - ma[cur->m_PidName]->Arrival;
			cur->m_Weighted = (float)(cur->m_Turnaround) / (float)(ma[cur->m_PidName]->Server);
			PCB::m_s_AverTurnaround += cur->m_Turnaround;
			PCB::m_s_AverWeighted += cur->m_Weighted;
			cur->m_Server = 0;//������Ժ���Ϊ0����ֹ�ٴε���
		}
		else if (cur->m_Server - q > 0)
		{
			T += q;
			cur->m_Arrival += q;//����ʱ��Ҳ���ű仯
			cur->m_Server -= q;
		}
		else//ʣ�����ʱ�䳬��ʱ��Ƭ
		{
			T += cur->m_Server;
			cout << "ʱ��" << T << ",����" << cur->m_PidName << "��ɣ��˳�" << endl;
			cur->m_Finish = T;
			cur->m_Turnaround = cur->m_Finish - ma[cur->m_PidName]->Arrival;
			cur->m_Weighted = (float)(cur->m_Turnaround) / (float)(ma[cur->m_PidName]->Server);
			cur->m_Server = 0;//������Ժ���Ϊ0����ֹ�ٴε���
			PCB::m_s_AverTurnaround += cur->m_Turnaround;
			PCB::m_s_AverWeighted += cur->m_Weighted;
		}
		qu.pop();//�������pop��

		for (int i = 0; i < num ; i++)
		//������һ����������ʱ���ں����������ʱ�������е���Ľ���push����
		{
			if (T >= Pid[i].m_Arrival && Pid[i].m_Status == WAITING)
			{
				qu.push(Pid + i);
				qu.back()->m_Status = BEREADY;//���䴦�ھ���������
			}
		}

		if (cur->m_Server != 0)//���������������ж��Ƿ������û�����ͼ����β
		{
			qu.push(cur);
			cur->m_Status = BEREADY;//���䴦�ھ���������
		}
	}
	for (int i = 0; i < num; i++)
	{
		Pid[i].m_Arrival = ma[Pid[i].m_PidName]->Arrival;//�������ֵ����ȥ
		Pid[i].m_Server = ma[Pid[i].m_PidName]->Server;
	}

	PCB::m_s_AverTurnaround /= (float)num;
	PCB::m_s_AverWeighted /= (float)num;
	PCB::OutputPid(Pid, num);
}
