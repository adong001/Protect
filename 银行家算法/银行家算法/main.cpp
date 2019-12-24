#include"Banker.h"

int main()
{

	int choose;
	
	while (1)
	{
		cout << "           银行家算法：" << endl<<endl;
		cout << "*****  1 - 初始化各矩阵        *****" << endl;
		cout << "*****  2 - 进程提出请求        *****" << endl;
		cout << "*****  3 - 显示各进程资源情况  *****" << endl;
		cout << "*****  0 - 结束                *****" << endl << endl;
		cout << "输入你的选择 ： ";
		cin >> choose;
		switch (choose)
		{

		case 0:exit(0); break;
		case 1:Init(); break;
		case 2:Require(); break;
		case 3:Display(); break;
		default:cout << "请输入正确的序号：" << endl;
		}
	}
    system("pause");
    return 0;
}