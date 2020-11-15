#include "stdafx.h"
#include "dbConn.h"
#include<string>
#include<iostream>
#include "sql.h"
using namespace std;


void addUser(string column1, string column2, string column3,string column4,string column5,string column6)
{
	string table = "userinfo";
	string workid = column1;
	string password = column2;
	string ip = column3;
	string dept = column4;
	string post = column5;
	string name = column6;
	add(table, workid, password, ip,dept,post,name);
}

void addUser(string column1, string column2, string column3)
{
	string table = "userinfo";
	string workid = column1;
	string password = column2;
	string ip = column3;
	add(table, workid, password, ip);
}

bool userNameIsExist(string column)
{
	string table = "userinfo";
	string workid = column;
	bool is = checkUsername(table, workid);
	return is;
}

bool loginCheck(string column1, string column2)
{
	string table = "userinfo";
	string workid = column1;
	string password = column2;
	string dept = dept;
	string post = post;
	bool is = checkUser(table, workid, password);
	return is;
}

string getIp(string column)
{
	string table = "userinfo";
	string username = column;
	string ip = selectIp(table, username);
	return ip;
}
string getUsername(string column)
{
	string table = "userinfo";
	string ip = column;
	string workid = selectuername(table, ip);
	return workid;
}

void updateIp(string column1, string column2)
{
	string table = "userinfo";
	string workid = column1;
	string ip = column2;
	update(table, workid, ip);
}

void updateIpZero(string column1)
{
	string table = "userinfo";
	string ip = column1;
	updateIP(table, ip);
}
string reback(void)
{
	return string();
}

///ÐÞ¸ÄÃÜÂë
void newpw(string id, string oldpw,string pw)
{

	string table = "userinfo";
	if (checkUser(table, id, oldpw))
	{
		updatePW(table, id, pw);
	}
}
string GetALLUsername(void)
{
	string table = "userinfo";
	string workid = rebackusername(table);
	return workid;
}