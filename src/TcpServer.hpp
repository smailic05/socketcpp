#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include<vector>
#include<cstring>

using namespace std;

class TcpServer 
{
    private:
    int sock;
    int listener;
    struct sockaddr_in addr;
    struct in_addr i_addr;
    public:
    void closeSock();
    void acceptTCP();
    void eraseArr();
    bool setup(int port);
    bool sendTCP(string data);
    string recieve(int size);
};


