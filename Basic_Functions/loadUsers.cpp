#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int counter1=0;
bool loadUsers(string userslist[],string passwordslist[])
{
	string line;
	ifstream user;
	user.open("Users.txt");
	if(user.is_open())
	{
		for(int i=0;!user.eof();i++)
		{
			getline(user,line,',');
			userslist[i]=line;
			cout<<userslist[i]<<endl;
			getline(user,line);
			passwordslist[i]=line;
		
			cout<<passwordslist[i]<<endl;
			cout<<endl;
			counter1++;
		}
	}
	else
	{
		cout<<"Sorry, we are unable to run the program, as user data does not exist."<<endl<<endl;
	}
}
int main()
{
	string username;
    string password;
    string userslist[100];
    string passwordslist[100];
    loadUsers(userslist,passwordslist);
    cout<<"Username :  ";
    cin>>username;
    cout<<endl<<"Password :  ";
    cin>>password;
    cout<<endl;
   if((username==userslist[0]&&password==passwordslist[0])||(username==userslist[1]&&password==passwordslist[1]))
   {
   	cout<<"OK DI WAZSH LAO ";
   }
   else
   {
   	cout<<"wargaye vai";
   }
    return 0;
}
