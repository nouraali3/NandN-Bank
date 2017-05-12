#include <iostream>
#include <fstream>
#include "A.cpp"
#include <string>

using namespace std;


class customer
{
	private:
		string name;
		int mobile;
		int id;
		double balance;
		int service;
	public:
		void setName(string n)  {name=n;}
		string getName()  {return name;}
		
		void setMobile(int m)  {mobile=m;}
		int getMobile()  {return mobile;}
		
		void setId(int i)  {id=i;}
		int getId()  {return id;}
		
		void setBalance(double b)  {balance=b;}
		double getBalance()  {return balance;}
		
		void setService(int s){ service=s;}
		int getService(){return service;}
		
		//int getaccountnumber(){return A.accountnumber;}
		
};
