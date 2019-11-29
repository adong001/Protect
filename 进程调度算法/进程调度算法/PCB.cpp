#include"PCB.h"

void PCB::InputPid()
{

	cout << "请输入进程名";
	cin >> m_PidName;
	cout << "进程到达时间:";
	cin >> m_Arrival;
	cout << "进程运行时间:";
	cin >> m_Server;
	cout << endl;
}


void PCB::OutputPid(PCB* P, int num)
{
	printf("\n%-5s %-5s %-5s %-5s %-5s %-5s %-5s %-5s\n\n", "进程名", "到达时间", "运行时间", "完成时间", "周转时间", "带权周转时间", "平均周转时间", "平均带权周转时间");
	for (int i = 0; i < num; i++)
	{
		cout << P[i].m_PidName << "\t  " << P[i].m_Arrival << "\t  " << P[i].m_Server << "\t    " << P[i].m_Finish << "\t    " << P[i].m_Turnaround << "\t    " << P[i].m_Weighted;
		if (i + 1 == num)
		{
			printf(" \t\t%3.2f\t  %3.2f\n\n", g_s_AverTurnaround, g_s_AverWeighted);
		}
		cout << endl;
	}
}


void FCFS()
{
	int num, T;
	cout << "-------------FCFS算法-------------\n\n\n";
	cout << "请输入进程个数:" << endl;
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
		tmp->m_Finish = T + tmp->m_Server;
		tmp->m_Turnaround = tmp->m_Finish - tmp->m_Arrival;
		tmp->m_Weighted = (float)tmp->m_Turnaround / (float)tmp->m_Server;
		g_s_AverTurnaround += tmp->m_Turnaround;
		g_s_AverWeighted += tmp->m_Weighted;
		T += tmp->m_Server;
		cout << "时刻" << T << ",进程" << tmp->m_PidName << "完成，退出" << endl;
		ip = m.erase(ip);
	}
	g_s_AverTurnaround /= (float)num;
	g_s_AverWeighted /= (float)num;
	PCB::OutputPid(Pid, num);
}



void SJF()
{
	int num, T;
	cout << "-------------SJF算法-------------\n\n\n";
	cout << "请输入进程个数:" << endl;
	cin >> num;
	PCB* Pid = new PCB[num];
	multimap<int, PCB*> m, m2;
	for (int i = 0; i < num; i++)
	{
		Pid[i].InputPid();
		m.insert(make_pair(Pid[i].m_Server, Pid + i));//最短服务时间

		m2.insert(make_pair(Pid[i].m_Arrival, Pid + i));//最短进入时间
	}
	auto& ip2 = m2.begin();
	T = ip2->second->m_Arrival;
	for (auto& ip = m.begin(); ip != m.end() || !m.empty();)
	{
		if (ip == m.end())
		{
			ip = m.begin();
		}
		PCB* tmp = ip->second;
		int count = 0;
		auto& itmp = m.end();
		for (auto& e : m)
		{
			count++;
		}

		/*if (T >= tmp->m_Arrival)
		{*/
		if (tmp->m_Arrival > T)

		{
			tmp->m_Finish = T + tmp->m_Server + (tmp->m_Arrival - T);
			T += tmp->m_Server + (tmp->m_Arrival - T);
		}	
		else
		{
			tmp->m_Finish = T + tmp->m_Server ;
			T += tmp->m_Server;
		}
		tmp->m_Turnaround = tmp->m_Finish - tmp->m_Arrival;
			tmp->m_Weighted = (float)tmp->m_Turnaround / (float)tmp->m_Server;
			g_s_AverTurnaround += tmp->m_Turnaround;
			g_s_AverWeighted += tmp->m_Weighted;
			
			cout << "时刻" << T << ",进程" << tmp->m_PidName << "完成，退出" << endl;
			ip = m.erase(ip);
			ip = m.begin();
		/*}*/
		/*else if()
		{

		}*/
	}
	g_s_AverTurnaround /= (float)num;
	g_s_AverWeighted /= (float)num;
	PCB::OutputPid(Pid, num);
}

void RR()
{
	int q = 0;
	int num, T;
	cout << "-------------RR算法-------------\n\n\n";
	cout << "请输入进程个数:" << endl;
	cin >> num;
	cout << "设置时间片:";
	cin >> q;

	PCB* Pid = new PCB[num];
	multimap<int, PCB*> m, m2;

	for (int i = 0; i < num; i++)
	{
		Pid[i].InputPid();
		m.insert(make_pair(Pid[i].m_Arrival, Pid + i));
	}

	T = Pid[0].m_Arrival;
	for (auto& ip = m.begin();!m.empty();)
	{
		if (ip == m.end())
		{
			ip = m.begin();
		}
		PCB* tmp = ip->second;
		if (T >= ip->first)//进程已到达
		{
			if (tmp->m_Server - q == 0)//刚好减完
			{
				T += q;
				cout << "时刻" << T << ",进程" << tmp->m_PidName << "完成，退出" << endl;
				tmp->m_Finish = T;
				tmp->m_Turnaround = tmp->m_Finish - tmp->m_Arrival;
				tmp->m_Weighted = (float)tmp->m_Turnaround / (float)tmp->m_Server;
				g_s_AverTurnaround += tmp->m_Turnaround;
				g_s_AverWeighted += tmp->m_Weighted;
				ip = m.erase(ip);
			}
			else if (ip->second->m_Server - q > 0)
			{
				T += q;
				ip->second->m_Server -= q;
				ip++;

			}
			else//剩余服务时间超过时间片
			{
				T += tmp->m_Server;
				cout << "时刻" << T << ",进程" << tmp->m_PidName << "完成，退出" << endl;
				tmp->m_Finish = T;
				tmp->m_Turnaround = tmp->m_Finish - tmp->m_Arrival;
				tmp->m_Weighted = (float)tmp->m_Turnaround / (float)tmp->m_Server;
				g_s_AverTurnaround += tmp->m_Turnaround;
				g_s_AverWeighted += tmp->m_Weighted;
				ip = m.erase(ip);
			}
		}
	}
	g_s_AverTurnaround /= (float)num;
	g_s_AverWeighted /= (float)num;
	PCB::OutputPid(Pid, num);

}