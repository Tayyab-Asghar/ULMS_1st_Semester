#include<iostream>
using namespace std;
void AddCourse(string codelist[],int creditlist[],int semesterlist[],string namelist[],string code,int credit,int semester,string name)
{
  if(isValidCourseCode(code))
    if(isValidCreditHours(credit))
      if(isValidSemester(semester))
        if(isValidCourseName(name))
          {
          	codelist[counter]=code;
          	creditlist[counter]=credit;
          	semesterlist[counter]=semester;
          	namelist[counter]=name;
          	counter++;
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
