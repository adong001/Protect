#include"PCB.h"

float PCB::m_s_AverTurnaround = 0;//ƽ����תʱ��
float PCB::m_s_AverWeighted = 0;//ƽ����Ȩ��תʱ��

void PCB::InputPid()
{
	cout << "�����������";
	cin >> m_PidName;
	cout << "���̵���ʱ��:";
	cin >> m_Arrival;
	cout << "��������ʱ��:";
	cin >> m_Server;
	cout << endl;
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
	cout << "��������̸���:" << endl;
	cin >> num;
	PCB* Pid = new PCB[num];
	multimap<int, PCB*> m;
	for (int i = 0; i < num; i++)
	{
		Pid[i].InputPid();
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
	cout << "��������̸���:" << endl;
	cin >> num;
	PCB* Pid = new PCB[num];
	multimap<int, PCB*> ma;//ma--������ʱ������
	for (int i = 0; i < num; i++)
	{
		Pid[i].InputPid();
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
	cout << "-------------RR�㷨-------------\n\n\n";
	cout << "��������̸���:" << endl;
	cin >> num;
	cout << "����ʱ��Ƭ:";
	cin >> q;

	PCB* Pid = new PCB[num];
	multimap<int, PCB*> ma,ma2;

	for (int i = 0; i < num; i++)
	{
		Pid[i].InputPid();
		ma.insert(make_pair(Pid[i].m_Arrival, Pid + i));
	}
	queue<PCB*> qu;

	T = ma.begin()->second->m_Arrival;//ȡ��һ�������ڴ�Ľ���
	auto ipma = ma.begin();
	while (!ma.empty())//maΪ�գ���ת���
	{
		for (;ipma != ma.end(); ipma++)//�ҵ����е���Ľ���push������
		{
			if (T >= ipma->second->m_Arrival)
			{
				qu.push(ipma->second);
			}
		}
		auto ip = qu.front();
		if (ip)
		{
			if (ip->m_Server - q == 0)//�պü���
			{
				T += q;
				cout << "ʱ��" << T << ",����" << ip->m_PidName << "��ɣ��˳�" << endl;
				ip->m_Server -= q;//ע�⣺���㷨��ÿ�����е�һ������ʱ������ķ���ʱ���ȥһ��ʱ��Ƭ(�������0)
				ip->m_Finish = T;
				ip->m_Turnaround = ip->m_Finish - ip->m_Arrival;
				ip->m_Weighted = (float)ip->m_Turnaround / (float)ip->m_Server;
				PCB::m_s_AverTurnaround += ip->m_Turnaround;
				PCB::m_s_AverWeighted += ip->m_Weighted;
			}
			else if (ip->m_Server - q > 0)
			{
				T += q;
				ip->m_Arrival += q;//����ʱ��Ҳ���ű仯
				ip->m_Server -= q;
				ip++;
			}
			else//ʣ�����ʱ�䳬��ʱ��Ƭ
			{
				T += ip->m_Server;
				cout << "ʱ��" << T << ",����" << ip->m_PidName << "��ɣ��˳�" << endl;
				ip->m_Server = 0;
				ip->m_Finish = T;
				ip->m_Turnaround = ip->m_Finish - ip->m_Arrival;
				ip->m_Weighted = (float)ip->m_Turnaround / (float)ip->m_Server;
				PCB::m_s_AverTurnaround += ip->m_Turnaround;
				PCB::m_s_AverWeighted += ip->m_Weighted;
			}
			for (auto& e : ma)
			{
				if (e.second == qu.front())
				{
					ipma = qu
				}
			}
			qu.pop();
		}
	}
	PCB::m_s_AverTurnaround /= (float)num;
	PCB::m_s_AverWeighted /= (float)num;
	PCB::OutputPid(Pid, num);

}
