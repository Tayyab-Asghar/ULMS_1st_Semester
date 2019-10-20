#include<iostream>
using namespace std;
void DeleteCourse(string codelist[],int creditlist[],int semesterlist[],string namelist[],string code)
{
	int o;
	for(int i=0;i<counter;i++)
	{
		if(code==codelist[i])
		 o=i;
	}
   for(int a=o;a<counter;a++)
   {
   	codelist[a]=codelist[a+1];
   	creditlist[a]=creditlist[a+1];
   	semesterlist[a]=semesterlist[a+1];
   	namelist[a]=namelist[a+1];
   }
  
  counter--;

}
int main()
{


    return 0;
}
