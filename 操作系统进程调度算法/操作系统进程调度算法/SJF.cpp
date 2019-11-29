#include"SJF.h"

void SJF::InputPid()
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
	int num;
	cout << "-------------SJF算法-------------\n\n\n";
	cout << "请输入进程个数:" << endl;
	cin >> num;
	SJF* Pid = new SJF[num];
	for (int i = 0; i < num; i++)
	{
		Pid[i].InputPid();
	}

}
