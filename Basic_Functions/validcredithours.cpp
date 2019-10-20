#include<iostream>
#include<iomanip>
using namespace std;
bool isValidCreditHours(int credit)
{
	if(credit>0&&credit<4)
	
		return 1;
	
	else
	 
		return 0;
	
}
int main()
{
	int a;
	cin>>a;
	cout<<isValidCreditHours(a)<<endl;
	return 0;
}
