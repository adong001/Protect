#define _CRT_SECURE_NO_WARNINGS 1
#include"Student.h"

int main()  //������
{
	student a;
	int x1, x2;

	do
	{
		a.menue();//���˵�
		cout << "��ѡ����Ĳ���:";
		cin >> x1;//����ѡ��
		switch (x1)//���˵�ѡ��
		{
		case 1:
			a.add2();
			break;
		case 2:
		{
				  a.grade();
				  fstream file("b.txt", ios::out | ios::app); //���ļ���ָ��ָ���ļ�β
				  file.write((char*)&a, sizeof(a));//������Ϣд���ļ�
				  file.close();
				  cout << "��Ϣ�Ѿ�����" << endl;
				  break;
		}
		case 3:
			do
			{
				a.reader();
				cout << "����������ţ�";
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
	cout << "************************ �ɹ��˳���ϵͳ������********************************";
	cout << endl;
	return 0;
}