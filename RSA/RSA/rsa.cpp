#include"rsa.h"

void RSA::ProdureKeyFile(const char* ekey_file, const char* dkey_file, const char* pkey_file)//����Կ���ļ�
{
	int keys = 3;
	int length = sizeof(DataType);
	ofstream fe(ekey_file);
	ofstream fd(dkey_file);
	ofstream fp(pkey_file);

	while (keys--)
	{
		DataType prime1 = GetPrime();
		DataType prime2 = GetPrime();
		while (prime1 == prime2)
		{
			prime2 = GetPrime();
		}
		DataType orla = GetOrla(prime1, prime2);
		DataType pKey = GetPKey(prime1, prime2);
		DataType eKey = GetEKey(orla);
		DataType dKey = GetDKey(m_key.m_eKey, orla);
		fe.write((char*)&eKey, length);
		fd.write((char*)&dKey, length);
		fp.write((char*)&pKey, length);
	}
	fe.close();
	fd.close();
	fp.close();
}

void RSA::Encrypt(const char* filename, const char* fileout)//�ļ�����
{
	//DataType m_eKey("512978033300805572280865");
	//DataType m_pKey("982348807953060486445057");
	//DataType m_dKey("123192531317109461264545");
	//DataType original = 'h';
	//DataType decout = Encrypt(original, m_eKey, m_pKey);
	//cout << "original:" << original << endl;
	//cout << "ecrept:" << decout << endl;
	//cout << "decrept:" << Decrypt(decout, m_dKey, m_dKey);
	//cout << endl << endl;

	//original = 'e';
	//decout = Encrypt(original,m_eKey, m_pKey);
	//cout << "original:" << original << endl;
	//cout << "ecrept:" << decout << endl;
	//cout << "decrept:" <<Decrypt(decout,m_dKey,m_pKey);
	//cout << endl << endl;

 //    original = 'l';
 //    decout = Encrypt(original,m_eKey, m_pKey);
	//cout << "original:" << original << endl;
	//cout << "ecrept:" << decout << endl;
	//cout << "decrept:" <<Decrypt(decout,m_dKey,m_pKey);
	//cout << endl << endl;


	ifstream fin(filename, ifstream::binary);
	ofstream fout(fileout, ofstream::binary);
	if (!fin.is_open())
	{
		perror("input file open failed\n");
		return;
	}
	
	int length = sizeof(DataType);
	char* bufferin = new char[NUMBER]; 
	DataType* bufferout = new DataType[NUMBER];
	int curNum;

	while (!fin.eof())
	{
		fin.read(bufferin, NUMBER);//ÿ�ζ�NUMBER���ֽڵ�����
		curNum = fin.gcount();//�����������ֽ������п��ܺ��������
		int i;
		for (i = 0; i < curNum; i++)
		{
			
			bufferout[i] = Encrypt((DataType)bufferin[i], m_key.m_eKey, m_key.m_pKey);
			//ÿ�ν�һ���ֽڼ��ܳ�һ��DataType�ͣ�д��bufferout��������
			cout << bufferin[i] << endl;
			cout << bufferout[i]  << endl;
		}
		//cout << endl;
		//cout << bufferout[0] << endl;
		//cout << bufferout[1] << endl;
		//cout << bufferout[2] << endl;
		//cout << bufferout[3] << endl;
		//cout << bufferout[4] << endl;
		//
		fout.write((char*)(bufferout), curNum * length);
		//��Ϊÿ�ν�һ���ֽڼ��ܳ�һ��DataType�ͣ�������curNum�Σ�bufferoutÿ��Ԫ�ش�СΪlength
		//����Ҫ��foutд��curNum * length���ֽ�
	}
	delete[] bufferin;
	delete[] bufferout;
	fin.close();
	fout.close();
}

void RSA::Decrypt(const char* filename, const char* fileout)//�ļ�����
{

	ifstream fin(filename, ifstream::binary);
	ofstream fout(fileout, ofstream::binary);
	if (!fin.is_open())
	{
		perror("input file open failed\n");
		return;
	}	
	
	int length = sizeof(DataType);
	int curNum;

    DataType* bufferin = new DataType[NUMBER];
	char* bufferout = new char[NUMBER];

	while (!fin.eof())
	{
		fin.read((char*)bufferin, NUMBER * length);//ÿ�ζ�NUMBER��DataType�ֽڵ�����
		cout << bufferin[0] << endl;
		curNum = fin.gcount();//�����������ֽ������п��ܺ��������
		curNum /= length;//��������curNum��DataType�ֽڵ����ݣ�����ͽ���curNum��
		int i;
		cout << "\n\n\n";
		for (i = 0; i < curNum; i++)
		{
			//ÿ����datatypeΪ��λ���н��ܣ�curnum��datatype�ֽڵ����ݣ�������curnum��
			//ÿ�ν�һ��datatypeΪ��λ�����ݽ��ܳ�һ���ֽڵ����ݣ�д��bufferout��������
			bufferout[i] = (char)Decrypt(bufferin[i], m_key.m_dKey, m_key.m_pKey);
			cout << bufferin[i] << endl;
			cout << bufferout[i] << endl;
		}
		cout << endl;
		cout << bufferout[0] << endl;
		cout << bufferout[1] << endl;
		cout << bufferout[2] << endl;
		cout << bufferout[3] << endl;
		cout << bufferout[4] << endl;
		fout.write(bufferout, curNum);
		//����curNum�Σ��͵õ�curNum�ֽڵ����ݣ�д��fout�ļ���
	}
	delete[] bufferin;
	delete[] bufferout;
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
	rp::mt19937 gen(time(NULL));
	rp::uniform_int_distribution<DataType> dist(2, DataType(1) << OFFSET);
	//�����ȡһ��128λ�Ĵ���
	srand(time(NULL));  
	DataType prime;
	while (true)
	{
		prime = dist(gen);
		if (IsPrime(prime))
		{
			break;
		}
	}
	cout << "prime = " << prime << endl;
	return prime;
}

bool RSA::IsPrime(DataType data)//�ж��Ƿ�Ϊ����
{
	rp::mt11213b gen(time(nullptr));
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
	rp::mt19937 gen(time(NULL));
	rp::uniform_int_distribution<DataType> dist(2,orla);//��ȡһ��2--orla�Ĵ���
	
	//srand(time(NULL));
	DataType ekey;
	while (true)
	{
		ekey = dist(gen);
		//ekey = rand() % orla;//ģ��϶�С��f(n)
		if (ekey > 1 && GetGcd(ekey, orla) == 1)//1 < e < orla e��orla����(���Լ��=1)
		{
			return ekey;
		}
	}

}
DataType RSA::GetDKey(DataType ekey, DataType orla)//��ȡ������Կd
{
	// e * d % f(n) = 1  (f(n) = orla)
	DataType x(0);
	DataType y(0);
	ExGcd(ekey, orla, x, y);
	//�任����˽Կd��һ���Ƚ�С��ֵ
	return (x % orla + orla) % orla;
	/*DataType dkey = orla / ekey;
	while (true)
	{
		if ((dkey * ekey) % orla == 1)
		{
			return dkey;
		}
		++dkey;
	}
	return dkey;*/
	
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
	DataType prime1 = GetPrime();
	DataType prime2 = GetPrime();
	while (prime1 == prime2)
	{
		prime2 = GetPrime();
	}

	DataType orla = GetOrla(prime1, prime2);

	m_key.m_pKey = GetPKey(prime1, prime2);
	m_key.m_eKey = GetEKey(orla);
	m_key.m_dKey = GetDKey(m_key.m_eKey, orla);
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