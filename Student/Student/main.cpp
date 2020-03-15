#define _CRT_SECURE_NO_WARNINGS 1
#include"Student.h"

int main()  //主程序
{
	student a;
	int x1, x2;

	do
	{
		a.menue();//主菜单
		cout << "请选择你的操作:";
		cin >> x1;//输入选项
		switch (x1)//主菜单选择
		{
		case 1:
			a.add2();
			break;
		case 2:
		{
				  a.grade();
				  fstream file("b.txt", ios::out | ios::app); //打开文件，指针指向文件尾
				  file.write((char*)&a, sizeof(a));//把类信息写入文件
				  file.close();
				  cout << "信息已经保存" << endl;
				  break;
		}
		case 3:
			do
			{
				a.reader();
				cout << "请输入操作号：";
				cin >> x2;
				switch (x2)
				{
				case 1:
					a.searchname();
					break;
				case 2:
					a.searchnumber();
					break;
				case 3:
					a.searchroom();
					break;
				}
			} while (x2 != 4); break;

		case 4:
			a.searchgrade();
			break;
		case 5:
			a.paixu();
			break;
		}

	} while (x1 != 6);
	cout << "************************ 成功退出本系统！！！********************************";
	cout << endl;
	return 0;
}