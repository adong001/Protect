#pragma once
#include<iostream>
#include<string>
#include<queue>
using namespace std;

void F();

class SJF
{
private:
	string m_PidName; //������
	int m_Arrival; //���̵���ʱ��
	int m_Server; //��������ʱ��
	int m_Finish;//�������ʱ��
	int m_Turnaround;//��תʱ��
	float m_Weighted;//��Ȩ��תʱ��
public:
	void InputPid();

};

