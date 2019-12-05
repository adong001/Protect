#pragma once
#include<iostream>
#include<string>
#include<map>
#include<queue>
using namespace std;


class PCB
{
private:
	string m_PidName; //������
	int m_Arrival; //���̵���ʱ��
	int m_Server; //��������ʱ��
	int m_Finish;//�������ʱ��
	int m_Turnaround;//��תʱ��
	float m_Weighted;//��Ȩ��תʱ��
	static float m_s_AverTurnaround;//ƽ����תʱ��
	static float m_s_AverWeighted;//ƽ����Ȩ��תʱ��
	
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