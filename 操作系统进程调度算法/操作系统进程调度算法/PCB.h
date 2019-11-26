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
	int m_Pid;//进程号
	string m_PName;//进程名
	int  m_Priority; //优先数
	double m_Arrival; //到达时间
	double m_RequireRun; //需要运行时间
	double m_UsedCPU; //已用CPU时间
	int m_PStatus;//进程状态
	static PCB* pcb;//指向对象数组的指针
	static const double TimeSlicing;//时间片
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