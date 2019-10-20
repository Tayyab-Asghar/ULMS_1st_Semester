#include<iostream>
#include<iomanip>
using namespace std;
bool isValidCourseName(string coursename)
{
	bool flag=0;
	int length=coursename.size();
	for(int i=0;i<length;i++)
	{
		if((coursename[i]>='A'&&coursename[i]<='Z')||(coursename[i]>='a'&&coursename[i]<='z')||coursename[i] == ' ')
		flag=1;
		else
		return 0;
	}
	return 1;
}
int main()
{
	int a;
	string name;
	getline(cin,name);
	cout<<isValidCourseName(name)<<endl;
	return 0;
}
