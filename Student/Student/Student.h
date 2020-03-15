#pragma once
#include"iostream"
#include"fstream"
#include"iomanip"
using namespace std;
class person//基本信息
{
public:
	void add();
protected:
	char name[10];
	char* sex;
};


class student :public person//继承 person 类
{
public:
	void add();
	void add2();
	void grade();
	void menue();
	void reader();
	void searchname();
	void searchroom();
	void searchnumber();
	void disp();
	int room1(){ return room; };
	int number1(){ return number; };
	void searchgrade();
	double gradedisp();
	void dispname();
	void paixu();
private:
	int number;
	int room;
	char tel[20];//定义学号  宿舍号  电话号码
	char cnum[5];
	char cname[15];
	int xuefen;
	int pingshif;
	int shiyanf;
	int juanmianf;
	double totalxuefen;
	double score;//定义课程号  课程名  学分  平时成绩  实验成绩  卷面成绩 综合分  总学分
};

bool comp(char s1[], char s2[]);          //比较两个字符串相等