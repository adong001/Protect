#pragma once
#include<iostream>
#include<string>
#include<queue>
using namespace std;

void F();

class SJF
{
private:
	string m_PidName; //进程名
	int m_Arrival; //进程到达时间
	int m_Server; //进程运行时间
	int m_Finish;//进程完成时间
	int m_Turnaround;//周转时间
	float m_Weighted;//带权周转时间
public:
	void InputPid();

};

