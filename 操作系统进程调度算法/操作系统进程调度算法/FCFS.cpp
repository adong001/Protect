#include"FCFS.h"

void FCFS::InputPid()
{

	cout << "�����������";
	cin >> m_PidName;
	cout << "���̵���ʱ��:";
	cin >> m_Arrival;
	cout << "��������ʱ��:";
	cin >> m_Server;
	cout << endl;
}


void F()
{
	int num,T;
	cout << "-------------FCFS�㷨-------------\n\n\n";
	cout << "��������̸���:" << endl;
	cin >> num;
	FCFS* Pid = new FCFS[num];
	for (int i = 0; i < num; i++)
	{
		Pid[i].InputPid();
	}

}
