#include"PCB.h"

void InputPcb()
{
	map<int, int> m;
	int Pcbnum;
	cout << "����Ҫ�����ȵĽ�������";
	cin >> Pcbnum;
	PCB::pcb = new PCB[Pcbnum];
	int i =m.size();
	for (; i < Pcbnum; i++)
	{
		PCB::pcb[i].m_Pid = i;
		cout << endl << endl << "������Pid[" << i << "]���̣�";
		cout << endl << "��������";
		cin >> PCB::pcb[i].m_PName;
		cout << endl << "���ȼ���";
		cin >> PCB::pcb[i].m_Priority;
		cout << endl << "��Ҫ����ʱ�䣺";
		cin >> PCB::pcb[i].m_RequireRun;
		m.insert(make_pair(PCB::pcb[i].m_Priority, i));
	}
}