#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<ctime>
#include<algorithm>
#include<string>
#include<fstream>
#include<cmath>
#include<utility>

//#include <boost/multipercision/cpp_int.hpp>"//�����⣬����ǿ��(����ָ�룬lamba���ʽ)
using namespace std;

/*void test()
{
	boost::multiprecision::cpp_int ci;
	ci = 1024;
	cout << ci << endl;
	ci = 23456789072837823439287165347894382765493230403483049324838947;
	cout << ci << endl;
}*/

class BigInt
{
private:
	string m_number;
	bool less(string num1, string num2);
public:
	//ͨ���ַ�����ʾ����
	string add(string num1, string num2);
	string sub(string num1, string num2);
	string mul(string num1, string num2);
	pair<string,string> div(string num1, string num2);//���������̺�����

	BigInt operator+(BigInt& bi);
	BigInt operator-(BigInt& bi);
	BigInt operator*(BigInt& bi);
	BigInt operator/(BigInt& bi);
	BigInt operator%(BigInt& bi);

	BigInt& operator+=(BigInt& bi);
	BigInt& operator-=(BigInt& bi);
	BigInt& operator*=(BigInt& bi);
	BigInt& operator/=(BigInt& bi);
	BigInt& operator%=(BigInt& bi);

	BigInt& operator++();
	BigInt operator++(int);//����
	BigInt& operator--();
	BigInt operator--(int);//����
	
	friend ostream& operator<<(ostream& os, BigInt& bi);
	friend istream& operator>>(istream& is, BigInt& bi);

	BigInt(){}
	BigInt(const string& num);
	BigInt(const int num);
};