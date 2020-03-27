#include"rsa.h"

void test_key()
{
	RSA rsa;
	int k = 10;
	while (k)
	{
		rsa.GetKeys();
		Key key = rsa.GetAllKey();
		cout << "key._eKey:" << key.m_eKey << "\n" << "key._dKey:" <<key.m_dKey << "\n" << "key._pKey:" << key.m_pKey << endl;
		DataType original = 10 ;
		DataType decout = rsa.Encrypt(original, key.m_eKey, key.m_pKey);
		cout << "original:" << original << endl;
		cout << "ecrept:" << decout << endl;
		cout << "decrept:" << rsa.Decrypt(decout, key.m_dKey, key.m_pKey);
		cout << endl << endl;
		k--;
	}
}

void test_file()
{
	RSA rsa;
	rsa.GetKeys();
	rsa.Encrypt("原文件.txt", "加密文件. txt");
	//rsa.Decrypt("加密文件.txt", "解密文件.txt");
}



int main()
{
	//GetPrime1();
	//GetRandom();
	//test_add_sub_mul_div();
	//test_boost();
	//test_key();
	test_file();
	//RSA rsa;
	//rsa.ProdureKeyFile("ekey.txt", "dkey.txt", "pkey.txt");
	system("pause");
	return 0;
}