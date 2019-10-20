#include<iostream>
#include<iomanip>
using namespace std;
bool isValidSemester(int s)
{
   if(s>0&&s<9)
   {
   	  return 1;
   }
   else
   {
   	return 0;
   }
}
int main()
{
	int a;
	cin>>a;
	cout<<isValidSemester(a)<<endl;
	return 0;
}
