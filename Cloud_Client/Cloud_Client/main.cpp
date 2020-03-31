#include"client.h"
int main()
{
	CloudClient client(LISTEN_DIR, STORE_FILE,SERVER_IP, SERVER_PORT);
	client.Start();
    system("pause");
    return 0;
}