#include"TcpServer.hpp"

void TcpServer::closeSock()
{
    close(sock);
}

void  TcpServer::acceptTCP()
{
        sock = accept(listener, NULL, NULL);
        if(sock < 0)
        {
            perror("accept");
            exit(3);
        }
}
bool TcpServer::setup(int port)

{
    listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0)
    {
        perror("socket");
        exit(1);
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3426);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(2);
    }

    if(listen(listener, 1)<0)
    {
        perror("listen");
        exit(3);
    }
    
    return true;
}

bool TcpServer::sendTCP(string data)

{
	if(sock != -1) 
	{
		if( send(sock , data.c_str() , data.size() , 0) < 0)
		{
			cout << "Send failed : " << data << endl;
			return false;
		}
	}
	else
		return false;
	return true;
}

string TcpServer::recieve(int size)

{
    char buffer[size];
	memset(&buffer[0], 0, sizeof(buffer));
  	string reply;
	if( recv(sock , buffer , size, 0) < 0)
  	{
	    cout << "receive failed!" << endl;
		return nullptr;
  	}
	buffer[size-1]='\0';
  	reply = buffer;
  	return reply;
}
