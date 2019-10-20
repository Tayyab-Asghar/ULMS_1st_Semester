#include<iostream>
#include<fstream>
using namespace std;
void saveCourses(string codelist[],string namelist[],int semesterlist[],int creditlist[],)
{
	ofstream file;
	file.open("Courses.txt");
	if(file.is_open())
	{
		for(int i=0;i<counter;i++)
		{
			file<<codelist[i]<<","<<namelist[i]<<","<<creditlist[i]<<","<<semesterlist<<endl;

		}
		cout<<"courses has been added successfully";
	}
	else
	{
		cout<<"ERROR OPENING FILE Courses.txt";
	}
}
int main()
{


    return 0;
}
