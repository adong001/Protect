#include"rsa.h"

void test_key()
{
	RSA rsa;
	int k = 10;
	while (k)
	{
		rsa.GetKeys();
		Key key = rsa.GetAllKey();
		std::cout << "key._eKey:" << key.m_eKey << "\n" << "key._dKey:" << key.m_dKey << "\n" << "key._pKey:" << key.m_pKey << std::endl;
		DataType original = 10 ;
		DataType decout = rsa.Encrypt(original, key.m_eKey, key.m_pKey);
		std::cout << "original:" << original << std::endl;
		std::cout << "ecrept:" << decout << std::endl;
		std::cout << "decrept:" << rsa.Decrypt(decout, key.m_dKey, key.m_pKey);
		std::cout << std::endl << std::endl;
		k--;
	}
}

void test_file()
{
	RSA rsa;
	///rsa.ProdureKeyFile();
	srand((unsigned int)time(NULL));
	rsa.GetKeys();

	rsa.Encrypt("src.txt", "enc.txt");
	rsa.Decrypt("enc.txt", "dec.txt");
	//Encrypt1(rsa, key, "src.txt", "enc.txt");
	//Decrypt1(rsa,key,"enc.txt", "dec.txt");
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