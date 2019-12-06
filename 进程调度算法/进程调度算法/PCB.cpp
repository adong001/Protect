#include"PCB.h"

float PCB::m_s_AverTurnaround = 0;//平均周转时间
float PCB::m_s_AverWeighted = 0;//平均带权周转时间
int PCB::m_s_Num = 0;//进程数量
PCB *Pid;

void ReadData()//读入数据
{
	ifstream readData;
	readData.open("data.txt");

	readData >> PCB::m_s_Num;//读入分区数量	
	Pid = new PCB[PCB::m_s_Num];//开空间

	for (int i = 0; i < PCB::m_s_Num; i++)//读入进程名称
	{
		readData >> Pid[i].m_PidName;
	}

	for (int i = 0; i < PCB::m_s_Num; i++)//读入进程到达时间
	{
		readData >> Pid[i].m_Arrival;
	}

	for (int i = 0; i < PCB::m_s_Num; i++)//读入进程运行时间
	{
		readData >> Pid[i].m_Server;
	}
	readData.close();
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
	ReadData();

	num = PCB::m_s_Num;
	multimap<int, PCB*> ma;//ma--按到达时间排序
	for (int i = 0; i < num; i++)
	{
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
	queue<PCB*> qu;
	PCB* cur;
	typedef struct
	{
		int Arrival;
		int Server;
	}tmp;
	map<string, tmp*> ma;
	cout << "-------------RR算法-------------\n\n\n";
	ReadData();

	num = PCB::m_s_Num;
	tmp * t = new tmp[num];
	cout << "设置时间片:";
	cin >> q;

	for (int i = 0; i < num; i++)//先使所有进程处于等待状态
	{
		t[i].Arrival = Pid[i].m_Arrival;
		t[i].Server = Pid[i].m_Server;
		ma.insert(make_pair(Pid[i].m_PidName,t + i));//将所有到达时间保存，在进程运行时会修改，运行完重新赋回去
		Pid[i].m_Status = WAITING;
	}
	T = Pid[0].m_Arrival;//取第一个到达内存的进程p
	qu.push(Pid);

	while (!qu.empty())//ma为空，轮转完毕
	{
		cur = qu.front();
		cur->m_Status = RUNNING;//拿到时间片状态标志位改变为RUNNING
		if (cur->m_Server - q == 0)//刚好减完
		{
			T += q;
			cout << "时刻" << T << ",进程" << cur->m_PidName << "完成，退出" << endl;
			cur->m_Finish = T;
			cur->m_Turnaround = cur->m_Finish - ma[cur->m_PidName]->Arrival;
			cur->m_Weighted = (float)(cur->m_Turnaround) / (float)(ma[cur->m_PidName]->Server);
			PCB::m_s_AverTurnaround += cur->m_Turnaround;
			PCB::m_s_AverWeighted += cur->m_Weighted;
			cur->m_Server = 0;//输出完以后置为0，防止再次调用
		}
		else if (cur->m_Server - q > 0)
		{
			T += q;
			cur->m_Arrival += q;//到达时间也跟着变化
			cur->m_Server -= q;
		}
		else//剩余服务时间超过时间片
		{
			T += cur->m_Server;
			cout << "时刻" << T << ",进程" << cur->m_PidName << "完成，退出" << endl;
			cur->m_Finish = T;
			cur->m_Turnaround = cur->m_Finish - ma[cur->m_PidName]->Arrival;
			cur->m_Weighted = (float)(cur->m_Turnaround) / (float)(ma[cur->m_PidName]->Server);
			cur->m_Server = 0;//输出完以后置为0，防止再次调用
			PCB::m_s_AverTurnaround += cur->m_Turnaround;
			PCB::m_s_AverWeighted += cur->m_Weighted;
		}
		qu.pop();//运行完就pop掉

		for (int i = 0; i < num ; i++)
		//将在上一个进程运行时间内和运行完这段时间中所有到达的进程push进队
		{
			if (T >= Pid[i].m_Arrival && Pid[i].m_Status == WAITING)
			{
				qu.push(Pid + i);
				qu.back()->m_Status = BEREADY;//让其处于就绪队列中
			}
		}

		if (cur->m_Server != 0)//这个进程运行完后判断是否结束，没结束就加入队尾
		{
			qu.push(cur);
			cur->m_Status = BEREADY;//让其处于就绪队列中
		}
	}
	for (int i = 0; i < num; i++)
	{
		Pid[i].m_Arrival = ma[Pid[i].m_PidName]->Arrival;//将保存的值赋回去
		Pid[i].m_Server = ma[Pid[i].m_PidName]->Server;
	}

	PCB::m_s_AverTurnaround /= (float)num;
	PCB::m_s_AverWeighted /= (float)num;
	PCB::OutputPid(Pid, num);
}
