#include"bigint.h"

BigInt::BigInt(const string& num) //���캯��
{}


BigInt::BigInt(const int num)//���캯��
{

}

string BigInt::add(string num1, string num2)
{
	int len1 = num1.size();
	int len2 = num2.size();
	string ret;
	if (len1 == 1 && num1[0] == '0' || len2 == 1 && num2[0] == '0')
		//һ������0,���������һ������ֵ����΢���Ч��
	{
		return num1[0] == '0' ? num2 : num1;
	}


	if (num1[0] == '-' && num2[0] == '-')//����
	{
		string s1(num1.begin() + 1, num1.end());
		string s2(num2.begin() + 1, num2.end());
		ret += '-';
		ret += add(s1, s2);//����������� == ���Ǿ���ֵ�����ȡ��
		return ret;
	}

	if (num1[0] == '-' && num2[0] != '-')//����������
	{
		string tmp;
		if (num1[0] == '-')//num1Ϊ����
		{
			tmp.append(num1.begin() + 1, num1.end());
			return sub(num2, tmp);//��������� == ���� - �����ľ���ֵ
		}
		else
		{
			tmp.append(num2.begin() + 1, num2.end());
			return sub(num1, tmp);//��������� == ���� - �����ľ���ֵ
		}
	}

	//����
	if (num1.size() < num2.size())//��num1���ϴ����
	{
		swap(num1, num2);
		swap(len1, len2);
	}

	ret.resize(len1);
	int step = 0;//��λ
	int i, j, tmp;

	for (i = len1 - 1, j = len2 - 1; i >= 0; --i)
	{
		if (j >= 0)//��С������δ����
		{
			tmp = num1[i] + num2[j] + step - 2 * '0';
			--j;
		}
		else
		{
			tmp = num1[i] + step - '0';
		}
		ret[i] = tmp % 10 + '0';
		step = tmp / 10;
	}
	if (step == 1)
	{
		ret.insert(0, 1, '1');//�����λ���Ͻ�λ��ֻ�ܽ�1
	}
	return ret;

}

string BigInt::sub(string num1, string num2)
{
	string ret;
	int len1 = num1.size();
	int len2 = num2.size();

	if (len1 == 1 && num1[0] == '0')//num1Ϊ0ʱ
	{
		if (num2[0] == '-')//num2Ϊ����ʱ
		{
			ret.append(num2.begin() + 1, num2.end());//0-����=�����ľ���ֵ
			return ret;
		}
		else
		{
			return  num2;
		}
	}

	else if (len2 == 1 && num2[0] == '0')//num2Ϊ0ʱ
	{
		return  num1;
	}


	else if (num1[0] == '-' && num2[0] != '-') //�� - �� = -(|��|+��)
	{
		string tmp(num1.begin() + 1, num1.end());
		ret += '-';
		ret += add(tmp, num2);
		return ret;
	}

	else if (num1[0] != '-' && num2[0] == '-') //�� - �� = |��| + ��
	{
		string tmp(num2.begin() + 1, num2.end());
		return add(num1,tmp);
	}


	else if (num1[0] == '-' && num2[0] == '-')//����  ��1 - ��2 = |��2| -|��1|
	{
		string s1(num1.begin()+ 1, num1.end()); //��1�ľ���ֵ
		string s2(num2.begin()+ 1, num2.end()); //��2�ľ���ֵ

		//return sub(s2,s1);//�˴�ֱ�ӵݹ�Ҳ����(�ݹ��ȥ���ܳ���С-�󻹻��һ��ջ)����������ķ�������һ��
		if (len1 > len2 || len1 == len2 && num1 > num2)//��1�ľ���ֵ > ��2�ľ���ֵ,����ɸ������ȼ���-(|��1|-|��2|)
		{
			ret += '-';
			ret += sub(s1, s2);
			return ret;
		}
		else//��2�ľ���ֵ >= ��1�ľ���ֵ
		{
			return sub(s2, s1);
		}
	}

	else if (num1[0] != '-' && num2[0] != '-')//����
	{
		if (len1 < len2 || len1 == len2 && num1 < num2)//С - �� = -(�� - С)
		{
			ret += '-';
			ret += sub(num2, num1);
			return ret;
		}


		else
		{
			ret.resize(len1); //����������ֻ�����ǣ���1 - ��2 && ��1 > ��2
			int step = 0;//��λ
			int i, j, tmp;

			for (i = len1 - 1, j = len2 - 1; i >= 0; --i)
			{
				tmp = 0;
				if (j >= 0)//��С������δ����
				{
					if (num1[i] < num2[j])//��Ҫ��λ
					{
						tmp = 10;//����һλ��һλ���൱��+10
						num1[i - 1]--;//���Ͻ�λ��һλ-1
					}
					ret[i] = num1[i] + tmp - num2[j] + '0';
					--j;
				}

				else
				{
					if (num1[i] < '0')
					{
						ret[i] = num1[i] + 10;
						--num1[i - 1];
					}
					else
					{
						ret[i] = num1[i];
					}
				}

			}
			//ɾ��ǰ��0,����0008---��8
			while (ret.size() > 1 && ret[0] == '0')
			{
				ret.erase(0, 1);//����ɾ��ͷ����0
			}
			return ret;
		}
	}
}

string BigInt::mul(string num1, string num2)
{
	string ret;
	int len1 = num1.size();
	int len2 = num2.size();
	if (len1 == 1 || len2 == 1)
	{
		if (len1 == 1 && num1[0] == '0' || len2 == 1 && num2[0] == '0')//�κ�������0=0
		{
			return ret;
		}

		if (len1 == 1 && num1[0] == '1' || len2 == 1 && num2[0] == '1')//�κ�������1=�κ���
		{
			return num1[0] == '1' ? num2 : num1;
		}
	}

	if (len1 == 2 && num1[0] == '-'&& num1[1] == '1')//num1==-1
	{
		if (num2[0] == '-')
		{
			ret.append(num2.begin() + 1, num2.end());
			return ret;
		}
		else
		{
			ret += '-';
			ret.append(num2.begin(), num2.end());
			return ret;
		}
	}

	if (len1 == 2 && num1[0] == '-'&& num1[1] == '1')//num2==-1
	{
		if (num1[0] == '-')
		{
			ret.append(num1.begin() + 1, num1.end());
			return ret;
		}
		else
		{
			ret += '-';
			ret.append(num1.begin(), num1.end());
			return ret;
		}
	}

	string s1, s2;

	if (num1[0] == '-' && num2[0] == '-')//���� ����
	{
		s1.append(num1.begin() + 1, num1.end());
		s2.append(num2.begin() + 1, num2.end());
		return mul(s1, s2);
	}

	else if (num1[0] == '-' || num2[0] == '-')//����/����
	{	
		if (num1[0] == '-')
		{
			s1.append(num1.begin() + 1, num1.end());
			s2 = num2;
		}
		else
		{
			s1 = num1;
			s2.append(num2.begin() + 1, num2.end());
		}
		ret += '-';
		ret += mul(s1, s2);
		return ret;
	}

	else //if (num1[0] != '-' && num2[0] != '-')//����
	{

		if (num1.size() < num2.size())//��num1���ϴ����
		{
			swap(num1, num2);
			swap(len1, len2);
		}

		ret = "0";
		for (int i = len2 - 1; i >= 0; --i)
		{
			int digit = num2[i] - '0';//��õ�ǰ������Ӧλ��ֵ
			int step = 0;//��λ

			string tmp = num1;//��ǰ�˻����
			for (int j = len1 - 1; j >= 0; --j)
			{
				tmp[j] = (tmp[j] - '0') * digit + step;//����ֵ

				if (tmp[j] > 9)
				{
					step = tmp[j] / 10;
					tmp[j] %= 10;
				}

				else//û�н�λ
				{
					step = 0;
				}
				tmp[j] += '0';//��ԭ���ַ�

			}
			if (step > 0)//�ж������һλ�Ƿ�Ҫ��λ
			{
				tmp.insert(0, 1, step + '0');
			}
			tmp.append(len2 - 1 - i, '0');

			//�����ۼ�һ�γ˷��Ľ��
			ret = add(ret, tmp);
		}
		return ret;
	}
}

bool BigInt::less(string num1, string num2)
{
	if (num1.size() < num2.size())
	{
		return true;
	}
	if (num1.size() > num2.size())
	{
		return false;
	}
	//������ͬʱ
	return num1 < num2;
}




pair<string, string> BigInt::div(string num1, string num2)//���������̺�����
{
	//��������ʵ��-->105/2 = 105-20-20-20-20-20  ��=���Ĵ���������=���ܼ�����
	
	//pair<string, string> ret;
	string ret;//��
	string rem = num1;//����

	int diffNum = num1.size() - num2.size();//���������зŴ󣬰���10�ı����Ŵ�
	num2.append(diffNum, '0');
	for (int i = 0; i < diffNum; ++i)
	{
		//��¼����ִ�еĴ���
		char count = '0';
		while (true)
		{
			if (less(0, num2))//����С�ڳ���
			{
				break;
			}
			rem = sub(rem, num2);
			++count;
		}
		ret += count;
		//������С10��
		num2.pop_back();
	}

	//ɾ��ǰ�õ�0
	while (ret.size() > 1 && ret[0] == '0')
	{
		ret.erase(0, 1);
	}
	
	return make_pair(ret,rem);
}


BigInt BigInt::operator+(BigInt& bi)
{
	string ret = add(m_number, bi.m_number);
	return BigInt(ret);
}

BigInt BigInt::operator-(BigInt& bi)
{
	string ret = sub(m_number, bi.m_number);
	return BigInt(ret);
}

BigInt BigInt::operator*(BigInt& bi)
{
	string ret = mul(m_number, bi.m_number);
	return BigInt(ret);
}

BigInt BigInt::operator/(BigInt& bi)
{
	string ret = div(m_number, bi.m_number).first;
	return BigInt(ret);
}

BigInt BigInt::operator%(BigInt& bi)
{
	string ret = div(m_number, bi.m_number).second;
	return BigInt(ret);
}

ostream& operator<<(ostream& os, BigInt& bi)
{
	os << bi.m_number;
	return os;
}
istream& operator>>(istream& is, BigInt& bi)
{
	is >> bi.m_number;
	return is;
}
//BigInt operator+(BigInt& bi);
//BigInt operator-(BigInt& bi);
//BigInt operator*(BigInt& bi);
//BigInt operator/(BigInt& bi);
//BigInt operator%(BigInt& bi);
//
//BigInt& operator+=(BigInt& bi);
//BigInt& operator-=(BigInt& bi);
//BigInt& operator*=(BigInt& bi);
//BigInt& operator/=(BigInt& bi);
//BigInt& operator%=(BigInt& bi);
//
//BigInt& operator++();
//BigInt operator++(int);//����
//BigInt& operator--();
//BigInt operator--(int);//����
//
//friend ostream& operator<<(ostream& os, BigInt& bi);
//friend istream& operator>>(istream& is, BigInt& bi);