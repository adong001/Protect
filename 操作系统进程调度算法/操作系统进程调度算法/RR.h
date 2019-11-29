//#pragma once
//#include<iostream>
//#include<string>
//#include<map>
//#define WAITING 0
//#define RUNNING 1
//#define FINISHED 2
//using namespace std;
//
//class PrioirityQueue;
//
//
//class Process
//{
//private:
//	int m_Pid;//进程号
//	string m_PName;//进程名
//	float  m_Priority; //优先数
//	float m_Arrival; //到达时间
//	float m_RequireRun; //需要运行时间
//	float m_UsedCPU; //已用CPU时间
//	int m_PStatus;//进程状态
//	friend class PrioirityQueue;
//public:
//	
//};
//
//class PrioirityQueue
//{
//private:
//	const double m_TimeSlice;//时间片
//	Process* m_PCB;
//public:
//	PrioirityQueue(double TimeSlice) :
//		m_PCB(nullptr),
//		m_TimeSlice(TimeSlice)
//	{}
//	void InputPcb();
//	void OutputPcb();
//	void updataPcb();
//};
//
