#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
#include<cstdio>
#include<cstdlib>
using namespace std;

enum Status//ϵͳ���ܳ��ֵ�״̬
{
	NEED_REQUEST = 0,//������Դ�����˽������������ֵ
	AVAILABLE_REQUEST,//������Դ������ϵͳ��ǰ��Դ
	SECURITY,//��ȫ״̬
	UNSECURITY//����ȫ״̬
};

vector<vector<int>> Allocation;//ϵͳ���˽����ѷ�����Դ
vector<vector<int>> Need;//�˽��̻��������Դ
vector<vector<int>> Max;//�˽�����Ҫ�����Դ

vector<int> Available;//ϵͳ������Դ
vector<vector<int>> Work;//��������
vector<bool> Finish;//�ɷ����־


void Init();//��ʼ��
void Display();//��ʾ����������Դ���


Status Requset();//����������Դ
Status AlgoBanker();//���м��㷨
Status AlgoSecurity();//��ȫ���㷨




