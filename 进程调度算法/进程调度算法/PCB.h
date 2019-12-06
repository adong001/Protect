#pragma once
#include<iostream>
#include<string>
#include<map>
#include<queue>
#include<fstream>
#include<functional>
using namespace std;

#define BEREADY 0 //就绪状态
#define RUNNING 1 //运行状态
#define WAITING 2 //等待状态

class PCB
{
private:
	string m_PidName; //进程名
	int m_Arrival; //进程到达时间
	int m_Server; //进程运行时间
	int m_Finish;//进程完成时间
	int m_Turnaround;//周转时间
	float m_Weighted;//带权周转时间
	int m_Status;//运行状态
	static float m_s_AverTurnaround;//平均周转时间
	static float m_s_AverWeighted;//平均带权周转时间
	static int m_s_Num;//进程数量
	
public:
	friend void FCFS();
	friend void SJF();
	friend void RR();
	friend void ReadData();
	static void OutputPid(PCB* P, int num);
};

void ReadData();//读入数据
void FCFS();
void SJF();
void RR();