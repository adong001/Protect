#include"Student.h"

void person::add()
{
	char choose;
	cout << "请输入姓名:  ";
	cin >> name;
	cout << endl;
label1:cout << "请选择性别：" << "\t";
	cout << "A、男" << "\t" << "B、女" << endl;
	cout << "请输入你的选择：";
	cin >> choose;
	if (choose == 'a' || 'A')
		sex = "男";
	else if (choose == 'b' || 'B')
		sex = "女";
	else {
		cout << "输入有误，请重新选择!" << endl;
		goto label1;
	};
}

void student::disp()//显示
{
	cout << endl << "                 姓  名: " << name << endl;
	cout << "                 学  号: " << number << endl;
	cout << "                 性  别: " << sex << endl;
	cout << "                 电话号码: " << tel << endl << endl;
}
void student::dispname()
{
	cout << name;
}
void student::add()
{
	cout << "*******************************录入学生信息*******************************" << endl;
	cout << "请输入学号:  ";
	cin >> number;
	cout << endl;
	person::add();
	cout << "请输入宿舍号：  ";
	cin >> room;
	cout << endl;
	cout << "请输入电话号码： ";
	cin >> tel;
	cout << endl;

}
void student::add2()//写入函数
{
	student a;
	a.add();
	fstream file("a.txt", ios::out | ios::app); //打开文件，指针指向文件尾
	file.write((char*)&a, sizeof(a));//把类信息写入文件
	file.close(); //关闭文件
	cout << "信息已经被保存" << endl;
}
void student::searchname()//按姓名查询
{
	cout << "请输入所要查询的学生姓名:  ";
	char name2[10];
	cin >> name2;
	student a;
	fstream file("a.txt", ios::in);//打开文件，指针在文件头
	file.read((char*)&a, sizeof(a));  //读取类信息
	while (!file.eof())               //判断文件指针是否到文件尾
	{
		if (comp(a.name, name2))       //判断输入的字符是否与文件中的一样
			a.disp();                  //如一样的话，显示信息
		file.read((char*)&a, sizeof(a));//如果指针没到文件尾，继续读取
	}
	file.close();                    //关闭文件
}
void student::searchroom()
{
	cout << "请输入所要查询的宿舍号:  ";
	int roomnum;
	cin >> roomnum;
	student a;                        //第一个学生类的对象
	fstream file("a.txt", ios::in); //打开文件，指针在文件头
	file.read((char*)&a, sizeof(a));   //读取类信息
	while (!file.eof())                //判断指针是否在文件尾
	{
		if (a.room1() == roomnum)             //判断输入宿舍号是否与文件中的宿舍号一样
			a.disp();                  //如果一样的话，显示信息
		file.read((char*)&a, sizeof(a)); //如果指针没到文件尾，继续读取
	}
	file.close();                      //关闭文件
}
void student::searchnumber()//按学号查询
{
	cout << "请输入所要查询的学号:";
	int number2;
	cin >> number2; //输入学号
	student a;                //第一个学生类的对象
	fstream file("a.txt", ios::in);  //二进制打开文件。指针在文件头
	file.read((char*)&a, sizeof(a));  //读取类信息
	while (!file.eof())               //判断指针是否在文件尾
	{
		if (a.number1() == number2)       //判断输入的学号是否与文件中的一样
			a.disp();
		file.read((char*)&a, sizeof(a));//如果指针没到文件尾，继续读取
	}
	file.close();                     //关闭文件
}

void student::menue()
{
	cout << "             *******************学生管理系统*************************      " << endl;
	cout << "             *                                                      *" << endl;
	cout << "             *              1、 添加学生信息                        *" << endl;
	cout << "             *              2、 添加学生成绩                        * " << endl;
	cout << "             *              3、 查询学生信息                        *" << endl;
	cout << "             *              4、 查询学生成绩                        *" << endl;
	cout << "             *              5、 学生成绩排序                        *" << endl;
	cout << "             *              6、 退出系统                            *" << endl;
	cout << "             *                                                      *" << endl;
	cout << "             ********************************************************       " << endl;
}
void student::reader()
{
	cout << "             *******************查询学生信息*************************      " << endl;
	cout << "             *                                                      *" << endl;
	cout << "             *              1、 按姓名查询                          *" << endl;
	cout << "             *              2、 按学号查询                          *" << endl;
	cout << "             *              3、 按宿舍号查询                        *" << endl;
	cout << "             *              4、 返回主菜单                          * " << endl;
	cout << "             ********************************************************" << endl;
}

bool comp(char s1[], char s2[])        //比较文件中字符和输入的字符是否相同
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
	cout << "*******************************录入学生成绩*******************************" << endl;
	cout << "请输入学号： ";
	cin >> number;
	cout << endl;
	cout << "请输入课程号： ";
	cin >> cnum;
	cout << endl;
	cout << "请输入课程名： ";
	cin >> cname;
	cout << endl;
label2:cout << "请输入学分： ";
	cin >> xuefen;
	if (!(xuefen >= 0 && xuefen <= 10))
	{
		cout << "输入错误，请输入0到10的整数：" << endl;
		goto label2;
	}
	cout << endl;
label3:cout << "请输入平时成绩： ";
	cin >> pingshif;
	if (!(pingshif >= 0 && pingshif <= 100))
	{
		cout << "输入错误,请输入0到100的整数：" << endl;
		goto label3;
	}
	cout << endl;
label4:cout << "请输入实验成绩： ";
	cin >> shiyanf;
	if (!(shiyanf >= -1 && shiyanf <= 100))
	{
		cout << "输入错误，范围是-1到100的整数：" << endl;
		goto label4;
	}
	cout << endl;
	cout << "请输入卷面成绩： ";
	cin >> juanmianf;
	cout << endl;
};
void student::searchgrade()
{
	cout << "请输入所要查询的学号:  ";
	int gradenum, i;
	double t;
	totalxuefen = 0;
	i = 0;
	cin >> gradenum;
	student b;//定义一个学生类的对象
	fstream file("b.txt", ios::in);
	file.read((char*)&b, sizeof(b));//打开文件。指针在文件头
	//读取类信息
	while (!file.eof())                //判断指针是否在文件尾
	{
		if (b.number1() == gradenum)             //判断输入学号是否与文件中的学号一样
		{
			t = b.gradedisp();      //如果一样的话，显示信息
			i++;
			totalxuefen = totalxuefen + t;
		}
		file.read((char*)&b, sizeof(b));
		//如果指针没到文件尾，继续读取
	}

	file.close();
	cout << "共  修：" << i << "科" << "\t" << "\t" << "实得总学分：" << totalxuefen << endl;
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
	cout << "学    号：" << number << "\t" << "姓    名：";
	fstream file("a.txt", ios::in); //打开文件，指针在文件头
	file.read((char*)&a, sizeof(a));   //读取类信息
	while (!file.eof())                //判断指针是否在文件尾
	{
		if (a.number1() == number)             //判断输入学号是否与文件中的学号一样
		{
			a.dispname();               //如果一样的话，显示信息
			break;
		}
		file.read((char*)&a, sizeof(a)); //如果指针没到文件尾，继续读取
	}
	file.close();                      //关闭文件
	cout << endl;
	cout << "课程编号：" << cnum << "\t" << "课程名称：" << cname << "\t" << "综合成绩：" << p << "\t" << "实得学分：" << score << endl;
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
	cout << "学号：" << "  " << "学分：" << endl;
	for (int i = 0; i<30; i++)

		cout << dd[i].number << "       " << dd[i].xuefen << endl;

};
