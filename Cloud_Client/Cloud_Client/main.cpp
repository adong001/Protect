#include"client.h"
#define STORE_FILE "./list.backup/" //持久化存储文件的路径
#define LISTEN_DIR "./backup/"	//待备份文件的路径
#define SERVER_IP "192.168.178.129" //服务端ip
#define SERVER_PORT 9000 //服务端port

int main()
{
	CloudClient client(LISTEN_DIR, STORE_FILE,SERVER_IP, SERVER_PORT);
	client.Start();
    system("pause");
    return 0;
}