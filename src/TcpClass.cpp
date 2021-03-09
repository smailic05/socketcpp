#include"TcpClass.hpp"

void TcpClient::eraseArr()
{
    arr.clear();
}

void TcpClient::setArr(vector<string> s)
{
    lock_guard<mutex> lock(mtx);
    arr=s;
}

vector<string> TcpClient::getArr()
{
    lock_guard<mutex> lock(mtx);
    return arr;
}

bool TcpClient::setup(int port, string adress="")

{
   	sock = socket(AF_INET , SOCK_STREAM , 0);
	if (sock == -1)
	{
  		cout << "Could not create socket" << endl;
        exit(1);
    }

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
    if (adress=="")
    {
        addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    }
    else if(inet_aton(adress.c_str(),&i_addr)!=0)
    {
        addr.sin_addr=i_addr;
    }
    else
    {
        cout<<"adress is incorrect";
    }
    if (connect(sock , (struct sockaddr *)&addr , sizeof(addr)) < 0)
  	{
    		cout<<"connect failed. Error";
    		exit(1);
  	}
    
    return true;
}

bool TcpClient::sendTCP(string data)

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

string TcpClient::recieve(int size)

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

void TcpClient::exitTCP()
{
    close(sock);
}
