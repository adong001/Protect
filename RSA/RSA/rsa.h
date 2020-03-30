#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS
#include<iostream>
#include<ctime>
#include<string>
#include<fstream>
#include<boost/multiprecision/cpp_int.hpp>
#include<boost/multiprecision/miller_rabin.hpp>//���������
#define NUMBER 2048   //һ�μ���NUMBER���ֽڴ�С������
#define OFFSET 128  //Կ�׵�λ��
#define KEYS 5 //����Կ�׵ĸ���
#define EKEYFILE "./ekey.txt" //����Կ�׵�Ĭ���ļ�·��
#define DKEYFILE "./dkey.txt" //���ڵ�һ�β���100��Կ�׹��Ժ�ʹ�ã��Ժ�ӽ������ݲ����˷�ʱ�����������Կ��
#define PKEYFILE "./pkey.txt"
namespace mp = boost::multiprecision;
namespace rp = boost::random;
typedef mp::uint1024_t DataType;//DataType��һ������λ�Ĵ���
#define LENGTH sizeof(DataType) //DataType�Ĵ�С

struct Key
{ 
	DataType m_eKey;//������Կ��e
	DataType m_dKey;//������Կ, d
	DataType m_pKey;//n
};

class RSA
{
private:

	Key m_key;
	

public:

	void ProdureKeyFile(const char* ekey_file = EKEYFILE, const char* dkey_file = DKEYFILE, const char* pkey_file = PKEYFILE);//����Կ���ļ�
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