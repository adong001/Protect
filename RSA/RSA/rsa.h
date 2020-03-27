#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS
#include<iostream>
#include<ctime>
#include<string>
#include<fstream>
//#include<xutility>
#include <boost/multiprecision/random.hpp>
#include<boost/multiprecision/cpp_int.hpp>
#include<boost/multiprecision/miller_rabin.hpp>//���������
#define NUMBER 10   //һ�μ���NUMBER���ֽڴ�С������
#define OFFSET 40  //Կ�׵�λ��

using namespace std;
namespace mp = boost::multiprecision;
namespace rp = boost::random;
//typedef long DataType;
typedef mp::cpp_int DataType;//DataType��һ������λ�Ĵ���


struct Key
{ 
	DataType m_eKey;//������Կ��e
	DataType m_dKey;//������Կ, d
	DataType m_pKey;//n
};

/*
	1.��������
	2.��n
	3.��f(n)
	4.��e (1< e < f(n), e��f(n)���ɻ��ʣ����ѡ��)
	5.��d (e * d % f(n) = 1)
	(e , n) (d , n)
	*/

class RSA
{
private:

	Key m_key;
	

public:
	void ProdureKeyFile(const char* ekey_file, const char* dkey_file, const char* pkey_file);//����Կ���ļ�
	DataType ExGcd(DataType a, DataType b, DataType& x, DataType& y);//��ģ��Ԫ��(��Կe)
	DataType Encrypt(DataType data, DataType ekey, DataType pkey);//���ܺ���
	DataType Decrypt(DataType data, DataType dkey, DataType pkey);//���ܺ���
	DataType GetPrime();//��ȡ����
	bool IsPrime(DataType data);//�ж��Ƿ�Ϊ����
	DataType GetPKey(DataType prime1, DataType prime2);//��ȡ��Կ
	DataType GetOrla(DataType prime1, DataType prime2);//ŷ������
	DataType GetEKey(DataType orla);//��ȡ��Կe
	DataType GetDKey(DataType ekey, DataType orla);//��ȡ˽Կd
	DataType GetGcd(DataType data1, DataType data2);//��ȡ�����������Լ��
	Key GetAllKey();//�����װ����˽�г�Ա�Ľӿ�

	void GetKeys();//��ȡȫ����Կ��
	void Encrypt(const char* filename, const char* fileout);//�ļ�����
	void Decrypt(const char* filename, const char* fileout);//�ļ�����

};