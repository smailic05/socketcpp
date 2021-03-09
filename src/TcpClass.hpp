#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include<vector>
#include<thread>
#include<mutex>
#include<cstring>
#include<condition_variable>
#include<sstream>
#include<algorithm>

using namespace std;

class TcpClient 
{
    private:
    vector<string> arr;
    mutex mtx;
    int sock;
    struct sockaddr_in addr;
    struct in_addr i_addr;
    public:
    void eraseArr();
    void setArr(vector<string> s);
    vector<string> getArr();
    bool setup(int port,string adress);
    bool sendTCP(string data);
    string recieve(int size);
    void exitTCP();
};

