#pragma once
#include"iostream"
#include"fstream"
#include"iomanip"
using namespace std;
class person//������Ϣ
{
public:
	void add();
protected:
	char name[10];
	char* sex;
};


class student :public person//�̳� person ��
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
	char tel[20];//����ѧ��  �����  �绰����
	char cnum[5];
	char cname[15];
	int xuefen;
	int pingshif;
	int shiyanf;
	int juanmianf;
	double totalxuefen;
	double score;//����γ̺�  �γ���  ѧ��  ƽʱ�ɼ�  ʵ��ɼ�  ����ɼ� �ۺϷ�  ��ѧ��
};

bool comp(char s1[], char s2[]);          //�Ƚ������ַ������