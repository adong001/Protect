#include"PCB.h"

float PCB::m_s_AverTurnaround = 0;//平均周转时间
float PCB::m_s_AverWeighted = 0;//平均带权周转时间

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
			printf(" \t\t%3.2f\t  %3.2f\n\n", PCB::m_s_AverTurnaround, PCB::m_s_AverWeighted);
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
		if (T >= tmp->m_Arrival)//上一个进程进行中这个进程已经到了内存
		{
			tmp->m_Finish = T + tmp->m_Server;
			T += tmp->m_Server;
		}

		else//map里的进程空了，直接执行下一个，T要加上等待时间(m_Arrival - T)
		{
			tmp->m_Finish = T + tmp->m_Server + (tmp->m_Arrival - T);
			T += tmp->m_Server + (tmp->m_Arrival - T);
		}
		tmp->m_Turnaround = tmp->m_Finish - tmp->m_Arrival;
		tmp->m_Weighted = (float)tmp->m_Turnaround / (float)tmp->m_Server;
		PCB::m_s_AverTurnaround += tmp->m_Turnaround;
		PCB::m_s_AverWeighted += tmp->m_Weighted;
		cout << "时刻" << T << ",进程" << tmp->m_PidName << "完成，退出" << endl;
		ip = m.erase(ip);
	}
	PCB::m_s_AverTurnaround /= (float)num;
	PCB::m_s_AverWeighted /= (float)num;
	PCB::OutputPid(Pid, num);
}



void SJF()
{
	int num, T;
	cout << "-------------SJF算法-------------\n\n\n";
	cout << "请输入进程个数:" << endl;
	cin >> num;
	PCB* Pid = new PCB[num];
	multimap<int, PCB*> ma;//ma--按到达时间排序
	for (int i = 0; i < num; i++)
	{
		Pid[i].InputPid();
		ma.insert(make_pair(Pid[i].m_Arrival, Pid + i));//最先进入时间
	}

	T = ma.begin()->second->m_Arrival;//开始时刻是先到达的那个进程的到达时间

	for (auto& ip = ma.begin(); !ma.empty();)//跳出条件是m2为空
	{
		PCB* tmp = ip->second;//记录ip->second的值，减少代码的冗余,进入后ip改变，不能使用tmp
		if (T >= tmp->m_Arrival)//进程到达
		{
			auto ip1 = ip;
			int MinServer1 = ip->second->m_Server;
			ip++;
			while (ip != ma.end() && T >= ip->second->m_Arrival)//找到已到达进程中的最小服务时间
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
			tmp = ip->second;//记录ip->second的值，减少代码的冗余
			tmp->m_Finish = T + tmp->m_Server;
			T += tmp->m_Server;
		}
		else
			//运行完进程A之后，其他进程还未到达等待队列中且满足是最小服务时间
		{
			auto ip2 = ip;
			int MinServer2 = ip->second->m_Server;
			int t = ip->second->m_Arrival;
			ip++;
			while (ip != ma.end() && t == ip->second->m_Arrival)//找到已到达进程中的最小服务时间
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
			tmp = ip->second;//记录ip->second的值，减少代码的冗余
			tmp->m_Finish = T + tmp->m_Server + (tmp->m_Arrival - T);
			//完成时间等于上一个进程的完成时间+要等待的时间(tm->m_Arrival-T)+需要运行的时间
			T += tmp->m_Server + (tmp->m_Arrival - T);//时刻T也要加上等待时间
		}
		tmp->m_Turnaround = tmp->m_Finish - tmp->m_Arrival;
		tmp->m_Weighted = (float)tmp->m_Turnaround / (float)tmp->m_Server;
		PCB::m_s_AverTurnaround += tmp->m_Turnaround;
		PCB::m_s_AverWeighted += tmp->m_Weighted;
		cout << "时刻" << T << ",进程" << tmp->m_PidName << "完成，退出" << endl;
		ip = ma.erase(ip);
		ip = ma.begin();//每次从ma的头部(即最先到达的进程找起)
	}
	PCB::m_s_AverTurnaround /= (float)num;
	PCB::m_s_AverWeighted /= (float)num;
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
	multimap<int, PCB*> ma,ma2;

	for (int i = 0; i < num; i++)
	{
		Pid[i].InputPid();
		ma.insert(make_pair(Pid[i].m_Arrival, Pid + i));
	}
	queue<PCB*> qu;

	T = ma.begin()->second->m_Arrival;//取第一个到达内存的进程
	auto ipma = ma.begin();
	while (!ma.empty())//ma为空，轮转完毕
	{
		for (;ipma != ma.end(); ipma++)//找到所有到达的进程push进队列
		{
			if (T >= ipma->second->m_Arrival)
			{
				qu.push(ipma->second);
			}
		}
		auto ip = qu.front();
		if (ip)
		{
			if (ip->m_Server - q == 0)//刚好减完
			{
				T += q;
				cout << "时刻" << T << ",进程" << ip->m_PidName << "完成，退出" << endl;
				ip->m_Server -= q;//注意：此算法中每次运行到一个进程时会给他的服务时间减去一个时间片(减完大于0)
				ip->m_Finish = T;
				ip->m_Turnaround = ip->m_Finish - ip->m_Arrival;
				ip->m_Weighted = (float)ip->m_Turnaround / (float)ip->m_Server;
				PCB::m_s_AverTurnaround += ip->m_Turnaround;
				PCB::m_s_AverWeighted += ip->m_Weighted;
			}
			else if (ip->m_Server - q > 0)
			{
				T += q;
				ip->m_Arrival += q;//到达时间也跟着变化
				ip->m_Server -= q;
				ip++;
			}
			else//剩余服务时间超过时间片
			{
				T += ip->m_Server;
				cout << "时刻" << T << ",进程" << ip->m_PidName << "完成，退出" << endl;
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
