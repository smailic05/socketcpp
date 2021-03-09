
#include "TcpClass.hpp"


using namespace std;
mutex mtx;
TcpClient tcp;
condition_variable cv;

bool comp(int a, int b)
{
	return a > b;
}

vector<string> split(const string &s, char delim) {
  stringstream ss(s);
  string item;
  vector<string> elems;
  while (getline(ss, item, delim)) 
  {
	if (item!="")
	{
		elems.push_back(item); 
	}
	  
  }
  return elems;
}

void check(const string &s)
{
	int count = 0;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i]>='9' && s[i]<='0')
		{
			cout<< "there is a problem with your string, please input only digits";
			exit(3);
		}
		else if (s[i]!=' ')
		{
			count++;
		}
	}
	if (count>64)
	{
		cout<< "there is a problem with your string, please input only 64 digits";
		exit(3);
	}
}

void strToInt(vector<string> &arr,vector<int> &buf)
{
	for (int i = 0; i < arr.size(); i++)
	{
		try
		{
			buf.push_back(stoi(arr[i])); //string to int massive
		}
		catch(const std::exception& e)
		{
			std::cerr<<"error " << '\n';
			if ( e.what()=="stoi")
			{
				cout<< "there is a problem with your string, please input only digits";
			}
			exit(3);
		}	
	}
}

void inputThreadFunc()
{
	while (1)
	{
		
		string s;	
		vector<int> buf;
		vector<string> arr;			
		unique_lock<std::mutex> lck(mtx);

		getline(cin,s); 
		check(s);
		arr = split(s,' ');

		strToInt(arr,buf);

		sort(buf.begin(),buf.end(),comp);

		for (int i = 0; i < buf.size(); i++)
		{
			if(buf[i]%2==0)
			{
				arr[i]="KB";
			}
			else
			{
				arr[i]=to_string(buf[i]);
			}
		}

		tcp.setArr(arr);
		cv.notify_one();
		cv.wait(lck,[&](){return tcp.getArr().size()==0;});
	}
}

void sendThreadFunc()
{

	string sumString;
	while (1)
	{
		unique_lock<std::mutex> lck(mtx);
		cv.wait(lck,[&](){return tcp.getArr().size()!=0;});
		vector<string> arr=tcp.getArr();
		cv.notify_one();
		int sum=0;
		for (int i = 0; i < arr.size(); i++)
		{
			if(arr[i]!="KB")
			{
				sum+=stoi(arr[i]); 
			}
		}
		sumString=to_string(sum);
		tcp.sendTCP(sumString);
		cout<<"sended"<<sumString<<endl;	
		tcp.eraseArr();
	}
		
}



int main()
{	
	tcp.setup(3426,"");

	thread inputThread(inputThreadFunc);
	thread sendThread(sendThreadFunc);
	inputThread.join();
	sendThread.join();
	
	
	return 0;
}