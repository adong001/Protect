#pragma once
#include <iostream>
#include <fstream>
#include<string>
#include<vector>
#include<functional>
#include<map>
#define MIN 3
using namespace std;

typedef struct//����
{
	static int PartitionNum;//�������� 
	int m_PartitionId;//������
	int m_Capacity;//��������
	int m_PartitionSize;//������С
}Partition;

typedef struct//���̿��ƿ�
{
	static int PCBNum;//��������
	string m_PidName;//��������
	int m_PidSize;//���̴�С
}PCB;

void ReadData();//��������
void Display();//�������������������״̬
void Display_PCB();//��ʾ���̵�״̬
void FirstFit();//�״���Ӧ�㷨
void NextFit();//ѭ���״���Ӧ�㷨
void BestFit();//�����Ӧ�㷨
void WorstFit();//���Ӧ�㷨
