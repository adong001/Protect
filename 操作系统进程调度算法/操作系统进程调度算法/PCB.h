#pragma once
#include<iostream>
#include<string>
#include<map>
#define WAITING 0
#define RUNNING 1
#define FINISHED 2
using namespace std;

void InputPcb();

class PCB
{
private:
	int m_Pid;//���̺�
	string m_PName;//������
	int  m_Priority; //������
	double m_Arrival; //����ʱ��
	double m_RequireRun; //��Ҫ����ʱ��
	double m_UsedCPU; //����CPUʱ��
	int m_PStatus;//����״̬
	static PCB* pcb;//ָ����������ָ��
	static const double TimeSlicing;//ʱ��Ƭ
public:
	friend void InputPcb();
	~PCB()
	{
		if (this)
		{
			delete this;
		}
	}
};

//PCB* PCB::pcb = nullptr;
//const double PCB::TimeSlicing = 0;