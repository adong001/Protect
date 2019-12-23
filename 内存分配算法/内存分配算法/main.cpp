#include"内存分配算法.h"

int main()
{
	int choose;
	/*map<int, string, greater<int>> m;
	m.insert(make_pair(3, "C"));
	m.insert(make_pair(1, "A"));
	m.insert(make_pair(7, "E"));
	m.insert(make_pair(2, "B"));
	m.insert(make_pair(5, "D"));
	for (auto& e : m)
	{
		cout << e.first << " " << e.second << endl;
	}*/

	while (1)
	{
		cout << "请选择实现的算法：" << endl;
		cout << "*****  1 - 首次适应算法     *****" << endl;
		cout << "*****  2 - 循环首次适应算法 *****" << endl;
		cout << "*****  3 - 最佳适应算法     *****" << endl;
		cout << "*****  4 - 最坏适应算法     *****" << endl;
		cout << "*****  0 - 结束             *****" << endl;
		cout << "输入你的选择 ： ";
		cin >> choose;
		switch (choose)
		{
			
			case 0:exit(0); break;
			case 1:FirstFit(); break;
			case 2:NextFit(); break;
			case 3:BestFit(); break;
			case 4:WorstFit(); break;
			default:cout << "请输入正确的序号：" << endl;
		}
	}
    system("pause");
    return 0;
}