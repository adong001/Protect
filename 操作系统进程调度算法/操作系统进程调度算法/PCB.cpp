#include"PCB.h"

void InputPcb()
{
	map<int, int> m;
	int Pcbnum;
	cout << "输入要被调度的进程数：";
	cin >> Pcbnum;
	PCB::pcb = new PCB[Pcbnum];
	int i =m.size();
	for (; i < Pcbnum; i++)
	{
		PCB::pcb[i].m_Pid = i;
		cout << endl << endl << "请输入Pid[" << i << "]进程：";
		cout << endl << "进程名：";
		cin >> PCB::pcb[i].m_PName;
		cout << endl << "优先级：";
		cin >> PCB::pcb[i].m_Priority;
		cout << endl << "需要运行时间：";
		cin >> PCB::pcb[i].m_RequireRun;
		m.insert(make_pair(PCB::pcb[i].m_Priority, i));
	}
}