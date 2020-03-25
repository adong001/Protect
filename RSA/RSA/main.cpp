#include"rsa.h"

void test_key()
{
	RSA rsa;
	int k = 2;
	//while (k)
	//{
	//	rsa.GetKeys();
	//	Key key = rsa.GetAllKey();
	//	cout << "key._eKey:" << key.m_eKey << "\n" << "key._dKey:" <<key.m_dKey << "\n" << "key._pKey:" << key.m_pKey << endl;
	//	DataType original("1234");
	//	DataType decout = rsa.Encrypt(original, key.m_eKey, key.m_pKey);
	//	cout << "original:" << original << endl;
	//	cout << "ecrept:" << decout << endl;
	//	cout << "decrept:" << rsa.Decrypt(decout, key.m_dKey, key.m_pKey);
	//	cout << endl << endl;
	//	k--;
	//}
	rsa.GetKeys();
	Key key = rsa.GetAllKey();
	cout << "key._eKey:" << key.m_eKey << "\n" << "key._dKey:" << key.m_dKey << "\n" << "key._pKey:" << key.m_pKey << endl;
	DataType original = 'h';
	DataType decout = rsa.Encrypt(original, key.m_eKey, key.m_pKey);
	cout << "original:" << original << endl;
	cout << "ecrept:" << decout << endl;
	cout << "decrept:" << rsa.Decrypt(decout, key.m_dKey, key.m_pKey);
	cout << endl << endl;

	original = 'e';
	decout = rsa.Encrypt(original, key.m_eKey, key.m_pKey);
	cout << "original:" << original << endl;
	cout << "ecrept:" << decout << endl;
	cout << "decrept:" << rsa.Decrypt(decout, key.m_dKey, key.m_pKey);
	cout << endl << endl;

	original = 'l';
	decout = rsa.Encrypt(original, key.m_eKey, key.m_pKey);
	cout << "original:" << original << endl;
	cout << "ecrept:" << decout << endl;
	cout << "decrept:" << rsa.Decrypt(decout, key.m_dKey, key.m_pKey);
	cout << endl << endl;

	original = 'o';
	decout = rsa.Encrypt(original, key.m_eKey, key.m_pKey);
	cout << "original:" << original << endl;
	cout << "ecrept:" << decout << endl;
	cout << "decrept:" << rsa.Decrypt(decout, key.m_dKey, key.m_pKey);
	cout << endl << endl;
}



void test_file()
{
	RSA rsa;
	rsa.GetKeys();
	rsa.Encrypt("原文件.txt", "加密文件.txt");
	//rsa.Decrypt("加密文件.txt", "解密文件.txt");
}


//void GetPrime1()//获取素数
//{
//	rp::mt19937 gen(time(NULL));
//	ofstream fout("素数表.txt", ifstream::binary);
//	if (!fout.is_open())
//	{
//		perror("input file open failed\n");
//		return;
//	}
//	int num = 3;//产生1000个大素数
//
//	DataType prime;
//	while (num--)
//	{
//		while (true)
//		{
//			rp::uniform_int_distribution<mp::cpp_int> dist(0, mp::cpp_int(1) << 128);
//			//prime = rand() % 100 + 2;
//			prime = dist(gen);
//			if (IsPrime1(prime))
//			{
//				string tmp(prime);
//				tmp += '\n';
//				fout.write(tmp.c_str(), tmp.size() + 1);
//				cout << prime << endl;
//				break;
//			}
//		}
//	}
//}


int main()
{
	//GetPrime1();
	//GetRandom();
	//test_add_sub_mul_div();
	//test_key();
	//test_boost();
	test_file();
	system("pause");
	return 0;
}