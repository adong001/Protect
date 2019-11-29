#pragma once
#include<iostream>
#include<string>
#include<map>
using namespace std;

static float g_s_AverTurnaround = 0;//ƽ����תʱ��
static float g_s_AverWeighted = 0 ;//ƽ����Ȩ��תʱ��

class PCB
{
private:
	string m_PidName; //������
	int m_Arrival; //���̵���ʱ��
	int m_Server; //��������ʱ��
	int m_Finish;//�������ʱ��
	int m_Turnaround;//��תʱ��
	float m_Weighted;//��Ȩ��תʱ��
	
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