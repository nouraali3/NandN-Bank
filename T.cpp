#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <cstdio>
#include <vector>
#include "C.cpp"

using namespace std;

class employee
{
	private:
		int id;
		string name;
		
	public:
		void setname(string n)  {name=n;}
		void setid(int i)  {id=i;}
		string getname()  {return name;}
		int getid()  {return id;}
		
};


class teller: public employee
{
	private:
		int password;
	public:
		teller(){password=123456;}
		void setpassword(int p){ password=p;}
		int getpassword(){ return password;}

		void performCreateAccount(customer c)
		{
			fstream obj("db.txt", ios::in | ios::out | ios::app);                                                    
			if (obj.is_open())
				obj<< c.getName() << ' ' << c.getMobile() << ' ' << c.getId() << ' '<< c.getBalance() << endl;
			else
				cout <<"error reaching database ...";
		}
		
		void performShowInfo(customer c)
		{
			bool found=false;
			string n; int m,i; double b;
			fstream obj("db.txt", ios::in | ios::out | ios::app);  
			while(obj>> n >> m >> i >> b)
			{
				if(n==c.getName() && m==c.getMobile() && i==c.getId() )
				{
					cout<< n << ' ' << m << ' ' << i << ' ' << b <<endl<<endl;
					found =true;
					break;
				}
			}
			if(!found)
				cout<<"No customer exists with this information"<<endl<<endl;
		}
		
		
		double performDeposit(customer c,double money)
		{
			bool found=false;
			string n; int m,i; double b,newb=0;
			
			fstream old("db.txt", ios::in);   //making the existing db as an input to read from it
			fstream newfile("newdb.txt",ios::out);  //making a new file to which we copy the contents of the old file
			
			while(old>> n >> m >> i >> b)
			{
				if(n==c.getName() && m==c.getMobile() && i==c.getId() )
				{
					b=b+money; newb=b;
					found =true;
				}
				newfile<< n << ' ' << m << ' ' << i << ' ' << b <<endl;
			}
			old.close();   // closing the old file buffer <a must> in order to unlock the file
			newfile.close();  //  closing the new file buffer <a must> in order to unlock the file
			remove("db.txt");  // remove old file (db.txt)
			rename("newdb.txt", "db.txt");  //rename new file (newdb.txt) to be (db.txt) 
			
			return newb;
		}
		
		
		double performWithdraw(customer c,double money)
		{
			bool found=false;
			string n; int m,i; double b,newb=0;
			
			fstream old("db.txt", ios::in);   //making the existing db as an input to read from it
			fstream newfile("newdb.txt",ios::out);  //making a new file to which we copy the contents of the old file
			
			while(old>> n >> m >> i >> b)
			{
				if(n==c.getName() && m==c.getMobile() && i==c.getId() )
				{
					b=b-money; newb=b;
					found =true;
				}
				newfile<< n << ' ' << m << ' ' << i << ' ' << b <<endl;
			}
			old.close();   // closing the old file buffer <a must> in order to unlock the file
			newfile.close();  //  closing the new file buffer <a must> in order to unlock the file
			remove("db.txt");  // remove old file (db.txt)
			rename("newdb.txt", "db.txt");  //rename new file (newdb.txt) to be (db.txt) 
			
			return newb;
		}
		
		void performTransfer(vector<double> &v ,customer c,customer c2 , double money)
		{
			teller t;
			v[0]=t.performWithdraw(c,money);
			v[1]=t.performDeposit(c2,money);
		}


};
