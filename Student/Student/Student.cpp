#include"Student.h"

void person::add()
{
	char choose;
	cout << "����������:  ";
	cin >> name;
	cout << endl;
label1:cout << "��ѡ���Ա�" << "\t";
	cout << "A����" << "\t" << "B��Ů" << endl;
	cout << "���������ѡ��";
	cin >> choose;
	if (choose == 'a' || 'A')
		sex = "��";
	else if (choose == 'b' || 'B')
		sex = "Ů";
	else {
		cout << "��������������ѡ��!" << endl;
		goto label1;
	};
}

void student::disp()//��ʾ
{
	cout << endl << "                 ��  ��: " << name << endl;
	cout << "                 ѧ  ��: " << number << endl;
	cout << "                 ��  ��: " << sex << endl;
	cout << "                 �绰����: " << tel << endl << endl;
}
void student::dispname()
{
	cout << name;
}
void student::add()
{
	cout << "*******************************¼��ѧ����Ϣ*******************************" << endl;
	cout << "������ѧ��:  ";
	cin >> number;
	cout << endl;
	person::add();
	cout << "����������ţ�  ";
	cin >> room;
	cout << endl;
	cout << "������绰���룺 ";
	cin >> tel;
	cout << endl;

}
void student::add2()//д�뺯��
{
	student a;
	a.add();
	fstream file("a.txt", ios::out | ios::app); //���ļ���ָ��ָ���ļ�β
	file.write((char*)&a, sizeof(a));//������Ϣд���ļ�
	file.close(); //�ر��ļ�
	cout << "��Ϣ�Ѿ�������" << endl;
}
void student::searchname()//��������ѯ
{
	cout << "��������Ҫ��ѯ��ѧ������:  ";
	char name2[10];
	cin >> name2;
	student a;
	fstream file("a.txt", ios::in);//���ļ���ָ�����ļ�ͷ
	file.read((char*)&a, sizeof(a));  //��ȡ����Ϣ
	while (!file.eof())               //�ж��ļ�ָ���Ƿ��ļ�β
	{
		if (comp(a.name, name2))       //�ж�������ַ��Ƿ����ļ��е�һ��
			a.disp();                  //��һ���Ļ�����ʾ��Ϣ
		file.read((char*)&a, sizeof(a));//���ָ��û���ļ�β��������ȡ
	}
	file.close();                    //�ر��ļ�
}
void student::searchroom()
{
	cout << "��������Ҫ��ѯ�������:  ";
	int roomnum;
	cin >> roomnum;
	student a;                        //��һ��ѧ����Ķ���
	fstream file("a.txt", ios::in); //���ļ���ָ�����ļ�ͷ
	file.read((char*)&a, sizeof(a));   //��ȡ����Ϣ
	while (!file.eof())                //�ж�ָ���Ƿ����ļ�β
	{
		if (a.room1() == roomnum)             //�ж�����������Ƿ����ļ��е������һ��
			a.disp();                  //���һ���Ļ�����ʾ��Ϣ
		file.read((char*)&a, sizeof(a)); //���ָ��û���ļ�β��������ȡ
	}
	file.close();                      //�ر��ļ�
}
void student::searchnumber()//��ѧ�Ų�ѯ
{
	cout << "��������Ҫ��ѯ��ѧ��:";
	int number2;
	cin >> number2; //����ѧ��
	student a;                //��һ��ѧ����Ķ���
	fstream file("a.txt", ios::in);  //�����ƴ��ļ���ָ�����ļ�ͷ
	file.read((char*)&a, sizeof(a));  //��ȡ����Ϣ
	while (!file.eof())               //�ж�ָ���Ƿ����ļ�β
	{
		if (a.number1() == number2)       //�ж������ѧ���Ƿ����ļ��е�һ��
			a.disp();
		file.read((char*)&a, sizeof(a));//���ָ��û���ļ�β��������ȡ
	}
	file.close();                     //�ر��ļ�
}

void student::menue()
{
	cout << "             *******************ѧ������ϵͳ*************************      " << endl;
	cout << "             *                                                      *" << endl;
	cout << "             *              1�� ���ѧ����Ϣ                        *" << endl;
	cout << "             *              2�� ���ѧ���ɼ�                        * " << endl;
	cout << "             *              3�� ��ѯѧ����Ϣ                        *" << endl;
	cout << "             *              4�� ��ѯѧ���ɼ�                        *" << endl;
	cout << "             *              5�� ѧ���ɼ�����                        *" << endl;
	cout << "             *              6�� �˳�ϵͳ                            *" << endl;
	cout << "             *                                                      *" << endl;
	cout << "             ********************************************************       " << endl;
}
void student::reader()
{
	cout << "             *******************��ѯѧ����Ϣ*************************      " << endl;
	cout << "             *                                                      *" << endl;
	cout << "             *              1�� ��������ѯ                          *" << endl;
	cout << "             *              2�� ��ѧ�Ų�ѯ                          *" << endl;
	cout << "             *              3�� ������Ų�ѯ                        *" << endl;
	cout << "             *              4�� �������˵�                          * " << endl;
	cout << "             ********************************************************" << endl;
}

bool comp(char s1[], char s2[])        //�Ƚ��ļ����ַ���������ַ��Ƿ���ͬ
{
	int i = 0;
	while (s1[i] != '\0'&&s2[i] != '\0'&&s1[i] == s2[i])
		i++;
	if (s1[i] == '\0'  &&s2[i] == '\0')
		return 1;
	else
		return 0;
};
void student::grade()
{
	cout << "*******************************¼��ѧ���ɼ�*******************************" << endl;
	cout << "������ѧ�ţ� ";
	cin >> number;
	cout << endl;
	cout << "������γ̺ţ� ";
	cin >> cnum;
	cout << endl;
	cout << "������γ����� ";
	cin >> cname;
	cout << endl;
label2:cout << "������ѧ�֣� ";
	cin >> xuefen;
	if (!(xuefen >= 0 && xuefen <= 10))
	{
		cout << "�������������0��10��������" << endl;
		goto label2;
	}
	cout << endl;
label3:cout << "������ƽʱ�ɼ��� ";
	cin >> pingshif;
	if (!(pingshif >= 0 && pingshif <= 100))
	{
		cout << "�������,������0��100��������" << endl;
		goto label3;
	}
	cout << endl;
label4:cout << "������ʵ��ɼ��� ";
	cin >> shiyanf;
	if (!(shiyanf >= -1 && shiyanf <= 100))
	{
		cout << "������󣬷�Χ��-1��100��������" << endl;
		goto label4;
	}
	cout << endl;
	cout << "���������ɼ��� ";
	cin >> juanmianf;
	cout << endl;
};
void student::searchgrade()
{
	cout << "��������Ҫ��ѯ��ѧ��:  ";
	int gradenum, i;
	double t;
	totalxuefen = 0;
	i = 0;
	cin >> gradenum;
	student b;//����һ��ѧ����Ķ���
	fstream file("b.txt", ios::in);
	file.read((char*)&b, sizeof(b));//���ļ���ָ�����ļ�ͷ
	//��ȡ����Ϣ
	while (!file.eof())                //�ж�ָ���Ƿ����ļ�β
	{
		if (b.number1() == gradenum)             //�ж�����ѧ���Ƿ����ļ��е�ѧ��һ��
		{
			t = b.gradedisp();      //���һ���Ļ�����ʾ��Ϣ
			i++;
			totalxuefen = totalxuefen + t;
		}
		file.read((char*)&b, sizeof(b));
		//���ָ��û���ļ�β��������ȡ
	}

	file.close();
	cout << "��  �ޣ�" << i << "��" << "\t" << "\t" << "ʵ����ѧ�֣�" << totalxuefen << endl;
};

double student::gradedisp()
{
	double p;
	student a;

	if (shiyanf == -1)
		p = pingshif*0.3 + juanmianf*0.7;
	else p = pingshif*0.15 + shiyanf*0.15 + juanmianf*0.7;
	if (p >= 90 && p <= 100)
		score = xuefen * 1;
	else if (p >= 80 && p<90)
		score = xuefen*0.8;
	else if (p >= 70 && p<80)
		score = xuefen*0.75;
	else if (p >= 60 && p<70)
		score = xuefen*0.6;
	else score = xuefen * 0;
	cout << endl;
	cout << "ѧ    �ţ�" << number << "\t" << "��    ����";
	fstream file("a.txt", ios::in); //���ļ���ָ�����ļ�ͷ
	file.read((char*)&a, sizeof(a));   //��ȡ����Ϣ
	while (!file.eof())                //�ж�ָ���Ƿ����ļ�β
	{
		if (a.number1() == number)             //�ж�����ѧ���Ƿ����ļ��е�ѧ��һ��
		{
			a.dispname();               //���һ���Ļ�����ʾ��Ϣ
			break;
		}
		file.read((char*)&a, sizeof(a)); //���ָ��û���ļ�β��������ȡ
	}
	file.close();                      //�ر��ļ�
	cout << endl;
	cout << "�γ̱�ţ�" << cnum << "\t" << "�γ����ƣ�" << cname << "\t" << "�ۺϳɼ���" << p << "\t" << "ʵ��ѧ�֣�" << score << endl;
	return score;
}
void student::paixu()
{
	int n;
	int t, m;
	student dd[30];
	ifstream file;
	file.open("b.txt", ios_base::in | ios_base::binary);
	for (n = 0; n<30; n++)
	{
		file.read(reinterpret_cast<char*>(&dd[n]), sizeof(student));
	}
	file.close();

	for (int i = 0; i<30; i++)
	for (int j = 0; j<30; j++)
	{
		if (dd[i].xuefen>dd[j].xuefen)
		{
			t = dd[i].xuefen;
			dd[i].xuefen = dd[j].xuefen;
			dd[j].xuefen = t;
			m = dd[i].number;
			dd[i].number = dd[j].number;
			dd[j].number = m;
		}
	}
	cout << "ѧ�ţ�" << "  " << "ѧ�֣�" << endl;
	for (int i = 0; i<30; i++)

		cout << dd[i].number << "       " << dd[i].xuefen << endl;

};
