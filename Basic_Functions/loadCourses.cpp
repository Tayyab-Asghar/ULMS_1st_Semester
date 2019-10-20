#include<iostream>
#include<fstream>
using namespace std;
bool loadCourses(string codelist[],string namelist[],int semesterlist[],int creditlist[])
{
	string line;
	int a;
	ifstream file1;
	file1.open("Courses.txt");
	if(file1.is_open())
	{
		for(int i=0;!file1.eof();i++)
		{
			getline(file1,line,',');
			if(isValidCourseCode(line))
			{
				codelist[i]=line;
				getline(file1,line,',');
				if(isValidCourseName(line))
			    {
				namelist[i]=line;
				  file1>>a;
			      if(isValidCreditHours(a))
			      {
			      creditlist[i]=a;
			         file1.ignore(1,',');
			         file1>>a;
			         if(isValidSemester(a))
			         {
				     semesterlist[i]=a;
				     
				     counter++;
				     file1.ignore(1,'\0');
		             }
			         else
			         {
				     cout<<i+1<<" SEMESTER INVALID "<<endl;
				     break;
			         }
			         
			      }
			      else
			      {
				  cout<<i+1<<" CREDIT HOUR INVALID "<<endl;
				  break;
			      }
			    }
			    else
			    {
				cout<<i+1<<" COURSE NAME IS INVALID "<<endl;
				break;
			    }
			}
			else
			{
				cout<<i+1<<" COURSE CODE IS INVALID "<<endl;
				break;
			}
			
			
			
			
			
			
		}
		cout<<"COURSES LOADED SUCCESSFULLY "<<endl<<endl;
	}
	else
	{
		cout<<"ERROR OPENING FILE OR FILE DOES NOT EXIST";
	}
	file1.close();
}
int main()
{


    return 0;
}
