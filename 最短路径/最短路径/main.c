#include"Graph.h"

int main()
{
	int i, n;
	cout << "������������������Ȩͼ�Ķ������: ";
	cin >> n;
	adjmatrix g;
	InitMatrix(g);
	CreateMatrix(g);
	cout << "������������Ȩͼ���ڽӾ����ʾΪ: " << endl;
	PrintMatrix(g, n);
	int * d = new int[n];
	edgenode ** path = new edgenode *[n];
	cout << "��������Ҫ�����Դ��: ";
	cin >> i;
	Dijkstra(g, d, path, i, n);
	PrintPath(d, path, i, n);
	return 0;
}
