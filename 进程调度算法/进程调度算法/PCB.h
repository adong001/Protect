#pragma once
#include<iostream>
#include<string>
#include<map>
#include<queue>
#include<fstream>
#include<functional>
using namespace std;

#define BEREADY 0 //����״̬
#define RUNNING 1 //����״̬
#define WAITING 2 //�ȴ�״̬

class PCB
{
private:
	string m_PidName; //������
	int m_Arrival; //���̵���ʱ��
	int m_Server; //��������ʱ��
	int m_Finish;//�������ʱ��
	int m_Turnaround;//��תʱ��
	float m_Weighted;//��Ȩ��תʱ��
	int m_Status;//����״̬
	static float m_s_AverTurnaround;//ƽ����תʱ��
	static float m_s_AverWeighted;//ƽ����Ȩ��תʱ��
	static int m_s_Num;//��������
	
public:
	friend void FCFS();
	friend void SJF();
	friend void RR();
	friend void ReadData();
	static void OutputPid(PCB* P, int num);
};

void ReadData();//��������
void FCFS();
void SJF();
void RR();