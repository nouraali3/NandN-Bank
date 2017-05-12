#include <iostream>
#include <queue>
#include<vector>
#include "T.cpp"
#include <string>

using namespace std;

void userMenu(queue <customer>q );
void customerMenu(queue<customer> q);
void tellerMenu(teller t,queue <customer>q);

int main()
{
	queue <customer> q; //creating an empty queue and pass it by reference to userMenu to allo adding customer later
	userMenu(q);
}

void userMenu(queue<customer> q)
{
	int choice;
	cout << "1-Customer"<<endl;
	cout << "2-Teller"<<endl;

	cin>> choice;
	cout<<endl;
	
	switch (choice)
	{
		case 1:
			customerMenu(q); //here we are sending the empty queue to customerMenu to add customers
			break;
			
        case 2:
        	{
        		teller t;
        		int p;
        		cout <<"please enter the password to continue: ";
        		cin>>p;
				if (p==t.getpassword())
				{
					if(q.size()>0)
						tellerMenu(t,q);
					else
					{
						cout<<"No customer to serve ,redirecting to user menu......."<<endl<<endl;
						userMenu(q);
					}
				}
        		else 
				{
					cout<<"wrong password"<<endl;
					userMenu(q);
				}        			
        	    break;
			}
	}
}

void customerMenu(queue <customer>q)
{	
	cout << "1-Create bank account"<<endl;
	cout << "2-Deposit"<<endl;
	cout << "3-Withdraw"<<endl;
	cout << "4-Transfer"<<endl;
	cout << "5-Get account information"<<endl;
	cout << "6-Go back"<<endl;    //here the main menu that contains the type of user (customer ,teller)
	
	int choice;
	cin >> choice;

	if(choice>=1 && choice<6)
	{
		customer c;
		c.setService(choice);
		q.push(c); //here the customer enter a queue of customers
		cout<<"Your request is submitted , please take a number and wait till a teller becomes available"<<endl;
		cout<<endl;
		userMenu(q);
	}
	else if (choice==6) //choice is to go to user menu 
	{
		cout<<endl;
		userMenu(q);	
	} 
	else
	{
		cout<<"please enter a right choice.."<<endl; 
		customerMenu(q);
	}
}

void tellerMenu(teller t,queue <customer>q)
{
	cout<<endl<<"The current number of customers is "<<q.size()<<endl<<endl ;
	customer c=q.front(); //deque a customer
	q.pop();
	int service=c.getService();	
	string name; int id,mobile; double balance;
	
	switch(service)
	{
		case 1:
			cout << "The customer wants to create account"<<endl;
			break;
		case 2:
			cout << "The customer wants to deposit money"<<endl;
			break;
		case 3:
            cout << "The customer wants to withdraw money"<<endl;
			break;
		case 4:
			cout << "The customer wants to transfer money"<<endl;
			break;
		case 5:
			cout<<"Customer wants to check account information"<<endl;
			break;
	}
	
	cout<<"Fill in the customer information"<<endl;
	cout<<"name: "; cin>>name; c.setName(name);
	cout<<"mobile number: "; cin>>mobile; c.setMobile(mobile);
	cout<<"id: "; cin>>id; c.setId(id);	      
	
	double money,newbalance;

	switch (service)
	{
		case 1:
		    cout<<"minimum balance: "; cin>>balance; c.setBalance(balance);
            cout<<endl;
			t.performCreateAccount(c);
			break;
		case 2:
			cout<<"amount to be deposited: " ; cin>>money;
			newbalance=t.performDeposit(c,money);
			if(newbalance==0)
				cout<<"No Customer with this information "<<newbalance<<endl;
			else if (newbalance>0)
				cout<<"Customer's new balance is "<<newbalance<<endl;
			break;
		case 3:
			cout<<"amount to be withdrawed: " ; cin>>money;
			newbalance=t.performWithdraw(c,money);
			if(newbalance==0)
				cout<<"No Customer with this information "<<endl;
			else if (newbalance<0)
				cout<<"Customer's balance is not enough "<<endl; 
			else if (newbalance>0)
				cout<<"Customer's new balance is "<<newbalance<<endl; 
			break;
		case 4:
			{
				vector<double> v(2,0); customer c2; string n2; int m2,i2; 
				cout<<"Amount of money to be transfered: " ; cin>>money;
				cout<<"Recipient name: "; cin>>n2;  c2.setName(n2);
				cout<<"Recipient mobile: "; cin>>m2;  c2.setMobile(m2);
				cout<<"Recipient id: "; cin>>i2;  c2.setId(i2);
				t.performTransfer(v,c,c2,money);
				cout<<"Sender balance after transfering money is "<<v[0]<<endl<<endl;
			break;
			}
		case 5:
			cout<<endl;
			t.performShowInfo(c);
			break;
	}
	
	Again:
	int n;
	cout<<"1-Continue serving customers"<<endl;
	cout<<"2-Go to user menu"<<endl;
	cin>>n;
	cout<<endl;
	
	if(n==1 && q.size()>0)  //if the teller chooses to serve more customers and there is customers in the queue
		tellerMenu(t,q);
	else if(n==1 && q.size()==0)   //if the teller chooses to serve more customer but there is customers' queue is empty
	{
		cout<<"No more customers to serve ,redirecting to main menu..."<<endl<<endl;
		userMenu(q);
	}
	else if (n==2)
		userMenu(q);
	else
	{
		cout<< "please enter a right choice"<<endl;
		goto Again;
	} 
}
