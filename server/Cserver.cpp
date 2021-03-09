#include "TcpServer.hpp"



int main()
{
    TcpServer tcp;
    int sock, listener;
    struct sockaddr_in addr;
    int bytes_read;
    int bufInt;
    tcp.setup(3426);
    
    while(1)
    {
        tcp.acceptTCP();

        while(1)
        {
            string str=tcp.recieve(1024);
            if (str.c_str()=="")
            {
                cerr<< "error, received empty package"<<endl;
                break;
            }
            else
            {
                try
		        {
			        bufInt=stoi(str.c_str());
		        }
		        catch(const std::exception& e)
		        {
			        std::cerr<<"error " << '\n';

			        break;
		        }	
                cout<<bufInt;
                if(bufInt>9 && bufInt%32==0)
                {
                    cout<<" the data is correct"<<endl;
                }
                else
                {
                    cout<<" the data isn`t correct"<<endl;
                }
            }

        }
    
        tcp.closeSock();
    }
    
    return 0;
}