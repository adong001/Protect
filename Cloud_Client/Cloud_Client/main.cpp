#include"client.h"
#define STORE_FILE "./list.backup/" //�־û��洢�ļ���·��
#define LISTEN_DIR "./backup/"	//�������ļ���·��
#define SERVER_IP "192.168.178.129" //�����ip
#define SERVER_PORT 9000 //�����port

int main()
{
	CloudClient client(LISTEN_DIR, STORE_FILE,SERVER_IP, SERVER_PORT);
	client.Start();
    system("pause");
    return 0;
}