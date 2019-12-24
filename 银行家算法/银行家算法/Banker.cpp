#include"Banker.h"

#define MAX_SOURCE 6 //可打印的最大资源数
#define STATE 4 //表格中的四列
vector<vector<int>> Allocation;//系统给此进程已分配资源
vector<vector<int>> Need;//此进程还需分配资源
vector<vector<int>> Max;//此进程需要最大资源
vector<int> Available;//系统可用资源

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
	int n = Need.size();//进程数
	int m = Need[0].size();//资源数
	int i, j, tmp;

	//1.打印表头
	printf("当前时刻资源分配表\n");
	printf("|—————————————————————————————————————————-|\n");
	printf("%-8s%-19s%-19s%-19s%-20s", "|进\\资源", "|       Max        ", "|    Allocation    ", "|       Need       ", "|     Available    |\n");
	printf("|   \\情 |—————————|—————————|—————————|—————————|\n");
	printf("|程  \\况");
	for (i = 0; i < STATE; i++)
	{
		cout << "|";
		for (j = 0; j < m; j++)
		{
			printf(" %c ", Name[j]);
		}
		tmp = MAX_SOURCE - m;//超出的用空格弥补
		Dis_char(tmp * 3, ' ');
	}
	cout << "|\n";
	printf("|-------|—————————|—————————|—————————|—————————|\n");


	//2.打印每一行
	for (i = 0; i < n; i++)
	{
		printf("|  P%-2d  ", i);
		for (j = 0; j < m; j++)//Max数据
		{
			cout << "|";
			for (j = 0; j < m; j++)
			{
				printf(" %d ", Max[i][j]);
			}
			tmp = MAX_SOURCE - m;//超出的用空格弥补
			Dis_char(tmp * 3, ' ');
		}


		for (j = 0; j < m; j++)//Allcoation数据
		{
			cout << "|";
			for (j = 0; j < m; j++)
			{
				printf(" %d ", Allocation[i][j]);
			}
			tmp = MAX_SOURCE - m;//超出的用空格弥补
			Dis_char(tmp * 3, ' ');
		}

		for (j = 0; j < m; j++)//Need数据
		{
			cout << "|";
			for (j = 0; j < m; j++)
			{
				printf(" %d ", Need[i][j]);
			}
			tmp = MAX_SOURCE - m;//超出的用空格弥补
			Dis_char(tmp * 3, ' ');
		}


		cout << "|";
		for (j = 0; j < m; j++)//Available数据
		{
			printf(" %d ", Available[j]);
		}
		tmp = MAX_SOURCE - m;//超出的用空格弥补
		Dis_char(tmp * 3, ' ');

		cout << "|\n";
		printf("|-------|—————————|—————————|—————————|—————————|\n");
	}
}

bool operator <= (vector<int>& Request, vector<int>& Need)//比较是否Request都小于等于Need
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

bool operator ==(vector<int>& Need,int n)//Need的每一项都等于0,
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


void Display_Security(pair<vector<int>, Status>& tmp)//显示是否安全
{
	if (tmp.second == SUCCESS)
	{
		cout << "安全序列为：";
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
			cout << "找到P" << tmp.first[tmp.first.size() - 1] << "进程后再找不到安全序列！\n";
		}
	}
	//Display_Security2(tmp.first);
}

//void Display_Security2(vector<int> res)
//{
//	char Name[] = "ABCDEFGH";
//	int n = Need.size();//进程数
//	int m = Need[0].size();//资源数
//	int i, j, tmp;
//
//	//1.打印表头
//	printf("当前时刻安全序列\n");
//	printf("|——————————————————————————————————————————————-|\n");
//	printf("%-8s%-19s%-19s%-19s%-20s%-10s", "|进\\资源", "|       Work       ", "|    Allocation   ", "|       Need       ", "|  Work+Allocation", "|        |\n");
//	printf("|   \\情 |—————————|—————————|—————————|—————————-| Finish |\n");
//	printf("|程  \\况");
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
//		tmp = 6 - m;//超出的用空格弥补
//		Dis_char(tmp * 3, ' ');
//	}
//	cout << " |        |\n";
//	printf("|-------|—————————|—————————|—————————|—————————-|————|\n");
//
//	//2.打印每一行
//	for (auto&e : res)
//	{
//		printf("|  P%-2d  ", e);
//		for (j = 0; j < m; j++)//Max数据
//		{
//			cout << "|";
//			for (j = 0; j < m; j++)
//			{
//				printf(" %d ", Max[i][j]);
//			}
//			tmp = MAX_SOURCE - m;//超出的用空格弥补
//			Dis_char(tmp * 3, ' ');
//		}
//
//
//		for (j = 0; j < m; j++)//Allcoation数据
//		{
//			cout << "|";
//			for (j = 0; j < m; j++)
//			{
//				printf(" %d ", Allocation[i][j]);
//			}
//			tmp = MAX_SOURCE - m;//超出的用空格弥补
//			Dis_char(tmp * 3, ' ');
//		}
//
//		for (j = 0; j < m; j++)//Need数据
//		{
//			cout << "|";
//			for (j = 0; j < m; j++)
//			{
//				printf(" %d ", Need[i][j]);
//			}
//			tmp = MAX_SOURCE - m;//超出的用空格弥补
//			Dis_char(tmp * 3, ' ');
//		}
//
//
//		cout << "|";
//		for (j = 0; j < m; j++)//Available数据
//		{
//			printf(" %d ", Available[j]);
//		}
//		tmp = MAX_SOURCE - m;//超出的用空格弥补
//		Dis_char(tmp * 3, ' ');
//
//		cout << "|\n";
//		printf("|-------|—————————|—————————|—————————|—————————|\n");
//	}
//}

void Init()
{
	pair<vector<int>, Status> retval;
	int PcbNum, Source;
	int i, j, tmp;
	cout << "输入进程的个数：";
	cin >> PcbNum;
	cout << "输入资源的种类：";
	cin >> Source;

	cout << "输入系统剩余资源(Available):";
	for (i = 0; i < Source; i++)
	{
		cin >> tmp;
		Available.push_back(tmp);
	}
	cout << endl;

	cout << "输入Allocation矩阵" << endl;

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

	cout << "输入Need矩阵" << endl;

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
	cout << "\n初始化完毕!\n\n";
	cout << "检测系统是否安全.......\n";
	retval = AlgoSecurity();
	if (retval.second == SECURITY)
	{
		cout << "系统此时为安全状态\n";
		Display();
	}

	else
	{
		cout << "系统此时处于不安全状态，请检查你的数据是否合理\n";
	}

}

void Require()//进程请求资源
{
	int Pid, tmp;
	vector<int>Requset;
	pair<vector<int>, Status> retval;

	cout << "输入要想系统请求资源的进程Id：";
	cin >> Pid;

	cout << "输入要想向系统请求资源的大小：";
	for (int i = 0; i < Available.size(); i++)
	{
		cin >> tmp;
		Requset.push_back(tmp);
	}

	retval = AlgoBanker(Pid, Requset);

	switch (retval.second)
	{
	case NEED_REQUEST:cout << "\n分配失败！此进程所需资源超过它宣布的最大需求！！！\n\n"; break;
	case AVAILABLE_REQUEST:cout << "\n分配失败！此进程所需资源超过系统资源！！！\n\n"; break;
	case SUCCESS:cout << "\n分配成功！\n"; Display_Security(retval); break;
	case FAIL:cout << "\n分配失败！此次分配会导致系统进出入不安全状态！！！\n"; Display_Security(retval); break;
	}
}


pair<vector<int>, Status> AlgoBanker(int Pid, vector<int>& Requset)//银行家算法,传入进程Id和请求分配大小
{
	pair<vector<int>, Status> retval;//first---安全序列，second---分配状态

	if (!(Requset <= Need[Pid]))//请求大于所需大小
	{
		retval.second = NEED_REQUEST;
	}

	else if (!(Requset <= Available))//请求大于系统拥有资源
	{
		retval.second = AVAILABLE_REQUEST;
	}

	else
	{
		for (int i = 0; i < Available.size(); i++)//试着分配给他
		{
			Available[i] -= Requset[i];
			Allocation[Pid][i] += Requset[i];
			Need[Pid][i] -= Requset[i];
		}
		retval = AlgoSecurity()

		if (retval.second == SECURITY)//若处于安全状态
		{
			if (Need[Pid] == 0)//不在需求资源，回收
			{
				for (int i = 0; i < Available.size(); i++)
				{
					Available[i] += Allocation[Pid][i];
				}
			}
			else//这次请求后还未完成(Need[Pid]!=0)，不能回收
			{
				//do nothing
			}
			retval.second = SUCCESS;//分配成功
		}
		else//不是状态，本次分配作废，回复原来状态。此进程等待
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

pair<vector<int>, Status> AlgoSecurity()//安全性算法
{
	pair<vector<int>, Status> retval;//first---安全序列，second---分配状态

	//①初始化两个向量
	vector<int> Work(Available);//工作向量
	vector<bool> Finish(Need.size(), false);//可分配标志
	int i, j;
	int flag;//每找到一个进程满足安全状态，flag--，减到0说明系统出于安全状态
	int tag;

	//②,查找
	while (1)
	{
		flag = count(Finish.begin(), Finish.end(), false);//flag记录暂时不能分配的进程个数
		tag = flag;//记录flag大小

		for (i = 0; i < Need.size(); i++)
		{
			if (Need[i] <= Work && Finish[i] == false)//找到一个进程满足分配需求且状态是未分配
			{
				//③
				for (j = 0; j < Work.size(); j++)
				{
					Work[j] += Allocation[i][j];
				}
				Finish[i] = true;
				flag--;
				retval.first.push_back(i);//将进程id  push 进安全序列中
			}
		}

		//④ ，所有进程Finish==true,表示系统安全
		if (flag == 0)
		{
			retval.second = SECURITY;
			break;
		}

		//进入死锁，不安全
		if (tag == flag)
		{
			retval.second = UNSECURITY;
			break;
		}

		else //循环查找
		{
			//do nothing
		}

	}
	return retval;

}