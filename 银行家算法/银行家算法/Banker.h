#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
using namespace std;

enum Status//ϵͳ���ܳ��ֵ�״̬
{
	NEED_REQUEST = 0,//������Դ�����˽������������ֵ
	AVAILABLE_REQUEST,//������Դ������ϵͳ��ǰ��Դ
	SECURITY,//��ȫ״̬
	UNSECURITY,//����ȫ״̬
	SUCCESS,//����ɹ�
	FAIL//����ʧ��
};

void Init();//��ʼ��
void Display();//��ʾ����������Դ���
void Dis_char(int i, char ch);//��ch�ַ���ʾi��
bool operator <= (vector<int>& Request, vector<int>& Need);//�Ƚ��Ƿ�Request��С�ڵ���Need
void Display_Security(pair<vector<int>, Status>& val);//��ʾ��ȫ����
void Display_Security2(pair<vector<int>, Status>& val);//��ʾ�������̰�ȫ���
void Require();//����������Դ
pair<vector<int>, Status> AlgoBanker(int Pid, vector<int>& Requset);//���м��㷨
pair<vector<int>, Status> AlgoSecurity();//��ȫ���㷨




