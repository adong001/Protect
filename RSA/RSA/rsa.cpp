#include"rsa.h"

//����Կ���ļ�
void RSA::ProdureKeyFile(const char* ekey_file, const char* dkey_file, const char* pkey_file)
{
	int keys = KEYS;
	std::ofstream fe(ekey_file, std::ofstream::binary);
	std::ofstream fd(dkey_file, std::ofstream::binary);
	std::ofstream fp(pkey_file, std::ofstream::binary);

	while (keys--)
	{
		DataType prime1 = GetPrime();
		DataType prime2 = GetPrime();
		while (prime1 == prime2)
		{
			prime2 = GetPrime();
		} 
		DataType orla = GetOrla(prime1, prime2);
		m_key.m_eKey = GetEKey(orla);
		m_key.m_dKey = GetDKey(m_key.m_eKey, orla);
		m_key.m_pKey = GetPKey(prime1, prime2);
		fe.write((char*)&m_key.m_eKey, LENGTH);
		fd.write((char*)&m_key.m_dKey, LENGTH);
		fp.write((char*)&m_key.m_pKey, LENGTH);
		std::cout << "------------------------" << std::endl;
		std::cout << "m_eKey = " << m_key.m_eKey << std::endl;
		std::cout << "m_dKey = " << m_key.m_dKey << std::endl;
		std::cout << "m_pKey = " << m_key.m_pKey << std::endl;
		std::cout << "------------------------" << std::endl;
	}
	fe.close();
	fd.close();
	fp.close();

}

void RSA::Encrypt(const char* filename,const char* fileout)//�ļ�����
{
	std::ifstream fin(filename,std::ifstream::binary);
	std::ofstream fout(fileout, std::ofstream::binary);
	if (!fin.is_open())
	{
		perror("input file open failed\n");
		return;
	}
	
	char bufferin[NUMBER]; 
	DataType bufferout[NUMBER];
	int curNum;
	while (!fin.eof())
	{
		fin.read(bufferin, NUMBER);//ÿ�ζ�NUMBER���ֽڵ�����
		curNum = fin.gcount();//�����������ֽ������п��ܺ��������
		int i;
		std::cout << "m_eKey = " << m_key.m_eKey << std::endl;
		std::cout << "m_dKey = " << m_key.m_dKey << std::endl;
		std::cout << "m_pKey = " << m_key.m_pKey << std::endl;
		for (i = 0; i < curNum; i++)
		{
			
			bufferout[i] = Encrypt((DataType)bufferin[i], m_key.m_eKey, m_key.m_pKey);
			//ÿ�ν�һ���ֽڼ��ܳ�һ��DataType�ͣ�д��bufferout��������
			std::cout << bufferin[i] << "  �����ܳ�  " << bufferout[i] << std::endl;
		}
		fout.write((char*)bufferout, curNum * LENGTH);
		//��Ϊÿ�ν�һ���ֽڼ��ܳ�һ��DataType�ͣ�������curNum�Σ�bufferoutÿ��Ԫ�ش�СΪlength
		//����Ҫ��foutд��curNum * length���ֽ�
	}
	fin.close();
	fout.close();
}

void RSA::Decrypt(const char* filename, const char* fileout)//�ļ�����
{
	std::ifstream fin(filename, std::ifstream::binary);
	std::ofstream fout(fileout, std::ofstream::binary);
	if (!fin.is_open())
	{
		perror("input file open failed\n");
		return;
	}	
	int curNum;
	DataType bufferin[NUMBER] = {0};
	char bufferout[NUMBER] = {0};
	while (!fin.eof())
	{
		fin.read((char*)bufferin, NUMBER * LENGTH);//ÿ�ζ�NUMBER��DataType�ֽڵ�����
		curNum = fin.gcount();//�����������ֽ������п��ܺ��������
		curNum /= LENGTH;//��������curNum��DataType�ֽڵ����ݣ�����ͽ���curNum��
		int i;
		std::cout << "-----------------\n";
		std::cout << "m_eKey = " << m_key.m_eKey << std::endl;
		std::cout << "m_dKey = " << m_key.m_dKey << std::endl;
		std::cout << "m_pKey = " << m_key.m_pKey << std::endl;
		for (i = 0; i < curNum; i++)
		{
			//ÿ����datatypeΪ��λ���н��ܣ�curnum��datatype�ֽڵ����ݣ�������curnum��
			//ÿ�ν�һ��datatypeΪ��λ�����ݽ��ܳ�һ���ֽڵ����ݣ�д��bufferout��������
			bufferout[i] = (char)Encrypt(bufferin[i], m_key.m_dKey, m_key.m_pKey);
			std::cout << bufferin[i] << "  �����ܳ�  " << bufferout[i] << std::endl;
		}
		fout.write(bufferout, curNum);
		//����curNum�Σ��͵õ�curNum�ֽڵ����ݣ�д��fout�ļ���
	}
	fin.close();
	fout.close();
}

DataType RSA::Encrypt(DataType data, DataType ekey, DataType pkey)//���ܺ���
{
	//msgE-->���ģ�data-->���ģ�ekey-->��Կ��pkey-->n
	/*���ܣ�msgE = (data^ekey)% pkey 
				 = ((data^(b0*2^0) * data^(b1*2^1)*......*data^(bn*2^n))% pkey 
	             = ((data^(2^i)) *......*(data^(2^n)))% pkey  //i����data ����λΪ1��λ��
				 = (((data^(2^i)) % pkey) *......*((data^(2^n)) % pkey))% pkey
��Ai = (data^(2^i))% pkey
  An = (data^(2^n))% pkey
     = (data^(2^(n-1))% pkey * data^(2^(n-1))% pkey)% pkey
	 = (An-1 * An-1) %pkey
				 = (Ai * ......* An);
				 ����ÿ�ζ�%pkey���Ͳ�������������
	*/
	DataType Ai = data;
	DataType msgE = 1;
	//data^ekey % pkey
	while (ekey)
	{
		if (ekey & 1)//ȡ������λΪ1��
		{
			msgE = (msgE * Ai) % pkey;//msgE = ����Ai ,��һ��Ai = data^ 2^ i % pkey
		}
		ekey >>= 1;//ȡ��һλ
		Ai = (Ai * Ai) % pkey; //Ai+1 = (Ai * Ai) % pkey
	}
	return msgE;//����
}

DataType RSA::Decrypt(DataType data, DataType dkey, DataType pkey)//���ܺ���
{
	//msgE-->���ģ�data-->���ģ�dkey-->˽Կ��pkey-->n
	//���ܣ�msgE = (data^dkey)%n 
	return Encrypt(data, dkey, pkey);
}


DataType RSA::GetPrime()//��ȡ����
{
	rp::mt19937 gen((unsigned int)time(NULL));
	rp::uniform_int_distribution<DataType> dist(2, DataType(1) << OFFSET);
	//�����ȡһ��128λ�Ĵ���  
	DataType prime;
	while (true)
	{
		prime = dist(gen);
		if (IsPrime(prime))
		{
			break;
		}
	}
	//std::cout << "prime = " << prime << std::endl;
	return prime;
}

bool RSA::IsPrime(DataType data)//�ж��Ƿ�Ϊ����
{
	rp::mt11213b gen((unsigned int)time(nullptr));
	if (mp::miller_rabin_test(data, 25, gen))
	{
		if (mp::miller_rabin_test((data - 1) / 2, 25, gen))
		{
			return true;
		}
	}
	return false;
}
DataType RSA::GetPKey(DataType prime1, DataType prime2)//��ȡn
{
	//f(n) = f(p1*p2)
	return prime1 * prime2;
}

DataType RSA::GetOrla(DataType prime1, DataType prime2)//ŷ��������
{
	//f(nm) = f(n)f(m) = (n-1)(m-1)
	return (prime1 - 1)*(prime2 - 1);
}

DataType RSA::GetEKey(DataType orla)//��ȡ������Կe
{
	//1 < e < f(n)
	rp::mt19937 gen((unsigned int)time(NULL));
	rp::uniform_int_distribution<DataType> dist(2, orla - 1);//��ȡһ��2--orla�Ĵ���
	
	//srand(time(NULL));
	DataType ekey;
	while (true)
	{
		ekey = dist(gen);
		//ekey = rand() % orla;//ģ��϶�С��f(n)
		if (GetGcd(ekey, orla) == 1)//1 < e < orla e��orla����(���Լ��=1)
		{
			return ekey;
		}
	}

}
DataType RSA::GetDKey(DataType ekey, DataType orla)//��ȡ������Կd
{
	// e * d % f(n) = 1  (f(n) = orla)
	DataType x, y;
	ExGcd(ekey, orla, x, y);
	//�任����˽Կd��һ���Ƚ�С��ֵ
	return (x % orla + orla) % orla;
}
DataType RSA::GetGcd(DataType data1, DataType data2)//��ȡ�����������Լ��
{
	//����ʱ��data1 >= data2
	if (data2 == 0)
	{
		return data1;
	}
	return GetGcd(data2, data1 % data2);
}

void RSA::GetKeys()
{
	std::ifstream ife(EKEYFILE, std::ifstream::binary);
	std::ifstream ifd(DKEYFILE, std::ifstream::binary);
	std::ifstream ifp(PKEYFILE, std::ifstream::binary);
	int pos = rand() % KEYS;//��ȡ�ڼ���Կ��
	std::cout << "pos = " << pos << std::endl;
	ife.clear();//����ϴε�ƫ�Ʊ�־
	ifd.clear();
	ifp.clear();

	ife.seekg(pos * LENGTH, std::ios::beg);//����ȡָ��ָ���pos��λ��
	ifd.seekg(pos * LENGTH, std::ios::beg);
	ifp.seekg(pos * LENGTH, std::ios::beg);

	ife.read((char*)&m_key.m_eKey, LENGTH);//������Կ�׶�ȡ�ļ��е�Կ��
	ifd.read((char*)&m_key.m_dKey, LENGTH);
	ifp.read((char*)&m_key.m_pKey, LENGTH);
	std::cout << "m_eKey = " << m_key.m_eKey << std::endl;
	std::cout << "m_dKey = " << m_key.m_dKey << std::endl;
	std::cout << "m_pKey = " << m_key.m_pKey << std::endl;
	ife.close();
	ifd.close();
	ifp.close();

	//DataType prime1 = GetPrime();
	//std::cout << "prime1 = " << prime1 << std::endl;
	//DataType prime2 = GetPrime();
	//while (prime1 == prime2)
	//{
	//	prime2 = GetPrime();
	//}
	//std::cout << "prime2 = " << prime2 << std::endl;

	//DataType orla = GetOrla(prime1, prime2);

	//m_key.m_pKey = GetPKey(prime1, prime2);
	//m_key.m_eKey = GetEKey(orla);
	//m_key.m_dKey = GetDKey(m_key.m_eKey, orla);
}

Key RSA::GetAllKey()//�����װ����˽�г�Ա�Ľӿ�
{
	return m_key;
}
//��˽Կ

//��ģ��Ԫ��(��Կe)
DataType RSA::ExGcd(DataType a, DataType b, DataType& x, DataType& y)
{
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	DataType gcd = ExGcd(b, a % b, x, y);
	DataType x1 = x;
	DataType y1 = y;
	x = y1;
	y = x1 - (a / b) * y1;
	return gcd;
}