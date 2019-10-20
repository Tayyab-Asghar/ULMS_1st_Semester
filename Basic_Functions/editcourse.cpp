#include<iostream>
using namespace std;
void EditCourse(string codelist[],int creditlist[],int semesterlist[],string namelist[],string code,int credit,int semester,string name)
{
	
  if(isValidCourseCode(code))
    if(isValidCreditHours(credit))
      if(isValidSemester(semester))
        if(isValidCourseName(name))
          {
          	codelist[global]=code;
          	creditlist[global]=credit;
          	semesterlist[global]=semester;
          	namelist[global]=name;
		  }
        else
        cout<<"INVALID COURSENAME"<<endl;
      else 
      cout<<"INVAID SEMESTER "<<endl;
    else
    cout<<"INVALID CREDIT HOUR"<<endl;
  else
  cout<<"INVALID COURSE CODE"<<endl;

}
int main()
{


    return 0;
}
