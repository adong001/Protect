#include"rsa.h"

//产生钥匙文件
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

void RSA::Encrypt(const char* filename,const char* fileout)//文件加密
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
		fin.read(bufferin, NUMBER);//每次读NUMBER个字节的数据
		curNum = fin.gcount();//真正读到的字节数，有可能后面读到空
		int i;
		std::cout << "m_eKey = " << m_key.m_eKey << std::endl;
		std::cout << "m_dKey = " << m_key.m_dKey << std::endl;
		std::cout << "m_pKey = " << m_key.m_pKey << std::endl;
		for (i = 0; i < curNum; i++)
		{
			
			bufferout[i] = Encrypt((DataType)bufferin[i], m_key.m_eKey, m_key.m_pKey);
			//每次将一个字节加密成一个DataType型，写入bufferout缓冲区中
			std::cout << bufferin[i] << "  被加密成  " << bufferout[i] << std::endl;
		}
		fout.write((char*)bufferout, curNum * LENGTH);
		//因为每次将一个字节加密成一个DataType型，共加密curNum次，bufferout每个元素大小为length
		//所以要向fout写入curNum * length个字节
	}
	fin.close();
	fout.close();
}

void RSA::Decrypt(const char* filename, const char* fileout)//文件解密
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
		fin.read((char*)bufferin, NUMBER * LENGTH);//每次读NUMBER个DataType字节的数据
		curNum = fin.gcount();//真正读到的字节数，有可能后面读到空
		curNum /= LENGTH;//真正读到curNum个DataType字节的数据，下面就解密curNum次
		int i;
		std::cout << "-----------------\n";
		std::cout << "m_eKey = " << m_key.m_eKey << std::endl;
		std::cout << "m_dKey = " << m_key.m_dKey << std::endl;
		std::cout << "m_pKey = " << m_key.m_pKey << std::endl;
		for (i = 0; i < curNum; i++)
		{
			//每次以datatype为单位进行解密，curnum个datatype字节的数据，共解密curnum次
			//每次将一个datatype为单位的数据解密成一个字节的数据，写入bufferout缓冲区中
			bufferout[i] = (char)Encrypt(bufferin[i], m_key.m_dKey, m_key.m_pKey);
			std::cout << bufferin[i] << "  被解密成  " << bufferout[i] << std::endl;
		}
		fout.write(bufferout, curNum);
		//解密curNum次，就得到curNum字节得数据，写入fout文件中
	}
	fin.close();
	fout.close();
}

DataType RSA::Encrypt(DataType data, DataType ekey, DataType pkey)//加密函数
{
	//msgE-->密文，data-->明文，ekey-->公钥，pkey-->n
	/*加密：msgE = (data^ekey)% pkey 
				 = ((data^(b0*2^0) * data^(b1*2^1)*......*data^(bn*2^n))% pkey 
	             = ((data^(2^i)) *......*(data^(2^n)))% pkey  //i代表data 比特位为1的位数
				 = (((data^(2^i)) % pkey) *......*((data^(2^n)) % pkey))% pkey
令Ai = (data^(2^i))% pkey
  An = (data^(2^n))% pkey
     = (data^(2^(n-1))% pkey * data^(2^(n-1))% pkey)% pkey
	 = (An-1 * An-1) %pkey
				 = (Ai * ......* An);
				 这样每次都%pkey，就不会产生数据溢出
	*/
	DataType Ai = data;
	DataType msgE = 1;
	//data^ekey % pkey
	while (ekey)
	{
		if (ekey & 1)//取出比特位为1的
		{
			msgE = (msgE * Ai) % pkey;//msgE = 叠乘Ai ,第一个Ai = data^ 2^ i % pkey
		}
		ekey >>= 1;//取下一位
		Ai = (Ai * Ai) % pkey; //Ai+1 = (Ai * Ai) % pkey
	}
	return msgE;//密文
}

DataType RSA::Decrypt(DataType data, DataType dkey, DataType pkey)//解密函数
{
	//msgE-->明文，data-->密文，dkey-->私钥，pkey-->n
	//解密：msgE = (data^dkey)%n 
	return Encrypt(data, dkey, pkey);
}


DataType RSA::GetPrime()//获取素数
{
	rp::mt19937 gen((unsigned int)time(NULL));
	rp::uniform_int_distribution<DataType> dist(2, DataType(1) << OFFSET);
	//随机获取一个128位的大数  
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

bool RSA::IsPrime(DataType data)//判断是否为素数
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
DataType RSA::GetPKey(DataType prime1, DataType prime2)//获取n
{
	//f(n) = f(p1*p2)
	return prime1 * prime2;
}

DataType RSA::GetOrla(DataType prime1, DataType prime2)//欧拉函数，
{
	//f(nm) = f(n)f(m) = (n-1)(m-1)
	return (prime1 - 1)*(prime2 - 1);
}

DataType RSA::GetEKey(DataType orla)//获取加密秘钥e
{
	//1 < e < f(n)
	rp::mt19937 gen((unsigned int)time(NULL));
	rp::uniform_int_distribution<DataType> dist(2, orla - 1);//获取一个2--orla的大数
	
	//srand(time(NULL));
	DataType ekey;
	while (true)
	{
		ekey = dist(gen);
		//ekey = rand() % orla;//模后肯定小于f(n)
		if (GetGcd(ekey, orla) == 1)//1 < e < orla e与orla互质(最大公约数=1)
		{
			return ekey;
		}
	}

}
DataType RSA::GetDKey(DataType ekey, DataType orla)//获取解密秘钥d
{
	// e * d % f(n) = 1  (f(n) = orla)
	DataType x, y;
	ExGcd(ekey, orla, x, y);
	//变换，让私钥d是一个比较小的值
	return (x % orla + orla) % orla;
}
DataType RSA::GetGcd(DataType data1, DataType data2)//获取两个数的最大公约数
{
	//传的时候data1 >= data2
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
	int pos = rand() % KEYS;//获取第几个钥匙
	std::cout << "pos = " << pos << std::endl;
	ife.clear();//清除上次的偏移标志
	ifd.clear();
	ifp.clear();

	ife.seekg(pos * LENGTH, std::ios::beg);//将读取指针指向第pos个位置
	ifd.seekg(pos * LENGTH, std::ios::beg);
	ifp.seekg(pos * LENGTH, std::ios::beg);

	ife.read((char*)&m_key.m_eKey, LENGTH);//给各个钥匙读取文件中的钥匙
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

Key RSA::GetAllKey()//对外封装访问私有成员的接口
{
	return m_key;
}
//求私钥

//求模范元素(公钥e)
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