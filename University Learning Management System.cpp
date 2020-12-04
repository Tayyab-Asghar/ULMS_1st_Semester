#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

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
void handleInputFailure();
void toUnRegisterAllStudent(string stdCourseList[][20], string courseCode);
void putInstdCourseList(string stdCourseList[][20], string regCourses);
void ViewLogedStudent(string stdNamesList[], string stdRegNoList[], string stdCourseList[][20], string regNo);
int whereCodeIsPresent(string codeList[], string courseCode);
int whereRegNoIsPresent(string stdRegNoList[], string regNo);
int whereToPlaceCourse(string stdCourseList[][20], int Position);
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

  if ( !(loadAllData (codeList, nameList, crtHrsList, semList, usersList, passwordsList, stdNamesList, stdRegNoList, stdCourseList)) )
   {
     return 0;
   }

  cout << setw(80) << "** Welcome to University Learning Management System **" << endl;
  cout << " Dear User, current software is intended for authorized users only." << endl;
  cout << " Login to the system to get access...." << endl << endl;

  do
   {
    cout << " Choose the option for Login" << endl;
    cout << " 1 for Admin\n 2 for Student" << endl;
    cout << " Enter Option: ";
    cin >> choice;

    if (cin.peek() != '\n')
     {
      handleInputFailure();
     }

    switch (choice)
     {
      case 1:
       {
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
               {
                handleInputFailure();
               }
             }
            while ( !(isUserDataValid (usersList, passwordsList, username, password)) );    //Loop will continue until user enters correct info. // loadUsers (usersList, passwordsList) == false;

            cout << "\n You have successfully logged into the system." << endl;
           }

          cout << "\n Choose the following option" << endl;
          cout << " 1\tAdd Course \n 2\tUpdate Course \n 3\tDelete Course \n 4\tView All Courses \n 5\tView Courses of a Semester"
               << "\n 6\tAdd New Student \n 7\tUpdate Student \n 8\tDelete Student \n 9\tView All Students"
               << "\n 10\tRegister the course for student \n 11\tUnregister the course for student"
               << "\n 12\tLogout of the system \n 13\tExit Program" << endl; // Menu of ULMS.
          cout << "\n\n Choose the option: ";
          cin >> option;

          if (cin.peek() != '\n')
           {
            option = 0;

            handleInputFailure();
           }

          switch (option)
           {
            case 0:
             {
              cout << " You Entered an INVALID Input (No Spaces or Alphabets after number) and Seriously, have you not read the Menu?" << endl;
              cout << " Read it Clearly and Execute (Choose) the option." << endl;
             }
            break;
                 // Case 1..................... ADD COURSE
            case 1:
             {
              do
               {
                NeedToRepeat = true;

                cout << "\n Enter the details of the Course: ";             // Entering the Course detail you want to Add.
                cin >> courseCode >> crdHrs >> semester;
                getline(cin, courseName);                        // As Course Name Contains spaces.

                if (isInputDataValid(courseCode, crdHrs, semester, courseName))              // To Check is All Data Valid at Same Time.
                 {
                  if ( !(isCourseAlreadyPresent(codeList, courseCode)) )               // To Check the Presence of Code.
                   {
                    AddCourse(codeList, nameList, crtHrsList, semList, courseCode, courseName, crdHrs, semester);
                    NeedToRepeat = false;

                    cout << " Course has been added successfully" << endl;
                   }

                  else
                   {
                    cout << " Course Code is Already Present." << endl;
                    cout << " You can not Add Course if Course Code is Already Present" << endl;
                   }
                 }

                else
                 {
                  cout << " Course can not be Added." << endl;
                 }

                if (cin.fail())
                 {
                  handleInputFailure();
                 }
               }
              while (NeedToRepeat);
             }
            break;
                  // Case 2..................... EDIT COURSE
            case 2:
             {
              string coureCodeToEdit;

              do
               {
                string CourseCodeToEdit;

                NeedToRepeat = true;

                if ( nonZeroTotalCourses() )
                 {
                  cout << "\n Enter the Course Code to Edit: ";
                  cin >> courseCode;

                  if (isCourseAlreadyPresent(codeList, courseCode))
                   {
                    CourseCodeToEdit = courseCode;

                    cout << " Enter the new details of the course: "; // Getting Details of New Course.
                    cin >> courseCode >> crdHrs >> semester;
                    getline(cin, courseName);

                    if ( isInputDataValid (courseCode, crdHrs, semester, courseName) && (CourseCodeToEdit == courseCode) ) // To Check is All Data Valid at Same Time.
                     {
                      EditCourse(codeList, nameList, crtHrsList, semList, courseCode, courseName, crdHrs, semester);

                      NeedToRepeat = false;

                      cout << " Course has been Edited successfully." << endl;
                     }

                    else
                     {
                      if (CourseCodeToEdit != courseCode)
                       {
                        cout << " To Edit Course Code Should be Same.you can't change Course Code." << endl;
                       }
                      cout << " Course can not be Edit." << endl;
                     }
                   }

                  else
                   {
                    cout << " Course Code is Not Present." << endl;
                    cout << " You can not Edit Course if Course Code is Not Present." << endl;
                   }
                 }

                else
                 {
                  NeedToRepeat = false;
                 }

                if (cin.fail())
                 {
                  handleInputFailure();
                 }
               }
              while (NeedToRepeat);
             }
            break;
                 // Case 3.....................DELETE COURSE
            case 3:
             {
              do
               {
                NeedToRepeat = true;

                if ( nonZeroTotalCourses() )
                 {
                  cout << "\n Enter the Course Code to Delete: ";
                  cin >> courseCode;

                  if ( isCourseAlreadyPresent(codeList, courseCode) ) // If Position lies in Array of codeList[].
                   {
                    DeleteCourse(codeList, nameList, crtHrsList, semList, courseCode);
                    toUnRegisterAllStudent(stdCourseList, courseCode);    // To Unregister all Students from that course as We Delete it.

                    NeedToRepeat = false;

                    cout << " Course has been Deleted successfully." << endl;
                   }

                  else
                   {
                    cout << " Course Code is Not Present." << endl;
                    cout << " You can not Deleted Course if Course Code is Not Present" << endl;
                   }
                 }

                else
                 {
                  NeedToRepeat = false;
                 }

                if (cin.fail())
                 {
                  handleInputFailure();
                 }
               }
              while (NeedToRepeat);
             }
            break;
                 // Case 4.....................VIEW ALL COURSES
            case 4:
             {
              if ( nonZeroTotalCourses() )
               {
                ViewCourses(codeList, nameList, crtHrsList, semList);
               }
             }
            break;
                // Case 5.....................VIEW SMESTER COURSES
            case 5:
             {
              do
               {
                NeedToRepeat = true;

                if ( nonZeroTotalCourses() )
                 {
                  cout << "\n Enter the Semester: ";
                  cin >> semester;

                  if (isValidSemester(semester)) // To Check the Validity of Semester.
                   {
                    ViewSemesterCourses(codeList, nameList, crtHrsList, semList, semester);

                    NeedToRepeat = false;
                   }

                  else        // If Semester is not Valid.
                   {
                    cout << " That is not a Valid Semester." << endl;
                   }
                 }

                else
                 {
                  NeedToRepeat = false;
                 }

                if (cin.fail())
                 {
                  handleInputFailure();
                 }
               }
              while (NeedToRepeat);
             }
            break;
                  // Case 6.....................ADD STUDENT
            case 6:
             {
              do
               {
                NeedToRepeat = true;

                cout << "\n Enter details of Student: ";
                cin >> regNo;
                getline (cin, studentName);

                if (isValidRegistrationNumber (regNo))
                 {
                  if (isValidStudentName(studentName))
                   {
                    if ( !(isRegNoAlreadyPresent(stdRegNoList, regNo)) )
                     {
                      AddStudent (stdNamesList, stdRegNoList, studentName, regNo);

                      NeedToRepeat = false;

                      cout << " Student has been added successfully." << endl;
                     }

                    else
                     {
                      cout << " Registration Number is Already Present." << endl;
                      cout << " You can not Add Student if Registration Number is Already Present" << endl;
                     }
                   }
                 }

                if (cin.fail())
                 {
                  handleInputFailure();
                 }
               }
              while (NeedToRepeat);
             }
            break;
                   // Case 7.....................EDIT STUDENT
            case 7:
             {
              do
               {
                string regNoToEdit;

                NeedToRepeat = true;

                if ( nonZeroTotalStudents() )
                 {
                  cout << "\n Enter Registration Number of the student to edit: ";
                  cin >> regNo;

                  if ( isRegNoAlreadyPresent (stdRegNoList, regNo) )
                   {
                    regNoToEdit = regNo;

                    cout << " Enter details of Student: ";
                    cin >> regNo;
                    getline (cin, studentName);

                    if ( isValidRegistrationNumber (regNo) )        // To Check is All Data Valid at Same Time.
                     {
                      if(isValidStudentName(studentName) )
                       {
                        if ( (regNoToEdit == regNo) )
                         {
                          UpdateStudent(stdNamesList, stdRegNoList, studentName, regNo);

                          NeedToRepeat = false;

                          cout << " Student has been Edited successfully." << endl;
                         }

                        else
                         {
                          cout << " You can't change Registration Number to Edit a student." << endl;
                         }
                       }
                     }
                   }

                  else
                   {
                    cout << " You can not Edit Student if his Registration Number is Not Present." << endl;
                   }
                 }

                else
                 {
                  NeedToRepeat = false;
                 }

                if (cin.fail())
                 {
                  handleInputFailure();
                 }
               }
              while (NeedToRepeat);
             }
            break;
                 // Case 8.....................DELETE STUDENT
            case 8:
             {
              do
               {
                NeedToRepeat = true;

                if ( nonZeroTotalStudents() )
                 {
                  cout << "\n Enter Registration Number of the Student to Delete: ";
                  cin >> regNo;

                  if ( isValidRegistrationNumber (regNo) )
                   {
                    if ( isRegNoAlreadyPresent (stdRegNoList, regNo) ) // If Position lies in Array of codeList[].
                     {
                      DeleteStudent (stdNamesList, stdRegNoList, stdCourseList, regNo);

                      NeedToRepeat = false;

                      cout << " Student has been deleted successfully." << endl;
                     }

                    else
                     {
                      cout << " Registration Number is Not Present." << endl;
                      cout << " You can not Delete Student if his Registration Number is Not Present." << endl;
                     }
                   }
                 }

                else
                 {
                  NeedToRepeat = false;
                 }

                if (cin.fail())
                 {
                  handleInputFailure();
                 }
               }
              while (NeedToRepeat);
             }
            break;
                 // Case 9.....................VIEW ALL STUDENTS
            case 9:
             {
              if ( nonZeroTotalStudents() )
               {
                ViewStudents(stdNamesList, stdRegNoList, stdCourseList);
               }
             }
            break;
                  // Case 10.....................REGISTER COURSE
            case 10:
             {
              do
               {
                NeedToRepeat = true;

                if ( (nonZeroTotalCourses()) && (nonZeroTotalStudents()) )
                 {
                  cout << "\n Enter Registration Number of the student for course registration: ";
                  cin >> regNo;

                  if ( isValidRegistrationNumber (regNo) )
                   {
                    if ( isRegNoAlreadyPresent (stdRegNoList, regNo) )
                     {
                      cout << " Enter Course Code to register: ";
                      cin >> courseCode;

                      if ( isValidCourseCode (courseCode) )
                       {
                        if ( !(isStudentAlreadyRegistered (stdRegNoList, stdCourseList, regNo, courseCode)) )
                         {
                          RegisterCourse (stdRegNoList, stdCourseList, codeList, regNo, courseCode);

                          NeedToRepeat = false;
                         }

                        else
                         {
                          cout << " Student ( Reg. No: " << regNo << " ) is Already Registered in this Course." << endl;
                         }
                       }
                     }

                    else
                     {
                      cout << " Registration Number is not Present.\n Course can't be Registered." << endl;
                     }
                   }
                 }

                else
                 {
                  NeedToRepeat = false;
                 }

                if (cin.fail())
                 {
                  handleInputFailure();
                 }
               }
              while (NeedToRepeat);
             }
            break;
                 // Case 11.....................UNREGISTER COURSE
            case 11:
             {
              do
               {
                NeedToRepeat = true;

                if ( (nonZeroTotalCourses()) && (nonZeroTotalStudents()) )
                 {
                  cout << "\n Enter registration Number of the student: ";
                  cin >> regNo;

                  if ( isValidRegistrationNumber (regNo) )
                   {
                    if ( isRegNoAlreadyPresent (stdRegNoList, regNo) )
                     {
                      cout << " Enter Course Code to unregister: ";
                      cin >> courseCode;

                      if ( isValidCourseCode (courseCode) )
                       {
                        if ( isStudentAlreadyRegistered (stdRegNoList, stdCourseList, regNo, courseCode) )
                         {
                          UnRegisterCourse(stdRegNoList, stdCourseList, codeList, regNo, courseCode);

                          NeedToRepeat = false;
                         }

                        else
                         {
                          cout << " Student ( Reg. No: " << regNo << " ) is Already Not Registered in this Course." << endl;
                         }
                       }
                     }

                    else
                     {
                      cout << " Registration Number is not Present.\n Course can't be Registered." << endl;
                     }
                   }
                 }

                else
                 {
                  NeedToRepeat = false;
                 }

                if (cin.fail())
                 {
                  handleInputFailure();
                 }
               }
              while (NeedToRepeat);
             }
            break;
                 // Case 12.....................LOGOUT
            case 12:
             {
              cout << " You have logged out from the system." << endl << endl << endl;

              LoggedIn = false;
             }
            break;
                  // Case 13.....................EXIT PROGRAM
            case 13:
             {
              if (saveCourses (codeList, nameList, crtHrsList, semList) &&  saveStudents (stdNamesList, stdRegNoList, stdCourseList))
               {
                cout << "\n All Changes have saved." << endl;
                cout << " Goodbye..................\n Hope you are Satisfied by this Application." << endl;
               }

              else
               {
               cout << "\n Data can't be saved.\n Anyways, Goodbye......." << endl;
               }

                 return 0;
             }
                            // Default...................
            default:
             {
              cout << "\n Dude, are you blind? That was not in options." << endl;
             }
           }
         }
        while (option != 12);
       }
      break;

      case 2:
       {
        do
         {
          cout << "\n\n Enter registration Number: ";
          cin >> regNo;
          cout << " Enter Password: ";
          cin >> password;
         }
        while ( !isValidInputDetails (stdNamesList, stdRegNoList, password, regNo) );

        do
         {
          cout << "\n\n Enter 1 to View Registered Course\n Enter 2 to Logout of the System\n Enter 3 to Exit" << endl;
          cout << " Choose Option: ";
          cin >> option;

          if (cin.peek() != '\n')
           {
            handleInputFailure();
           }

          switch (option)
           {
            case 1:
             {
              ViewLogedStudent(stdNamesList, stdRegNoList, stdCourseList, regNo);
             }
            break;

            case 2:
             {
              cout << " You have logged out from the system." << endl << endl << endl;
             }
            break;

            case 3:
             {
              cout << " Goodbye..................\n Hope you are Satisfied by this Application." << endl;

                return 0;
             }
            break;

            default:
             {
              cout << "\n Dude, are you blind? That was not in options." << endl;
             }
           }
         }
        while (option != 2);
       }
      break;

      default:
       {
        cout << "\n Dude, are you blind? That was not in options." << endl << endl;
       }
     }
   }
  while (true);
}

                                   /******************************
                                     Functions in Manual..........
                                    ******************************/

// To check the Validity of Course Code you entered.
bool isValidCourseCode(string courseCode)
{
  if (courseCode.size() == 5) // Course Code should contain 5 charters.
   {
    // To check the validity of 1st code.
    if ((courseCode[0] >= 'A' && courseCode[0] <= 'Z'))
     {
      // To check the validity of 2nd code.
      if ((courseCode[1] >= 'A' && courseCode[1] <= 'Z'))
       {
        // To check the validity of 3rd code.
        if (isdigit (courseCode[2]) != 0)
         {
          // To check the validity of 4th code.
          if (isdigit (courseCode[3]) != 0)
           {
            // To check the validity of 5th code.
            if (isdigit (courseCode[4]) != 0)
             {
              return true;
             }
           }
         }
       }
     }
   }

  cout << " Course Code is INVALID." << endl;

  return false;
}

      // To check the Validity of Course Name you entered.
bool isValidCourseName(string name)
{
  name = triming(name);     // Storing name in same string after removing unnecessary spaces.

  if (name.empty())
   {
    cout << " Course Name Can't be Empty." << endl;

      return false;
   }

  if (name.size() <= 50) // Course name should be smaller than 50 charters.
   {
    for (int i = 0; i < name.size(); i++)
     {
      if ( !(isalpha (name[i]) || (name[i] == ' ') || (name[i] == '(') || (name[i] == ')')) )  // Course Name is consist of 3 different data types.
       {
        cout << " Course Name is INVALID." << endl;

        return false;
       }
     }

      return true;   // If string made out of loop.
   }
  cout << " Course Name Exceeds the Limit." << endl;

    return false;
}

// To check the Validity of Course Credit Hours you entered.
bool isValidCreditHours(int crdHrs)
{
  if (crdHrs > 0 && crdHrs < 4)
   {
    return true;
   }
  cout << " Course Credit Hours are INVALID." << endl;

    return false;
}

// To check the Validity of Semester you entered.
bool isValidSemester(int semester)
{
  if (semester > 0 && semester < 9)
   {
    return true;
   }
  cout << " Semester is INVALID." << endl;

    return false;
}

bool saveCourses(string codeList[], string nameList[], int crtHrsList[], int semList[])
{
  ofstream CoursesDataFile;
  CoursesDataFile.open("E:\\documents\\Tayyab Asghar\\I TO C (Lab)\\Project 14\\Courses.txt");

  if (CoursesDataFile.fail())
   {
    cout << " Courses Data File is not present." << endl;

    return false;
   }

  for (int i = 0; i < TotalCourses; i++)
   {
    CoursesDataFile << codeList[i] << ",";
    CoursesDataFile << nameList[i] << ",";
    CoursesDataFile << crtHrsList[i] << ",";
    CoursesDataFile << semList[i] << endl;
   }
  CoursesDataFile.close();

    return true;
}

bool loadCourses(string codeList[], string nameList[], int crtHrsList[], int semList[])
{
  ifstream CoursesDataFile;
  CoursesDataFile.open("E:\\documents\\Tayyab Asghar\\I TO C (Lab)\\Project 14\\Courses.txt");

  if (CoursesDataFile.fail())
   {
    cout << " Courses Data File is not present." << endl;

    return false;
   }


   while ( !(CoursesDataFile.eof()) ) // To avoid taking any empty line.
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
  UserDataFile.open("E:\\documents\\Tayyab Asghar\\I TO C (Lab)\\Project 14\\Users.txt");

  if (UserDataFile.fail())
   {
    cout << " Sorry, we are unable to run the program, as user data does not exist." << endl;

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
  if (regNo.size() == 11)
   {
    if (regNo[0] == '2')
     {
      if(regNo[1] == '0')
       {
        if (regNo[2] == '1')
         {
          if ( isdigit (regNo[3]) )
           {
            if (regNo[4] == '-')
             {
              if (regNo[5] == 'C')
               {
                if ( (regNo[6] >= 'A') && (regNo[6] <= 'Z') )
                 {
                  if (regNo[7] == '-')
                   {
                    if ( (isdigit (regNo[8])) && (isdigit (regNo[9])) && (isdigit (regNo[10])) )
                     {
                      if ( !((regNo[8] == '0') && (regNo[9] == '0') && (regNo[10] == '0')) )
                       {
                          return true;
                       }
                     }
                   }
                 }
               }
             }
           }
         }
       }
     }
   }
  cout << " INVALID Registration Number." << endl;

    return false;
}


bool isValidStudentName(string studentName)
{
 studentName = triming(studentName);     // Storing name in same string after removing unnecessary spaces.

 if (studentName.empty())
  {
   cout << " Student Name Can't be Empty." << endl;

     return false;
  }

 for (int i=0; i < studentName.size(); i++)
  {
    if ( !( isalpha (studentName[i]) || (studentName[i] == ' ') ) )    // Student Name is consist of 3 different data types.
     {
      cout << "  Student Name is INVALID." << endl;

      return false;
     }
   }

   return true;   // If string made out of loop.
}


bool saveStudents(string stdNamesList[], string stdRegNoList[], string stdCourseList[][20])
{
  ofstream StudentDataFile;
  StudentDataFile.open("E:\\documents\\Tayyab Asghar\\I TO C (Lab)\\Project 14\\Students.txt");

  if (StudentDataFile.fail())
   {
    cout << " Sorry, we are unable to run the program, as Student Registered Courses data does not exist." << endl;

    return false;
   }

  for (int i=0; i < TotalStudents; i++)
   {
    StudentDataFile << stdRegNoList[i] << "," << stdNamesList[i] << endl;

    for (int j=0; stdCourseList[i][j] != "\0"; j++)
     {
      StudentDataFile <<  stdCourseList[i][j];

      if (stdCourseList[i][j+1] != "\0")
       {
        StudentDataFile <<  ",";
       }
     }
    StudentDataFile << endl;
   }

  StudentDataFile.close();
}


bool loadStudents( string stdNamesList[], string stdRegNoList[],string stdCourseList[][20])
{
  string regCourses;

  ifstream StudentDataFile;
  StudentDataFile.open("E:\\documents\\Tayyab Asghar\\I TO C (Lab)\\Project 14\\Students.txt");

  if (StudentDataFile.fail())
   {
    cout << " Sorry, we are unable to run the program, as Student Registered Courses data does not exist." << endl;

    return false;
   }

   while ( !(StudentDataFile.eof()) ) // To avoid taking any empty line.
    {
      getline (StudentDataFile, stdRegNoList[TotalStudents], ',');
      getline (StudentDataFile, stdNamesList[TotalStudents], '\n');
      getline (StudentDataFile, regCourses, '\n');

      if( !(stdRegNoList[TotalStudents].empty()) )
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
      nameList[TotalCourses] = triming(courseName); // To remove the Extra spaces from start and end only.

      TotalCourses++; // Increasing the Numbers of Total Courses Stored in Array.
}

void EditCourse(string codeList[], string nameList[], int crtHrsList[], int semList[], string courseCode, string courseName, int crdHrs, int semester)
{
    int Position = whereCodeIsPresent(codeList, courseCode);
     // Editing Desired Data.
    codeList[Position] = courseCode;
    crtHrsList[Position] = crdHrs;
    semList[Position] = semester;
    nameList[Position] = triming(courseName); // To remove the Extra spaces from start and end only.
}

void DeleteCourse(string codeList[], string nameList[], int crtHrsList[], int semList[], string courseCode)
{
  int Position = whereCodeIsPresent(codeList, courseCode);

  for (int i = Position; i < TotalCourses; i++)
   {
      // Deleting Desired Data.
      codeList[i] = codeList[i + 1];
      crtHrsList[i] = crtHrsList[i + 1];
      semList[i] = semList[i + 1];
      nameList[i] = nameList[i + 1];
   }
  TotalCourses--; // Decreasing the Numbers of Total Courses Stored in Array.
}

void ViewCourses(string codeList[], string nameList[], int crtHrsList[], int semList[])
{
  cout << setw(19) << "Course Code" << setw(9) << "Name" << setw(63) << "Credit Hours" << setw(15) << "Semester" << endl;

  for (int i = 0; i < TotalCourses; i++)
   {
     // Viewing All Stored Data.
    cout << setw(13) << codeList[i];
    cout << "\t        " << nameList[i];
    cout << setw(57 - nameList[i].size()) << crtHrsList[i];
    cout << "\t\t   " << semList[i] << endl;
    }
}

void ViewSemesterCourses(string codeList[], string nameList[], int crtHrsList[], int semList[], int semester)
{
     bool flag = true;

      cout << setw(19) << "Course Code" << setw(9) << "Name" << setw(63) << "Credit Hours" << endl;

      for (int i = 0; i < TotalCourses; i++)
      {
        if (semList[i] == semester)
        {
          flag = false;

          // Printing the Desired Semester Data.
          cout << setw(13) << codeList[i];
          cout << "\t        " << nameList[i];
          cout << setw(57 - nameList[i].size()) << crtHrsList[i];
          cout << endl;
        }
      }
      if (flag) // If there is no Course in Semester.
      {
        cout << "\n There are no Courses in semester " << semester << "." << endl;
      }
}


void AddStudent(string stdNamesList[], string stdRegNoList[], string studentName, string regNo)
{
      stdNamesList[TotalStudents] = triming (studentName);
      stdRegNoList[TotalStudents] = regNo;

      TotalStudents++;
}


void UpdateStudent(string stdNamesList[], string stdRegNoList[], string studentName, string regNo)
{
   int Position = whereRegNoIsPresent (stdRegNoList, regNo);
                            // Editing Desired Data.
    stdNamesList[Position] = triming (studentName);
    stdRegNoList[Position] = regNo;
}


void DeleteStudent(string stdNamesList[], string stdRegNoList[], string stdCourseList[][20], string regNo)
{
   int Position = whereRegNoIsPresent (stdRegNoList, regNo);

   for (int i=Position; i < TotalStudents; i++ )                                       // Deleting Whole row of 2D Array.
    {
                  // Deleting Desired Data.
      stdNamesList[i] = stdNamesList[i + 1];
      stdRegNoList[i] = stdRegNoList[i + 1];

      for (int j=0; j < 20; j++)
       {
        stdCourseList[i][j] = stdCourseList[i+1][j];
       }
     }

  TotalStudents--;       // Decreasing the Numbers of Total Students Stored in Array.
}


void ViewStudents(string stdNamesList[], string stdRegNoList[], string stdCourseList[][20])
{
   cout << setw(27) << "Registration Number" << setw(17) << "Student Name" << setw(45) << "Registered Courses" << endl;

    for (int i=0; i < TotalStudents; i++ )
     {
      cout << setw (19) << stdRegNoList[i];
      cout << "\t\t" << stdNamesList[i];
      cout << setw (44 - stdNamesList[i].size());     // To set Format,

      for (int j=0; stdCourseList[i][j] != "\0"; j++)
       {
        cout << stdCourseList[i][j];

        if ( stdCourseList[i][j+1] != "\0")
        {
         cout << ", ";
        }
       }
      cout << endl;
     }
}


void RegisterCourse (string stdRegNoList[], string stdCourseList[][20], string codeList[], string regNo, string courseCode)
{
  if ( isCourseAlreadyPresent (codeList,courseCode) )
   {
    int Position = whereRegNoIsPresent(stdRegNoList, regNo);      // To find Correct Row.
    int i=0;

    while ( stdCourseList[Position][i] != "\0")
     {
      i++;                                               // To find Correct Column.
     }

    stdCourseList [Position][i] = courseCode;

    cout << " Course has been Registered for Student." << endl;
   }

  else
   {
    cout << " Course Code does not Exist.\n Student can't be Registered." << endl;
   }
}


void UnRegisterCourse(string stdRegNoList[], string stdCourseList[][20], string codeList[], string regNo, string courseCode)
{
  if ( isCourseAlreadyPresent (codeList,courseCode) )
   {
    int Position = whereRegNoIsPresent(stdRegNoList, regNo);            // To find Correct Row.
    int i = 0;

    while (stdCourseList[Position][i] != courseCode)
     {
      i++;                                               // To find Correct Column.
     }

    while (stdCourseList[Position][i] != "\0")
     {
      stdCourseList[Position][i] = stdCourseList[Position][i+1];
      i++;
     }

    cout << " Course has been Un-Registered for Student." << endl;
   }

  else
   {
    cout << " Course Code does not Exist.\n Student can't be Un-Registered." << endl;
   }
}

                             /*************************************************
                              Function I made for my Simplicity...............
                             *************************************************/

      // To Check that are all data that is taken from user is Valid by sending it into Different Function.

bool isInputDataValid(string courseCode, int crdHrs, int semester, string courseName)
{
  if (isValidCourseCode(courseCode))
   {
    if (isValidCreditHours(crdHrs))
     {
      if (isValidSemester(semester))
       {
        if (isValidCourseName(courseName))
         {
          return true;
         }
       }
     }
   }

  return false;
}

                  // To Check Course id Present.
bool isCourseAlreadyPresent(string codeList[], string courseCode)
{
  for (int i = 0; i < TotalCourses; i++)
   {
    if (codeList[i] == courseCode) // If course Code Found.
     {
      return true;
     }
   }

  return false;
}

bool isUserDataValid(string usersList[], string passwordsList[], string username, string password)
{
 for (int i = 0; usersList[i] != "\0"; i++)
  {
   if ( (usersList[i] == username) && (passwordsList[i] == password) )
    {
      return true;
    }
  }
 cout << "\n Dear User, Username/password is incorrect.\n Enter the username/password again to get access to the system." << endl;

  return false;
}

bool loadAllData(string codeList[], string nameList[], int crtHrsList[], int semList[], string usersList[], string passwordsList[], string stdNamesList[], string stdRegNoList[], string stdCourseList[][20])
{
  if ( loadCourses(codeList, nameList, crtHrsList, semList) )
   {
    if (loadUsers (usersList, passwordsList))
     {
      if (loadStudents (stdNamesList, stdRegNoList, stdCourseList))
       {
          return true;
       }
     }

   }

  return false;
}

bool isRegNoAlreadyPresent(string stdRegNoList[], string regNo)
{
  for (int i = 0; i < TotalStudents; i++)
   {
    if (stdRegNoList[i] == regNo) // If Registration Number Found.
     {
         return true;
     }
   }

   return false;
}

bool isStudentAlreadyRegistered (string stdRegNoList[], string stdCourseList[][20], string regNo, string courseCode)
{
  int Position = whereRegNoIsPresent(stdRegNoList, regNo);

  for (int i=0; stdCourseList[Position][i] != "\0"; i++)
   {
    if (stdCourseList[Position][i] == courseCode)
     {
       return true;
     }
   }

    return false;
}

bool nonZeroTotalCourses()
{
  if ( TotalCourses > 0)
   {
      return true;
   }
  cout << " There is No Course present to complete the Process.\n Add them by selecting \"Add Course\" option." << endl;

   return false;
}

bool nonZeroTotalStudents()
{
   if (TotalStudents > 0)
    {
      return true;
    }
   cout << " There is No Student present to complete the Process.\n Add them by selecting \"Add NewStudent\" option." << endl;

    return false;
}

bool isValidInputDetails(string stdNamesList[], string stdRegNoList[], string password, string regNo)
{
  int position = whereRegNoIsPresent(stdRegNoList, regNo);
  int lenght = stdNamesList[position].size();
  string stdName = stdNamesList[position];

  if ( isValidRegistrationNumber (regNo) )
  {
   if ( isRegNoAlreadyPresent (stdRegNoList, regNo) )
    {
     if (password.size() == 3)
      {
       if (stdName[lenght-3] == password[0])
        {
         if (stdName[lenght-2] == password[1])
          {
           if (stdName[lenght-1] == password[2])
            {
              return true;
            }
          }
        }
      }
    }

   else
    {
     cout << " You are not added to this UNIVERSITY." << endl;

        return false;
    }
  }
  cout << " INVALID Password...." << endl;

     return false;
}

void handleInputFailure()
{
  cin.clear(); // To safe your code from Input Failure.
  cin.ignore(500, '\n');
  cout << endl << endl;
}

void toUnRegisterAllStudent(string stdCourseList[][20], string courseCode)
{
  for (int i=0; stdCourseList[i][0] != "\0"; i++)
   {
    for (int j=whereCourseIsPresentInStdList (stdCourseList, courseCode, i); stdCourseList[i][j] != "\0"; j++)
     {
      stdCourseList[i][j] = stdCourseList[i][j+1];
     }
   }
}

void putInstdCourseList(string stdCourseList[][20], string regCourses)
{
 int i=0, j=0, m = 5;

  while (i != (regCourses.size() / 5))
   {
    while ( (j%m != 0) || (j == 0) )
     {
      stdCourseList[TotalStudents][i] += regCourses [j];
      j++;
     }
    j++;
    i++;
    m += 6;
   }
}

void ViewLogedStudent(string stdNamesList[], string stdRegNoList[], string stdCourseList[][20], string regNo)
{
  int position = whereRegNoIsPresent(stdRegNoList, regNo);

    cout << setw(27) << "Registration Number" << setw(17) << "Student Name" << setw(45) << "Registered Courses" << endl;

      cout << setw (19) << stdRegNoList[position];
      cout << "\t\t" << stdNamesList[position];
      cout << setw (44 - stdNamesList[position].size());     // To set Format,

      for (int j=0; stdCourseList[position][j] != "\0"; j++)
       {
        cout << stdCourseList[position][j];

        if ( stdCourseList[position][j+1] != "\0")
        {
         cout << ", ";
        }
       }
      cout << endl << endl;
}

int whereCodeIsPresent(string codeList[], string courseCode)
{
  for (int i = 0; i < TotalCourses; i++)
   {
    if (codeList[i] == courseCode) // To Find where Course Code is Present.
     {
      return i; // To return where Course Code is Present.
     }
   }
}

int whereRegNoIsPresent(string stdRegNoList[], string regNo)
{
  for (int i=0; i < TotalStudents; i++)
   {
     if (stdRegNoList[i] == regNo)
      {
       return i;
      }
   }
}

int whereCourseIsPresentInStdList(string stdCourseList[][20], string courseCode, int i)
{
  int j=0;

  while (stdCourseList[i][j] != courseCode)
   {
    j++;
   }

    return j;
}
string triming(string Name) // To remove the Extra spaces from start only.
{
  int lenght = Name.find_first_not_of(" \t");

  Name.erase(0, lenght);

  lenght = Name.find_last_not_of(" \t");

  if (string::npos != lenght)
   {
    Name.erase(lenght + 1);
   }

    return Name;
}
