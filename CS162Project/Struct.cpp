#include <string>
#include <fstream>

using namespace std;

#include "Struct.h"

void StaffMember::createSchoolYear(){
    SchoolYear* cur = schoolYear;
    while (cur && cur -> next) cur = cur -> next;
    cout << "Please input school year: ";
    int data;
    cin >> data;
    SchoolYear* newYear = new SchoolYear;
    newYear -> next = nullptr;
    newYear -> yearStart = data;
    if (cur) cur -> next = newYear; else schoolYear = newYear;
}

void createSeveralClasses(Class *&HeadClass){
    string temp;
    cout<<"Enter name of classes separated by space. Finish by entering Q"<<endl;
    while(true)
    {
        cin>>temp;
        if(temp=="Q") break;  //exit loop when user enters 'Q'.
    Class *newOne = new Class;
    newOne->classname = temp;
    newOne->next=nullptr;
    if(HeadClass==nullptr){
    HeadClass=newOne;
    }
    else
    {
    newOne->next=HeadClass;
    HeadClass=newOne;
    }
    }
}


void User::login(){
    cout << "1: Student" << endl;
    cout << "2: Staff member" << endl;
    cout << "Enter: " ;
    int ca;
    cin >> ca;
    while(ca != 1 && ca != 2){
        cout << "Wrong number !"  << endl;
        cout << "1: Student" << endl;
        cout << "2: Staff member" << endl;
        cout << "Enter: " ;
        cin >> ca;
    }
    string x,y;
    cout << "Username: ";
    cin.ignore();
    getline(cin, x);
    cout << "Password: ";
    getline(cin, y);
    if(ca == 1){
        Student* cur = students;
        while(cur){
            if(x == cur->userName)
                if(y == cur->passWord){
                    user1 = cur;
                    return;
                }
            cur = cur->next;
        }
    }else{
        StaffMember* cur = staffMembers;
        while(cur){
            if(x == cur->userName)
                if(y == cur->passWord){
                    user2 = cur;
                    return;
                }
            cur = cur->next;
        }
    }
    if(!user1&&!user2){
        cout << " Wrong Username or Password" << endl;
        login();
    }
}
void inputFromFile(Class *clas, string name){
    Class*cur = clas;
    while(cur){
        if(clas->classname == name){
            clas->inputFromFile();
            return;
        }
        cur = cur->next;
    }
    cout << "Don't have any class having this name";
}
void Class::inputFromFile(){
    string name;
    name = classname+".csv";
    ifstream fin;
    fin.open(name);
    if(!fin.is_open()){
        cout << "Error! ";
        return;
    }
    string line;
    getline(fin, line);
    string temp;
    while(getline(fin, temp, ',')){
        if(temp == "endlist"){
            break;
        }
        Student *stu = new Student;
        stu->No = stoi(temp);
        getline(fin, temp, ',');
        stu->studentId = temp;
        getline(fin, temp, ',');
        stu->firstName = temp;
        getline(fin, temp, ',');
        stu->lastName = temp;
        getline(fin, temp, ',');
        stu->gender = temp;
        getline(fin, temp, ',');
        stu->dateOfBirth.day = stoi(temp);
        getline(fin, temp, ',');
        stu->dateOfBirth.month = stoi(temp);
        getline(fin, temp, ',');
        stu->dateOfBirth.year = stoi(temp);
        getline(fin, temp);
        stu->socialId = temp;
        stu->next = student;
        student = stu;
    }
    fin.close();
}


void Class::addStudents()
{
    cout << "Enter number of students: ";
    int n;
    cin >> n;
    if(n--){
        Student *stu = new Student;
        cout << "No: ";
        cin >> stu->No;
        cout << "Student Id: ";
        cin >> stu->studentId;
        cout << "First name: ";
        cin >> stu->firstName;
        cout << "Last name: ";
        cin >> stu->lastName;
        cout << "Gender: (male/female)";
        cin >> stu->gender;
        cout << "Day of birth: ";
        cin >> stu->dateOfBirth.day;
        cin >> stu -> dateOfBirth.month;
        cin >> stu->dateOfBirth.year;
        cout << "Social id: ";
        cin >> stu->socialId;
        stu->next = student;
        student = stu;
    }
}
void User::addInformationStudent(){
    students = new Student;


}

void SchoolYear::createSemester(){
    semester = new Semester[3];
    cout << "Semester created!" << endl;
    return;
}

void Semester::addCourse(){
    Course* temp = new Course;
    cout << "Please enter course ID:";
    cin >> temp -> id;
    cout << "Please enter course name: ";
    cin >> course->name;
    cout << "Please enter class name: ";
    cout << "Please enter teacher's name:";
    cout << "Please enter the number of credits: ";
    cout << "Please enter the maximal number of students in the course: ";
    cout << "Please enter the day the course will be performed in: ";
    cout << "Please enter the session the course will be performed in: ";
}
void Semester::viewTheListOfCourses()
{
    while (Semester->course != NULL)
    {
        cout << "Course ID: " << Semester->course.id << endl;
        cout << "Course Name: " << Semester->course.name << endl;
        cout << "Teacher Name: " << Semester->course.teacherName << endl;
        cout << "Number of Credits " << Semester->course.numberOfCredits << endl;
        Semester->course = Semester->course->next;
    }
}

