#pragma once
#include<string>
#include<iostream>
using namespace std;
void add(string table, string column1, string column2, string column3,string dept,string post,string name);
void add(string table, string uName, string pWord, string ip);
string selectIp(string table, string column);
string selectuername(string table, string column);
string rebackusername(string table);
bool checkUsername(string table, string column);
bool checkUser(string table, string column1, string column2);
void update(string table, string column1, string column2);
void updateIP(string table, string column1);
void updatePW(string table, string workid, string PW);
