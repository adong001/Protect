#include"SJF.h"

void SJF::InputPid()
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
	int num;
	cout << "-------------SJF�㷨-------------\n\n\n";
	cout << "��������̸���:" << endl;
	cin >> num;
	SJF* Pid = new SJF[num];
	for (int i = 0; i < num; i++)
	{
		Pid[i].InputPid();
	}

}
