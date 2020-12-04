#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <regex>

using namespace std;
                     // Defining the Functions.
bool isValidCourseCode(string courseCode);
bool isValidCourseName(string courseName);
bool isValidCreditHours(int crdHrs);
bool isValidSemester(int semester);
bool saveCourses(string codeList[], string nameList[], int crtHrsList[], int semList[]);
bool loadCourses(string codeList[], string nameList[], int crtHrsList[], int semList[]);
bool loadUsers(string usersList[], string passwordsList[]);
bool isValidRegistrationNumber(string regNo);
bool isValidStudentName(string studentName);
bool saveStudents(string stdNamesList[], string stdRegNoList[], string stdCourseList[][20]);
bool loadStudents(string stdNamesList[], string stdRegNoList[], string stdCourseList[][20]);
void AddCourse(string codeList[], string nameList[], int crtHrsList[], int semList[], string courseCode, string courseName, int crdHrs, int semester);
void EditCourse(string codeList[], string nameList[], int crtHrsList[], int semList[], string courseCode, string courseName, int crdHrs, int semester);
void DeleteCourse(string codeList[], string nameList[], int crtHrsList[], int semList[], string courseCode);
void ViewCourses(string codeList[], string nameList[], int crtHrsList[], int semList[]);
void ViewSemesterCourses(string codeList[], string nameList[], int crtHrsList[], int semList[], int semester);
void AddStudent(string stdNamesList[], string stdRegNoList[], string studentName, string regNo);
void UpdateStudent(string stdNamesList[], string stdRegNoList[], string studentName, string regNo);
void DeleteStudent(string stdNamesList[], string stdRegNoList[], string stdCourseList[][20], string regNo);
void ViewStudents(string stdNamesList[], string stdRegNoList[], string stdCourseList[][20]);
void RegisterCourse(string stdRegNoList[], string stdCourseList[][20], string codeList[], string regNo, string courseCode);
void UnRegisterCourse(string stdRegNoList[], string stdCourseList[][20],string codeList[], string regNo, string courseCode);

                  // Defining the Functions that are not in Manual but I built them for my Simplicity.
bool isInputDataValid(string courseCode, int crdHrs, int semester, string courseName);
bool isCourseAlreadyPresent(string codeList[], string courseCode);
bool isUserDataValid(string usersList[], string passwordsList[], string username, string password);
bool loadAllData(string codeList[], string nameList[], int crtHrsList[], int semList[], string usersList[], string passwordsList[], string stdNamesList[], string stdRegNoList[], string stdCourseList[][20]);
bool isRegNoAlreadyPresent(string stdRegNoList[], string regNo);
bool isStudentAlreadyRegistered (string stdRegNoList[], string stdCourseList[][20], string regNo, string courseCode);
bool nonZeroTotalCourses();
bool nonZeroTotalStudents();
bool isValidInputDetails(string stdNamesList[], string stdRegNoList[], string password, string regNo);
void courseInput(string &courseCode, int &crdHrs, int &semester, string &courseName);
void studentInput(string &regNo, string &studentName);
void handleInputFailure();
void toUnRegisterAllStudent(string stdCourseList[][20], string courseCode);
void putInstdCourseList(string stdCourseList[][20], string regCourses);
void ViewLoggedStudent(string stdNamesList[], string stdRegNoList[], string stdCourseList[][20], string regNo);
int whereIsPresent(string codeList[], string courseCode);
int whereCourseIsPresentInStdList(string stdCourseList[][20], string courseCode, int i);
string triming(string Name);

int TotalCourses = 0;     // Made a global variable so all functions can access it and change it.
int TotalStudents = 0;   // Made a global variable so all functions can access it and change it. registered

int main()
{
  int option, choice; // For switch statement.
  int crdHrs, semester;
  string password, username, courseCode, courseName, studentName, regNo;
  int crtHrsList[100], semList[100];                                         // For testing Phase it is 1000.
  string codeList[100], nameList[100], usersList[100], passwordsList[100], stdNamesList[100], stdRegNoList[100];
  string stdCourseList[100][20];    // For testing Phase it is 100.
  bool LoggedIn = false, NeedToRepeat = true;

  if (!(loadAllData (codeList, nameList, crtHrsList, semList, usersList, passwordsList, stdNamesList, stdRegNoList, stdCourseList)))
     return 0;

  cout << setw(80) << "** Welcome to University Learning Management System **\n"
       << " Dear User, current software is intended for authorized users only.\n"
       << " Login to the system to get access....\n\n";

  do
  {
    cout << " Choose the option for Login\n 1 for Admin\n 2 for Student\n Enter Option: ";
    cin >> choice;

    if (cin.peek() != '\n')
      handleInputFailure();

    switch (choice)
    {
      case 1:
        do
        {
          if (!(LoggedIn))
          {
            do
            {
              LoggedIn = true;

              cout << "\n Username: ";
              cin >> username;
              cout << " Password: ";
              cin >> password;

              if (cin.peek() != '\n')
                handleInputFailure();
            } while (!(isUserDataValid (usersList, passwordsList, triming(username), password)));    //Loop will continue until user enters correct info. // loadUsers (usersList, passwordsList) == false;
            cout << "\n You have successfully logged into the system.\n";
          }
          cout << "\n Choose the following option\n"
               << " 1\tAdd Course \n 2\tUpdate Course \n 3\tDelete Course \n 4\tView All Courses \n 5\tView Courses of a Semester"
               << "\n 6\tAdd New Student \n 7\tUpdate Student \n 8\tDelete Student \n 9\tView All Students"
               << "\n 10\tRegister the course for student \n 11\tUnregister the course for student"
               << "\n 12\tLogout of the system \n 13\tExit Program\n"   // Menu of ULMS.
               << "\n\n Choose the option: ";
          cin >> option;

          if (cin.peek() != '\n')
          {
            option = 0;
            handleInputFailure();
          }

          switch (option)
          {
            case 0:
              cout << " You Entered an INVALID Input (No Spaces or Alphabets after number) and Seriously, have you not read the Menu?\n"
                   << " Read it Clearly and Execute (Choose) the option.\n";
            break;
                 // Case 1..................... ADD COURSE
            case 1:
              do
              {
                NeedToRepeat = true;

                cout << "\n Enter the details of the Course. ";       // Entering the Course detail you want to Add.
                courseInput(courseCode, crdHrs, semester, courseName);

                if (isInputDataValid(courseCode, crdHrs, semester, courseName))              // To Check is All Data Valid at Same Time.
                {
                  if (!(isCourseAlreadyPresent(codeList, courseCode)))               // To Check the Presence of Code.
                  {
                    AddCourse(codeList, nameList, crtHrsList, semList, courseCode, courseName, crdHrs, semester);
                    NeedToRepeat = false;
                    cout << " Course has been added successfully\n";
                  }
                  else
                    cout << " Course Code is Already Present.\n You can not Add Course if Course Code is Already Present\n";
                }
                else
                  cout << " Course can not be Added.\n";

                if (cin.fail())
                  handleInputFailure();
              } while (NeedToRepeat);
            break;
                  // Case 2..................... EDIT COURSE
            case 2:
              do
              {
                string CourseCodeToEdit;
                NeedToRepeat = true;

                if (nonZeroTotalCourses())
                {
                  cout << "\n Enter the Course Code to Edit: ";
                  cin >> courseCode;

                  courseName = triming(courseCode);

                  if (isCourseAlreadyPresent(codeList, courseCode))
                  {
                    CourseCodeToEdit = courseCode;
                    
                    cout << " Enter the new details of the course: "; // Getting Details of New Course.
                    courseInput(courseCode, crdHrs, semester, courseName);

                    if (isInputDataValid (courseCode, crdHrs, semester, courseName) && (CourseCodeToEdit == courseCode)) // To Check is All Data Valid at Same Time.
                    {
                      EditCourse(codeList, nameList, crtHrsList, semList, courseCode, courseName, crdHrs, semester);
                      NeedToRepeat = false;
                      cout << " Course has been Edited successfully.\n";
                    }
                    else
                    {
                      if (CourseCodeToEdit != courseCode)
                        cout << " To Edit Course Code Should be Same.you can't change Course Code.\n";
                      cout << " Course can not be Edit.\n";
                    }
                  }
                  else
                    cout << " Course Code is Not Present.\n You can not Edit Course if Course Code is Not Present.\n";
                }
                else
                  NeedToRepeat = false;

                if (cin.fail())
                  handleInputFailure();
              } while (NeedToRepeat);
            break;
                 // Case 3.....................DELETE COURSE
            case 3:
              do
              {
                NeedToRepeat = true;

                if (nonZeroTotalCourses())
                {
                  cout << "\n Enter the Course Code to Delete: ";
                  cin >> courseCode;

                  courseCode = triming(courseCode);

                  if (isCourseAlreadyPresent(codeList, courseCode)) // If Position lies in Array of codeList[].
                  {
                    DeleteCourse(codeList, nameList, crtHrsList, semList, courseCode);
                    toUnRegisterAllStudent(stdCourseList, courseCode);    // To Unregister all Students from that course as We Delete it.
                    NeedToRepeat = false;
                    cout << " Course has been Deleted successfully.\n";
                  }
                  else
                    cout << " Course Code is Not Present.\n You can not Deleted Course if Course Code is Not Present\n";
                }
                else
                  NeedToRepeat = false;

                if (cin.fail())
                  handleInputFailure();
                
              } while (NeedToRepeat);
            break;
                 // Case 4.....................VIEW ALL COURSES
            case 4:
              if (nonZeroTotalCourses())
                ViewCourses(codeList, nameList, crtHrsList, semList);
            break;
                // Case 5.....................VIEW SEMESTER COURSES
            case 5:
              do
              {
                NeedToRepeat = true;

                if (nonZeroTotalCourses())
                {
                  cout << "\n Enter the Semester: ";
                  cin >> semester;

                  if (isValidSemester(semester)) // To Check the Validity of Semester.
                  {
                    ViewSemesterCourses(codeList, nameList, crtHrsList, semList, semester);
                    NeedToRepeat = false;
                  }
                  else        // If Semester is not Valid.
                    cout << " That is not a Valid Semester.\n";
                }
                else
                  NeedToRepeat = false;

                if (cin.fail())
                  handleInputFailure();
              } while (NeedToRepeat);
            break;
                  // Case 6.....................ADD STUDENT
            case 6:
              do
              {
                NeedToRepeat = true;

                cout << "\n Enter details of Student: ";
                
                studentInput(regNo, studentName);

                if (isValidRegistrationNumber (regNo))
                  if (isValidStudentName(studentName))
                  {
                    if ( !(isRegNoAlreadyPresent(stdRegNoList, regNo)) )
                    {
                      AddStudent (stdNamesList, stdRegNoList, studentName, regNo);
                      NeedToRepeat = false;
                      cout << " Student has been added successfully.\n";
                    }
                    else
                      cout << " Registration Number is Already Present.\n"
                           << " You can not Add Student if Registration Number is Already Present\n";
                  }

                if (cin.fail())
                  handleInputFailure();
              } while (NeedToRepeat);
            break;
                   // Case 7.....................EDIT STUDENT
            case 7:
              do
              {
                string regNoToEdit;

                NeedToRepeat = true;

                if (nonZeroTotalStudents())
                {
                  cout << "\n Enter Registration Number of the student to edit: ";
                  cin >> regNo;

                  regNo = triming(regNo);

                  if (isRegNoAlreadyPresent (stdRegNoList, regNo))
                  {
                    regNoToEdit = regNo;

                    cout << "\n Enter New details of Student: ";
                    studentInput(regNo, studentName);

                    if (isValidRegistrationNumber (regNo))        // To Check is All Data Valid at Same Time.
                      if (isValidStudentName(studentName))
                      {
                        if ( (regNoToEdit == regNo) )
                        {
                          UpdateStudent(stdNamesList, stdRegNoList, studentName, regNo);
                          NeedToRepeat = false;
                          cout << " Student has been Edited successfully.\n";
                        }
                        else
                          cout << " You can't change Registration Number to Edit a student.\n";
                      }
                  }
                  else
                    cout << " You can not Edit Student if his Registration Number is Not Present.\n";
                }
                else
                  NeedToRepeat = false;

                if (cin.fail())
                  handleInputFailure();
              } while (NeedToRepeat);
            break;
                 // Case 8.....................DELETE STUDENT
            case 8:
              do
              {
                NeedToRepeat = true;

                if (nonZeroTotalStudents())
                {
                  cout << "\n Enter Registration Number of the Student to Delete: ";
                  cin >> regNo;

                  regNo = triming(regNo);

                  if (isValidRegistrationNumber (regNo))
                    if (isRegNoAlreadyPresent (stdRegNoList, regNo)) // If Position lies in Array of codeList[].
                    {
                      DeleteStudent (stdNamesList, stdRegNoList, stdCourseList, regNo);
                      NeedToRepeat = false;
                      cout << " Student has been deleted successfully.\n";
                    }
                    else
                      cout << " Registration Number is Not Present.\n"
                           << " You can not Delete Student if his Registration Number is Not Present.\n";
                }
                else
                  NeedToRepeat = false;

                if (cin.fail())
                  handleInputFailure();
              } while (NeedToRepeat);
            break;
                 // Case 9.....................VIEW ALL STUDENTS
            case 9:
              if ( nonZeroTotalStudents() )
                ViewStudents(stdNamesList, stdRegNoList, stdCourseList);
            break;
                  // Case 10.....................REGISTER COURSE
            case 10:
              do
              {
                NeedToRepeat = true;

                if ((nonZeroTotalCourses()) && (nonZeroTotalStudents()))
                {
                  cout << "\n Enter Registration Number of the student for course registration: ";
                  cin >> regNo;

                  regNo = triming(regNo);

                  if (isValidRegistrationNumber (regNo))
                  {
                    if (isRegNoAlreadyPresent (stdRegNoList, regNo))
                    {
                      cout << " Enter Course Code to register: ";
                      cin >> courseCode;

                      courseCode = triming(courseCode);

                      if (isValidCourseCode (courseCode))
                      {
                        if (!(isStudentAlreadyRegistered (stdRegNoList, stdCourseList, regNo, courseCode)))
                        {
                          RegisterCourse (stdRegNoList, stdCourseList, codeList, regNo, courseCode);
                          NeedToRepeat = false;
                        }
                        else
                          cout << " Student ( Reg. No: " << regNo << " ) is Already Registered in this Course.\n";
                      }
                    }
                    else
                      cout << " Registration Number is not Present.\n Course can't be Registered.\n";
                  }
                }
                else
                  NeedToRepeat = false;

                if (cin.fail())
                  handleInputFailure();
              } while (NeedToRepeat);
            break;
                 // Case 11.....................UNREGISTER COURSE
            case 11:
              do
              {
                NeedToRepeat = true;

                if ((nonZeroTotalCourses()) && (nonZeroTotalStudents()))
                {
                  cout << "\n Enter registration Number of the student: ";
                  cin >> regNo;

                  regNo = triming(regNo);

                  if (isValidRegistrationNumber (regNo))
                  {
                    if (isRegNoAlreadyPresent (stdRegNoList, regNo))
                    {
                      cout << " Enter Course Code to unregister: ";
                      cin >> courseCode;

                      courseCode = triming(courseCode);

                      if (isValidCourseCode (courseCode))
                        if (isStudentAlreadyRegistered (stdRegNoList, stdCourseList, regNo, courseCode))
                        {
                          UnRegisterCourse(stdRegNoList, stdCourseList, codeList, regNo, courseCode);
                          NeedToRepeat = false;
                        }
                        else
                          cout << " Student ( Reg. No: " << regNo << " ) is Already Not Registered in this Course.\n";
                    }
                    else
                      cout << " Registration Number is not Present.\n Course can't be Registered.\n";
                  }
                }
                else
                  NeedToRepeat = false;

                if (cin.fail())
                  handleInputFailure();
              } while (NeedToRepeat);
            break;
                 // Case 12.....................LOGOUT
            case 12:
             {
              cout << " You have logged out from the system.\n\n\n";
              LoggedIn = false;
             }
            break;
                  // Case 13.....................EXIT PROGRAM
            case 13:
            {
              if (saveCourses (codeList, nameList, crtHrsList, semList) &&  saveStudents (stdNamesList, stdRegNoList, stdCourseList))
                cout << "\n All Changes have saved.\n Goodbye..................\n Hope you are Satisfied by this Application.\n";
              else
               cout << "\n Data can't be saved.\n Anyways, Goodbye.......\n";

              return 0;
            }
                            // Default...................
            default:
              cout << "\n Dude, are you blind? That was not in options.\n";
          }
        } while (option != 12);
      break;

      case 2:
      {
        do
        {
          cout << "\n\n Enter registration Number: ";
          cin >> regNo;
          cout << " Enter Password: ";
          cin >> password;
        } while (!isValidInputDetails (stdNamesList, stdRegNoList, password, triming(regNo)));

        do
        {
          cout << "\n\n Enter 1 to View Registered Course\n Enter 2 to Logout of the System\n Enter 3 to Exit\n";
          cout << " Choose Option: ";
          cin >> option;

          if (cin.peek() != '\n')
            handleInputFailure();

          switch (option)
          {
            case 1:
              ViewLoggedStudent(stdNamesList, stdRegNoList, stdCourseList, regNo);
            break;

            case 2:
              cout << " You have logged out from the system.\n\n\n";
            break;

            case 3:
            {
              cout << " Goodbye..................\n Hope you are Satisfied by this Application.\n";
                return 0;
            }
            break;

            default:
              cout << "\n Dude, are you blind? That was not in options.\n";
          }
        } while (option != 2);
      }
      break;

      default:
        cout << "\n Dude, are you blind? That was not in options.\n\n";
    }
  } while (true);
}
                                   /******************************
                                     Functions in Manual..........
                                    ******************************/
// To check the Validity of Course Code you entered.
bool isValidCourseCode(string courseCode)
{
  courseCode = triming(courseCode);     // Storing name in same string after removing unnecessary spaces.

  if (regex_match (courseCode, regex("^[A-Z]{2}[0-9]{3}$")))
    return true; 
  
  cout << " Course Code is INVALID.\n";
  return false;
}
      // To check the Validity of Course Name you entered.
bool isValidCourseName(string name)
{
  if (name.size() > 50)
  {
    cout << " Course Name Exceeds the Limit.\n";
    return false;
  }
  
  if (regex_match (name, regex("^[A-Za-z ()]{1,50}$")))
      return true;
  
  cout << " Course Name is INVALID.\n";
  return false;
}

// To check the Validity of Course Credit Hours you entered.
bool isValidCreditHours(int crdHrs)
{
  if (crdHrs > 0 && crdHrs < 4)
    return true;
  
  cout << " Course Credit Hours are INVALID.\n";
  return false;
}

// To check the Validity of Semester you entered.
bool isValidSemester(int semester)
{
  if (semester > 0 && semester < 9)
    return true;

  cout << " Semester is INVALID.\n";
  return false;
}

bool saveCourses(string codeList[], string nameList[], int crtHrsList[], int semList[])
{
  ofstream CoursesDataFile;
  CoursesDataFile.open("Courses.txt");

  if (CoursesDataFile.fail())
  {
    cout << " Courses Data File is not present.\n";
    return false;
  }

  for (int i = 0; i < TotalCourses; i++)
  {
    CoursesDataFile << codeList[i] << ",";
    CoursesDataFile << nameList[i] << ",";
    CoursesDataFile << crtHrsList[i] << ",";
    CoursesDataFile << semList[i] << "\n";
  }
  CoursesDataFile.close();
  return true;
}

bool loadCourses(string codeList[], string nameList[], int crtHrsList[], int semList[])
{
  ifstream CoursesDataFile;
  CoursesDataFile.open("Courses.txt");

  if (CoursesDataFile.fail())
  {
    cout << " Courses Data File is not present.\n";
    return false;
  }

  while (!(CoursesDataFile.eof())) // To avoid taking any empty line.
  {
    getline(CoursesDataFile, codeList[TotalCourses], ',');
    getline(CoursesDataFile, nameList[TotalCourses], ',');
    CoursesDataFile >> crtHrsList[TotalCourses];
    CoursesDataFile.ignore(1, ','); // To ignore the Comma.
    CoursesDataFile >> semList[TotalCourses];
    CoursesDataFile.ignore(1, ' ');  // To ignore to format error.

    TotalCourses++;
  }
  CoursesDataFile.close();
  return true;
}

bool loadUsers(string usersList[], string passwordsList[])
{
  int i = 0;

  ifstream UserDataFile;
  UserDataFile.open("Users.txt");

  if (UserDataFile.fail())
  {
    cout << " Sorry, we are unable to run the program, as user data does not exist.\n";
    return false;
  }

  while (!((UserDataFile.eof()) || (UserDataFile.peek() == '\n')))   // (UserDataFile.peek() == '\n') is used to avoid taking any empty line.
  {
    getline(UserDataFile, usersList[i], ',');
    getline(UserDataFile, passwordsList[i], '\n');
    i++;
  }
  UserDataFile.close();
  return true;
}

bool isValidRegistrationNumber(string regNo)
{
  if (regex_match (regNo, regex("^201[0-9]-[A-Z]{2,3}-[1-9]{1,3}$")))
    return true; 
  cout << " INVALID Registration Number.\n";
  return false;
}

bool isValidStudentName(string studentName)
{
  if (regex_match (studentName, regex("^([A-Za-z ])+$")))
    return true; 
  cout << "  Student Name is INVALID.\n";
  return false;
}

bool saveStudents(string stdNamesList[], string stdRegNoList[], string stdCourseList[][20])
{
  ofstream StudentDataFile;
  StudentDataFile.open("Students.txt");

  if (StudentDataFile.fail())
  {
    cout << " Sorry, we are unable to run the program, as Student Registered Courses data does not exist.\n";
    return false;
  }

  for (int i=0; i < TotalStudents; i++)
  {
    StudentDataFile << stdRegNoList[i] << "," << stdNamesList[i] << "\n";

    for (int j=0; stdCourseList[i][j] != "\0"; j++)
    {
      StudentDataFile <<  stdCourseList[i][j];

      if (stdCourseList[i][j+1] != "\0")
        StudentDataFile <<  ",";
    }
    StudentDataFile << "\n";
  }
  StudentDataFile.close();
}

bool loadStudents( string stdNamesList[], string stdRegNoList[],string stdCourseList[][20])
{
  string regCourses;

  ifstream StudentDataFile;
  StudentDataFile.open("Students.txt");

  if (StudentDataFile.fail())
  {
    cout << " Sorry, we are unable to run the program, as Student Registered Courses data does not exist.\n";
    return false;
  }

  while (!(StudentDataFile.eof()) ) // To avoid taking any empty line.
  {
    getline (StudentDataFile, stdRegNoList[TotalStudents], ',');
    getline (StudentDataFile, stdNamesList[TotalStudents], '\n');
    getline (StudentDataFile, regCourses, '\n');

    if (!(stdRegNoList[TotalStudents].empty()))
    {
      putInstdCourseList (stdCourseList, regCourses);
      TotalStudents ++;
    }
  }
  StudentDataFile.close();
  return true;
}

void AddCourse(string codeList[], string nameList[], int crtHrsList[], int semList[], string courseCode, string courseName, int crdHrs, int semester)
{
  codeList[TotalCourses] = courseCode;
  crtHrsList[TotalCourses] = crdHrs;
  semList[TotalCourses] = semester;
  nameList[TotalCourses] = courseName; // To remove the Extra spaces from start and end only.

  TotalCourses++; // Increasing the Numbers of Total Courses Stored in Array.
}

void EditCourse(string codeList[], string nameList[], int crtHrsList[], int semList[], string courseCode, string courseName, int crdHrs, int semester)
{
  int Position = whereIsPresent(codeList, courseCode);
     // Editing Desired Data.
  codeList[Position] = courseCode;
  crtHrsList[Position] = crdHrs;
  semList[Position] = semester;
  nameList[Position] = courseName; // To remove the Extra spaces from start and end only.
}

void DeleteCourse(string codeList[], string nameList[], int crtHrsList[], int semList[], string courseCode)
{
  int Position = whereIsPresent(codeList, courseCode);

  for (int i = Position; i < TotalCourses; i++)  // Deleting Desired Data.
  {
    codeList[i] = codeList[i + 1];
    crtHrsList[i] = crtHrsList[i + 1];
    semList[i] = semList[i + 1];
    nameList[i] = nameList[i + 1];
  }
  TotalCourses--; // Decreasing the Numbers of Total Courses Stored in Array.
}

void ViewCourses(string codeList[], string nameList[], int crtHrsList[], int semList[])
{
  cout << setw(19) << "Course Code" << setw(9) << "Name" << setw(63) << "Credit Hours" << setw(15) << "Semester\n";

  for (int i = 0; i < TotalCourses; i++) // Viewing All Stored Data.
    cout << setw(13) << codeList[i] << "\t        " << nameList[i]
         << setw(57 - nameList[i].size()) << crtHrsList[i] << "\t\t   " << semList[i] << "\n";
}

void ViewSemesterCourses(string codeList[], string nameList[], int crtHrsList[], int semList[], int semester)
{
  bool flag = true;

  cout << setw(19) << "Course Code" << setw(9) << "Name" << setw(63) << "Credit Hours\n";

  for (int i = 0; i < TotalCourses; i++)
    if (semList[i] == semester)
    {
      flag = false;
      cout << setw(13) << codeList[i] << "\t        " << nameList[i] << setw(57 - nameList[i].size()) << crtHrsList[i] << "\n";
    }
  
  if (flag) // If there is no Course in Semester.
    cout << "\n There are no Courses in semester " << semester << ".\n";
}

void AddStudent(string stdNamesList[], string stdRegNoList[], string studentName, string regNo)
{
  stdNamesList[TotalStudents] = triming(studentName);
  stdRegNoList[TotalStudents] = triming(regNo);
  TotalStudents++;
}

void UpdateStudent(string stdNamesList[], string stdRegNoList[], string studentName, string regNo)
{
  int Position = whereIsPresent (stdRegNoList, regNo);
  stdNamesList[Position] = triming(studentName);
  stdRegNoList[Position] = triming(regNo);
}

void DeleteStudent(string stdNamesList[], string stdRegNoList[], string stdCourseList[][20], string regNo)
{
  int Position = whereIsPresent (stdRegNoList, regNo);

  for (int i = Position; i < TotalStudents; i++ )                                       // Deleting Whole row of 2D Array.
  {
    stdNamesList[i] = stdNamesList[i + 1];
    stdRegNoList[i] = stdRegNoList[i + 1];

    for (int j=0; j < 20; j++)
      stdCourseList[i][j] = stdCourseList[i+1][j];
  }
  TotalStudents--;       // Decreasing the Numbers of Total Students Stored in Array.
}

void ViewStudents(string stdNamesList[], string stdRegNoList[], string stdCourseList[][20])
{
  cout << setw(27) << "Registration Number" << setw(17) << "Student Name" << setw(45) << "Registered Courses\n";

  for (int i=0; i < TotalStudents; i++ )
  {
    cout << setw (19) << stdRegNoList[i] << "\t\t" << stdNamesList[i] << setw (44 - stdNamesList[i].size());     // To set Format,

    for (int j=0; stdCourseList[i][j] != "\0"; j++)
    {
      cout << stdCourseList[i][j];

      if ( stdCourseList[i][j+1] != "\0")
        cout << ", ";
    }
      cout << "\n";
  }
}

void RegisterCourse (string stdRegNoList[], string stdCourseList[][20], string codeList[], string regNo, string courseCode)
{
  if ( isCourseAlreadyPresent (codeList,courseCode) )
  {
    int Position = whereIsPresent(stdRegNoList, regNo);      // To find Correct Row.
    int i = 0;

    while ( stdCourseList[Position][i] != "\0")
      i++;                                               // To find Correct Column.

    stdCourseList [Position][i] = courseCode;
    cout << " Course has been Registered for Student.\n";
  }
  else
    cout << " Course Code does not Exist.\n Student can't be Registered.\n";
}

void UnRegisterCourse(string stdRegNoList[], string stdCourseList[][20], string codeList[], string regNo, string courseCode)
{
  if ( isCourseAlreadyPresent (codeList,courseCode) )
  {
    int Position = whereIsPresent(stdRegNoList, regNo);            // To find Correct Row.
    int i = 0;

    while (stdCourseList[Position][i] != courseCode)
      i++;                                               // To find Correct Column.

    while (stdCourseList[Position][i] != "\0")
    {
      stdCourseList[Position][i] = stdCourseList[Position][i+1];
      i++;
    }
    cout << " Course has been Un-Registered for Student.\n";
  }
  else
    cout << " Course Code does not Exist.\n Student can't be Un-Registered.\n";
}

                             /*************************************************
                              Function I made for my Simplicity...............
                             *************************************************/
      // To Check that are all data that is taken from user is Valid by sending it into Different Function.
bool isInputDataValid(string courseCode, int crdHrs, int semester, string courseName)
{
  if (isValidCourseCode(courseCode) && isValidCreditHours(crdHrs))
    if (isValidSemester(semester) && isValidCourseName(courseName))
          return true;
  return false;
}
                  // To Check Course id Present.
bool isCourseAlreadyPresent(string codeList[], string courseCode)
{
  for (int i = 0; i < TotalCourses; i++)
    if (codeList[i] == courseCode) // If course Code Found.
      return true;
  return false;
}

bool isUserDataValid(string usersList[], string passwordsList[], string username, string password)
{
  for (int i = 0; usersList[i] != "\0"; i++)
    if ((usersList[i] == username) && (passwordsList[i] == password))
      return true;
  cout << "\n Dear User, Username/password is incorrect.\n Enter the username/password again to get access to the system.\n";
  return false;
}

bool loadAllData(string codeList[], string nameList[], int crtHrsList[], int semList[], string usersList[], string passwordsList[], string stdNamesList[], string stdRegNoList[], string stdCourseList[][20])
{
  if (loadCourses(codeList, nameList, crtHrsList, semList) && loadUsers (usersList, passwordsList))
    if (loadStudents (stdNamesList, stdRegNoList, stdCourseList))
      return true;
  return false;
}

bool isRegNoAlreadyPresent(string stdRegNoList[], string regNo)
{
  for (int i = 0; i < TotalStudents; i++)
    if (stdRegNoList[i] == regNo) // If Registration Number Found.
      return true;
  return false;
}

bool isStudentAlreadyRegistered (string stdRegNoList[], string stdCourseList[][20], string regNo, string courseCode)
{
  int Position = whereIsPresent(stdRegNoList, regNo);

  for (int i=0; stdCourseList[Position][i] != "\0"; i++)
    if (stdCourseList[Position][i] == courseCode)
      return true;
  return false;
}

bool nonZeroTotalCourses()
{
  if ( TotalCourses > 0)
    return true;
  cout << " There is No Course present to complete the Process.\n Add them by selecting \"Add Course\" option.\n";
  return false;
}

bool nonZeroTotalStudents()
{
  if (TotalStudents > 0)
    return true;
  cout << " There is No Student present to complete the Process.\n Add them by selecting \"Add NewStudent\" option.\n";
  return false;
}

bool isValidInputDetails(string stdNamesList[], string stdRegNoList[], string password, string regNo)
{
  int position = whereIsPresent(stdRegNoList, regNo);
  int length = stdNamesList[position].size();
  string stdName = stdNamesList[position];

  if ( isValidRegistrationNumber (regNo) )
    if ( isRegNoAlreadyPresent (stdRegNoList, regNo) )
    {
      if (password.size() == 3)
        if (stdName[length-3] == password[0] && stdName[length-2] == password[1] && stdName[length-1] == password[2])
          return true;
    }
    else
    {
      cout << " You are not added to this UNIVERSITY.\n";
      return false;
    }
  cout << " INVALID Password....\n";
  return false;
}

void courseInput(string &courseCode, int &crdHrs, int &semester, string &courseName)
{
  cout << "\n Course Code : ";
  cin >> courseCode;
  cout << "\n Course Credit Hours : ";
  cin >> crdHrs;
  cout << "\n Course semester : ";
  cin >> semester;
  cout << "\n Course Name : ";
  getline(cin, courseName);                        // As Course Name Contains spaces.

  courseCode = triming(courseCode);
  courseName = triming(courseName);
}

void studentInput(string &regNo, string &studentName)
{
  cout << "\n Enter Register Number : ";
  cin >> regNo;
  cout << "\n Enter Student Name : ";
  getline (cin, studentName);

  regNo = triming(regNo);
  studentName = triming(studentName);
}

void handleInputFailure()
{
  cin.clear(); // To safe your code from Input Failure.
  cin.ignore(500, '\n');
  cout << "\n\n";
}

void toUnRegisterAllStudent(string stdCourseList[][20], string courseCode)
{
  for (int i=0; stdCourseList[i][0] != "\0"; i++)
    for (int j=whereCourseIsPresentInStdList (stdCourseList, courseCode, i); stdCourseList[i][j] != "\0"; j++)
      stdCourseList[i][j] = stdCourseList[i][j+1];
}

void putInstdCourseList(string stdCourseList[][20], string regCourses)
{
 int i=0, j=0, m = 5;

  while (i != (regCourses.size() / 5))
  {
    while ((j % m != 0) || (j == 0))
    {
      stdCourseList[TotalStudents][i] += regCourses [j];
      j++;
    }
    j++;
    i++;
    m += 6;
  }
}

void ViewLoggedStudent(string stdNamesList[], string stdRegNoList[], string stdCourseList[][20], string regNo)
{
  int position = whereIsPresent(stdRegNoList, regNo);

  cout << setw(27) << "Registration Number" << setw(17) << "Student Name" << setw(45) << "Registered Courses\n"
       << setw (19) << stdRegNoList[position] << "\t\t" << stdNamesList[position]
       << setw (44 - stdNamesList[position].size());     // To set Format,

  for (int j=0; stdCourseList[position][j] != "\0"; j++)
  {
    cout << stdCourseList[position][j];

    if ( stdCourseList[position][j+1] != "\0")
      cout << ", ";
  }
  cout << "\n\n";
}

int whereIsPresent(string List[], string Find) // To Find where Course Code/Student Registration Number is Present.
{
  for (int i = 0; i < TotalCourses; i++)
    if (List[i] == Find) 
      return i;
}

int whereCourseIsPresentInStdList(string stdCourseList[][20], string courseCode, int i)
{
  int j = 0;

  while (stdCourseList[i][j] != courseCode)
    j++;

  return j;
}

string triming(string Name) // To remove the Extra spaces.
{
  Name.erase(0, Name.find_first_not_of(" \t"));
  
  int length = Name.find_last_not_of(" \t");

  if (string::npos != length)
    Name.erase(length + 1);

  return Name;
}
