#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<map>
using namespace std;

void F();

class FCFS
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
	void OutputPid();
	friend void F();
};

