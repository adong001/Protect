#pragma once
#include <iostream>
#include <fstream>
#include<string>
#include<vector>
#include<functional>
#include<cstdlib>
#include<map>
#include<set>
using namespace std;
typedef struct//分区
{
	static int PartitionNum;//分区数量 
	int m_PartitionId;//分区首地容量址
	int m_PartitionSize;//分区
	int m_BlockId;//空白分区首地址
}Partition;

typedef struct//进程控制块
{
	static int PCBNum;//进程数量
	string m_PidName;//进程名称
	int m_PidSize;//进程大小
}PCB;

void ReadData();//读入数据
void Display1();
void Display_Partition();
void Display();//输出分区完后各个分区的状态
void Display_PCB();//显示进程的状态
void FirstFit();//首次适应算法
void NextFit();//循环首次适应算法
void BestFit();//最佳适应算法
void WorstFit();//最坏适应算法
