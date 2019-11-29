#include"FCFS.h"

void FCFS::InputPid()
{

	cout << "请输入进程名";
	cin >> m_PidName;
	cout << "进程到达时间:";
	cin >> m_Arrival;
	cout << "进程运行时间:";
	cin >> m_Server;
	cout << endl;
}


void F()
{
	int num,T;
	cout << "-------------FCFS算法-------------\n\n\n";
	cout << "请输入进程个数:" << endl;
	cin >> num;
	FCFS* Pid = new FCFS[num];
	for (int i = 0; i < num; i++)
	{
		Pid[i].InputPid();
	}

}
