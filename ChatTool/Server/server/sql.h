#pragma once
#include "stdafx.h"
#include<string>
#include<iostream>
using namespace std;

void addUser(string workid, string password, string ip,string dept,string post,string name); //����û�
void addUser(string column1, string column2, string column3);
bool userNameIsExist(string workid);                 //�ж��û����Ƿ����
bool loginCheck(string workid, string password);     //�ж��û����������Ƿ���ȷ,
string getIp(string workid);                            //�����û�����ȡ�û�IP
string getUsername(string ip);                            //�����û�IP��ȡ�û���
void updateIp(string workid, string ip);                //�����û�IP
void updateIpZero(string ip);                             //����ͻ�����һ̨�豸��¼ʱ�������ǰ�û�IP
void newpw(string id, string oldpw, string pw);//�޸�����ӿ�//id���û�����pw��������
void updateIpZero(string ip);                             //����ͻ�����һ̨�豸��¼ʱ�������ǰ�û�IP
void updateIpZero(string ip);                             //����ͻ�����һ̨�豸��¼ʱ�������ǰ�û�IP
string reback(void);
string GetALLUsername(void);