#pragma once
#include "stdafx.h"
#include<string>
#include<iostream>
using namespace std;

void addUser(string workid, string password, string ip,string dept,string post,string name); //添加用户
void addUser(string column1, string column2, string column3);
bool userNameIsExist(string workid);                 //判断用户名是否存在
bool loginCheck(string workid, string password);     //判断用户名，密码是否正确,
string getIp(string workid);                            //根据用户名获取用户IP
string getUsername(string ip);                            //根据用户IP获取用户名
void updateIp(string workid, string ip);                //更新用户IP
void updateIpZero(string ip);                             //多个客户端在一台设备登录时，清空以前用户IP
void newpw(string id, string oldpw, string pw);//修改密码接口//id是用户名，pw是新密码
void updateIpZero(string ip);                             //多个客户端在一台设备登录时，清空以前用户IP
void updateIpZero(string ip);                             //多个客户端在一台设备登录时，清空以前用户IP
string reback(void);
string GetALLUsername(void);