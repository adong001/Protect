#include"Banker.h"

#define MAX_SOURCE 6 //�ɴ�ӡ�������Դ��
#define STATE 4 //����е�����
vector<vector<int>> Allocation;//ϵͳ���˽����ѷ�����Դ
vector<vector<int>> Need;//�˽��̻��������Դ
vector<vector<int>> Max;//�˽�����Ҫ�����Դ
vector<int> Available;//ϵͳ������Դ

void Dis_char(int i, char ch)
{
	while (i--)
	{
		cout << ch;
	}
}

void Display()
{
	char Name[] = "ABCDEFGH";
	int n = Need.size();//������
	int m = Need[0].size();//��Դ��
	int i, j, tmp;

	//1.��ӡ��ͷ
	printf("��ǰʱ����Դ�����\n");
	printf("|����������������������������������������������������������������������������������-|\n");
	printf("%-8s%-19s%-19s%-19s%-20s", "|��\\��Դ", "|       Max        ", "|    Allocation    ", "|       Need       ", "|     Available    |\n");
	printf("|   \\�� |������������������|������������������|������������������|������������������|\n");
	printf("|��  \\��");
	for (i = 0; i < STATE; i++)
	{
		cout << "|";
		for (j = 0; j < m; j++)
		{
			printf(" %c ", Name[j]);
		}
		tmp = MAX_SOURCE - m;//�������ÿո��ֲ�
		Dis_char(tmp * 3, ' ');
	}
	cout << "|\n";
	printf("|-------|������������������|������������������|������������������|������������������|\n");


	//2.��ӡÿһ��
	for (i = 0; i < n; i++)
	{
		printf("|  P%-2d  ", i);
		for (j = 0; j < m; j++)//Max����
		{
			cout << "|";
			for (j = 0; j < m; j++)
			{
				printf(" %d ", Max[i][j]);
			}
			tmp = MAX_SOURCE - m;//�������ÿո��ֲ�
			Dis_char(tmp * 3, ' ');
		}


		for (j = 0; j < m; j++)//Allcoation����
		{
			cout << "|";
			for (j = 0; j < m; j++)
			{
				printf(" %d ", Allocation[i][j]);
			}
			tmp = MAX_SOURCE - m;//�������ÿո��ֲ�
			Dis_char(tmp * 3, ' ');
		}

		for (j = 0; j < m; j++)//Need����
		{
			cout << "|";
			for (j = 0; j < m; j++)
			{
				printf(" %d ", Need[i][j]);
			}
			tmp = MAX_SOURCE - m;//�������ÿո��ֲ�
			Dis_char(tmp * 3, ' ');
		}


		cout << "|";
		for (j = 0; j < m; j++)//Available����
		{
			printf(" %d ", Available[j]);
		}
		tmp = MAX_SOURCE - m;//�������ÿո��ֲ�
		Dis_char(tmp * 3, ' ');

		cout << "|\n";
		printf("|-------|������������������|������������������|������������������|������������������|\n");
	}
}

bool operator <= (vector<int>& Request, vector<int>& Need)//�Ƚ��Ƿ�Request��С�ڵ���Need
{
	for (int i = 0; i < Request.size(); i++)
	{
		if (Request[i] > Need[i])
		{
			return false;
		}
	}
	return true;
}

bool operator ==(vector<int>& Need,int n)//Need��ÿһ�����0,
{
	for (auto& e : Need)
	{
		if (e != n)
		{
			return false;
		}
	}
	return true;
}


void Display_Security(pair<vector<int>, Status>& tmp)//��ʾ�Ƿ�ȫ
{
	if (tmp.second == SUCCESS)
	{
		cout << "��ȫ����Ϊ��";
		for (auto& e : tmp.first)
		{
			cout << "P" << e << "->";
		}
		cout << endl;
	}
	else
	{
		if (tmp.first.size() > 0)
		{
			for (auto& e : tmp.first)
			{
				cout << "P" << e << "->";
			}
			cout << "�ҵ�P" << tmp.first[tmp.first.size() - 1] << "���̺����Ҳ�����ȫ���У�\n";
		}
	}
	//Display_Security2(tmp.first);
}

//void Display_Security2(vector<int> res)
//{
//	char Name[] = "ABCDEFGH";
//	int n = Need.size();//������
//	int m = Need[0].size();//��Դ��
//	int i, j, tmp;
//
//	//1.��ӡ��ͷ
//	printf("��ǰʱ�̰�ȫ����\n");
//	printf("|��������������������������������������������������������������������������������������������-|\n");
//	printf("%-8s%-19s%-19s%-19s%-20s%-10s", "|��\\��Դ", "|       Work       ", "|    Allocation   ", "|       Need       ", "|  Work+Allocation", "|        |\n");
//	printf("|   \\�� |������������������|������������������|������������������|������������������-| Finish |\n");
//	printf("|��  \\��");
//	int m = 3;
//	int i, j, tmp;
//	char Name[] = "ABCDEFGH";
//	for (i = 0; i < 4; i++)
//	{
//		cout << "|";
//		for (j = 0; j < m; j++)
//		{
//			printf(" %c ", Name[j]);
//		}
//		tmp = 6 - m;//�������ÿո��ֲ�
//		Dis_char(tmp * 3, ' ');
//	}
//	cout << " |        |\n";
//	printf("|-------|������������������|������������������|������������������|������������������-|��������|\n");
//
//	//2.��ӡÿһ��
//	for (auto&e : res)
//	{
//		printf("|  P%-2d  ", e);
//		for (j = 0; j < m; j++)//Max����
//		{
//			cout << "|";
//			for (j = 0; j < m; j++)
//			{
//				printf(" %d ", Max[i][j]);
//			}
//			tmp = MAX_SOURCE - m;//�������ÿո��ֲ�
//			Dis_char(tmp * 3, ' ');
//		}
//
//
//		for (j = 0; j < m; j++)//Allcoation����
//		{
//			cout << "|";
//			for (j = 0; j < m; j++)
//			{
//				printf(" %d ", Allocation[i][j]);
//			}
//			tmp = MAX_SOURCE - m;//�������ÿո��ֲ�
//			Dis_char(tmp * 3, ' ');
//		}
//
//		for (j = 0; j < m; j++)//Need����
//		{
//			cout << "|";
//			for (j = 0; j < m; j++)
//			{
//				printf(" %d ", Need[i][j]);
//			}
//			tmp = MAX_SOURCE - m;//�������ÿո��ֲ�
//			Dis_char(tmp * 3, ' ');
//		}
//
//
//		cout << "|";
//		for (j = 0; j < m; j++)//Available����
//		{
//			printf(" %d ", Available[j]);
//		}
//		tmp = MAX_SOURCE - m;//�������ÿո��ֲ�
//		Dis_char(tmp * 3, ' ');
//
//		cout << "|\n";
//		printf("|-------|������������������|������������������|������������������|������������������|\n");
//	}
//}

void Init()
{
	pair<vector<int>, Status> retval;
	int PcbNum, Source;
	int i, j, tmp;
	cout << "������̵ĸ�����";
	cin >> PcbNum;
	cout << "������Դ�����ࣺ";
	cin >> Source;

	cout << "����ϵͳʣ����Դ(Available):";
	for (i = 0; i < Source; i++)
	{
		cin >> tmp;
		Available.push_back(tmp);
	}
	cout << endl;

	cout << "����Allocation����" << endl;

	for (i = 0; i < PcbNum; i++)
	{
		Allocation.push_back(vector<int>());
		Max.push_back(vector<int>());

		for (j = 0; j < Source; j++)
		{
			cin >> tmp;
			Allocation[i].push_back(tmp);
			Max[i].push_back(tmp);
		}
	}
	cout << endl;

	cout << "����Need����" << endl;

	for (i = 0; i < PcbNum; i++)
	{
		Need.push_back(vector<int>());

		for (j = 0; j < Source; j++)
		{
			cin >> tmp;
			Need[i].push_back(tmp);
			Max[i][j] += tmp;
		}
	}
	cout << "\n��ʼ�����!\n\n";
	cout << "���ϵͳ�Ƿ�ȫ.......\n";
	retval = AlgoSecurity();
	if (retval.second == SECURITY)
	{
		cout << "ϵͳ��ʱΪ��ȫ״̬\n";
		Display();
	}

	else
	{
		cout << "ϵͳ��ʱ���ڲ���ȫ״̬��������������Ƿ����\n";
	}

}

void Require()//����������Դ
{
	int Pid, tmp;
	vector<int>Requset;
	pair<vector<int>, Status> retval;

	cout << "����Ҫ��ϵͳ������Դ�Ľ���Id��";
	cin >> Pid;

	cout << "����Ҫ����ϵͳ������Դ�Ĵ�С��";
	for (int i = 0; i < Available.size(); i++)
	{
		cin >> tmp;
		Requset.push_back(tmp);
	}

	retval = AlgoBanker(Pid, Requset);

	switch (retval.second)
	{
	case NEED_REQUEST:cout << "\n����ʧ�ܣ��˽���������Դ������������������󣡣���\n\n"; break;
	case AVAILABLE_REQUEST:cout << "\n����ʧ�ܣ��˽���������Դ����ϵͳ��Դ������\n\n"; break;
	case SUCCESS:cout << "\n����ɹ���\n"; Display_Security(retval); break;
	case FAIL:cout << "\n����ʧ�ܣ��˴η���ᵼ��ϵͳ�����벻��ȫ״̬������\n"; Display_Security(retval); break;
	}
}


pair<vector<int>, Status> AlgoBanker(int Pid, vector<int>& Requset)//���м��㷨,�������Id����������С
{
	pair<vector<int>, Status> retval;//first---��ȫ���У�second---����״̬

	if (!(Requset <= Need[Pid]))//������������С
	{
		retval.second = NEED_REQUEST;
	}

	else if (!(Requset <= Available))//�������ϵͳӵ����Դ
	{
		retval.second = AVAILABLE_REQUEST;
	}

	else
	{
		for (int i = 0; i < Available.size(); i++)//���ŷ������
		{
			Available[i] -= Requset[i];
			Allocation[Pid][i] += Requset[i];
			Need[Pid][i] -= Requset[i];
		}
		retval = AlgoSecurity()

		if (retval.second == SECURITY)//�����ڰ�ȫ״̬
		{
			if (Need[Pid] == 0)//����������Դ������
			{
				for (int i = 0; i < Available.size(); i++)
				{
					Available[i] += Allocation[Pid][i];
				}
			}
			else//��������δ���(Need[Pid]!=0)�����ܻ���
			{
				//do nothing
			}
			retval.second = SUCCESS;//����ɹ�
		}
		else//����״̬�����η������ϣ��ظ�ԭ��״̬���˽��̵ȴ�
		{
			for (int i = 0; i < Available.size(); i++)
			{
				Available[i] += Requset[i];
				Allocation[Pid][i] -= Requset[i];
				Need[Pid][i] += Requset[i];
			}
			retval.second = FAIL;
		}
	}
	return retval;
}

pair<vector<int>, Status> AlgoSecurity()//��ȫ���㷨
{
	pair<vector<int>, Status> retval;//first---��ȫ���У�second---����״̬

	//�ٳ�ʼ����������
	vector<int> Work(Available);//��������
	vector<bool> Finish(Need.size(), false);//�ɷ����־
	int i, j;
	int flag;//ÿ�ҵ�һ���������㰲ȫ״̬��flag--������0˵��ϵͳ���ڰ�ȫ״̬
	int tag;

	//��,����
	while (1)
	{
		flag = count(Finish.begin(), Finish.end(), false);//flag��¼��ʱ���ܷ���Ľ��̸���
		tag = flag;//��¼flag��С

		for (i = 0; i < Need.size(); i++)
		{
			if (Need[i] <= Work && Finish[i] == false)//�ҵ�һ�������������������״̬��δ����
			{
				//��
				for (j = 0; j < Work.size(); j++)
				{
					Work[j] += Allocation[i][j];
				}
				Finish[i] = true;
				flag--;
				retval.first.push_back(i);//������id  push ����ȫ������
			}
		}

		//�� �����н���Finish==true,��ʾϵͳ��ȫ
		if (flag == 0)
		{
			retval.second = SECURITY;
			break;
		}

		//��������������ȫ
		if (tag == flag)
		{
			retval.second = UNSECURITY;
			break;
		}

		else //ѭ������
		{
			//do nothing
		}

	}
	return retval;

}