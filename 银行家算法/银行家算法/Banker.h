#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
using namespace std;

enum Status//系统可能出现的状态
{
	NEED_REQUEST = 0,//所需资源超过此进程宣布的最大值
	AVAILABLE_REQUEST,//所需资源超过此系统当前资源
	SECURITY,//安全状态
	UNSECURITY,//不安全状态
	SUCCESS,//分配成功
	FAIL//分配失败
};

void Init();//初始化
void Display();//显示各个进程资源情况
void Dis_char(int i, char ch);//将ch字符显示i次
bool operator <= (vector<int>& Request, vector<int>& Need);//比较是否Request都小于等于Need
void Display_Security(pair<vector<int>, Status>& val);//显示安全序列
void Display_Security2(pair<vector<int>, Status>& val);//显示各个进程安全情况
void Require();//进程请求资源
pair<vector<int>, Status> AlgoBanker(int Pid, vector<int>& Requset);//银行家算法
pair<vector<int>, Status> AlgoSecurity();//安全性算法




