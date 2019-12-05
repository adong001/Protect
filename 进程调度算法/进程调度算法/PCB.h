#pragma once
#include<iostream>
#include<string>
#include<map>
#include<queue>
using namespace std;


class PCB
{
private:
	string m_PidName; //进程名
	int m_Arrival; //进程到达时间
	int m_Server; //进程运行时间
	int m_Finish;//进程完成时间
	int m_Turnaround;//周转时间
	float m_Weighted;//带权周转时间
	static float m_s_AverTurnaround;//平均周转时间
	static float m_s_AverWeighted;//平均带权周转时间
	
public:
	friend void FCFS();
	friend void SJF();
	friend void RR();
	void InputPid();
	static void OutputPid(PCB* P, int num);
};


void FCFS();
void SJF();
void RR();