#include"Banker.h"

int main()
{

	int choose;
	
	while (1)
	{
		cout << "           ���м��㷨��" << endl<<endl;
		cout << "*****  1 - ��ʼ��������        *****" << endl;
		cout << "*****  2 - �����������        *****" << endl;
		cout << "*****  3 - ��ʾ��������Դ���  *****" << endl;
		cout << "*****  0 - ����                *****" << endl << endl;
		cout << "�������ѡ�� �� ";
		cin >> choose;
		switch (choose)
		{

		case 0:exit(0); break;
		case 1:Init(); break;
		case 2:Require(); break;
		case 3:Display(); break;
		default:cout << "��������ȷ����ţ�" << endl;
		}
	}
    system("pause");
    return 0;
}