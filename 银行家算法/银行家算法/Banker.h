#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
#include<cstdio>
#include<cstdlib>
using namespace std;

enum Status//系统可能出现的状态
{
	NEED_REQUEST = 0,//所需资源超过此进程宣布的最大值
	AVAILABLE_REQUEST,//所需资源超过此系统当前资源
	SECURITY,//安全状态
	UNSECURITY//不安全状态
};

vector<vector<int>> Allocation;//系统给此进程已分配资源
vector<vector<int>> Need;//此进程还需分配资源
vector<vector<int>> Max;//此进程需要最大资源

vector<int> Available;//系统可用资源
vector<vector<int>> Work;//工作向量
vector<bool> Finish;//可分配标志


void Init();//初始化
void Display();//显示各个进程资源情况


Status Requset();//进程请求资源
Status AlgoBanker();//银行家算法
Status AlgoSecurity();//安全性算法




