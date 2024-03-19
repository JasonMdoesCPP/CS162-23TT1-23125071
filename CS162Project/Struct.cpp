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

//void Course::inputStudent2CourseFromFile(){
//    string name1;
//    name1 = name+".csv";
//    ifstream fin;
//    fin.open(name1);
//    if(!fin.is_open()){
//        cout << "Error! ";
//        return;
//    }
//    string line;
//    getline(fin, line);
//    string temp;
//    while(getline(fin, temp, ',')){
//        if(temp == "endlist"){
//            break;
//        }
//        StudentEnrolled *stu = new StudentEnrolled;
//        stu->studentId = stoi(temp);
//        getline(fin, temp, ',');
//        stu->socialId = stoi(temp);
//        getline(fin, temp, ',');
//        stu->firstName = temp;
//        getline(fin, temp, ',');
//        stu->lastName = temp;
//        getline(fin, temp, ',');
//        stu->gender = temp;
//        getline(fin, temp, ',');
//        stu->dateOfBirth.day = stoi(temp);
//        getline(fin, temp, ',');
//        stu->dateOfBirth.month = stoi(temp);
//        getline(fin, temp, ',');
//        stu->dateOfBirth.year = stoi(temp);
//        getline(fin, temp);
//        stu=stu->next;
//
//    }
//    fin.close();
//}


void SchoolYear::createSemester(){
    semester = new Semester[3];
    cout << "Please choose the current semester (1, 2, 3): ";
    int cur;
    cin >> cur;
    cout << "Please enter start date: "; cin >> semester[cur-1].startDay;
    cout << "Please enter the end date: "; cin >> semester[cur-1].endDay;
    cout << "Semester created!" << endl;
    return;
}

void Semester::addCourse(){
    Course* temp = new Course;
    cout << "Please enter course ID:";
    cin >> temp -> id;
    cout << "Please enter course name: ";
    cin >> temp->name;
    cout << "Please enter class name: ";
    cin >> temp -> classname;
    cout << "Please enter teacher's name:";
    cin >> temp -> teacherName;
    cout << "Please enter the number of credits: ";
    cin >> temp -> numberOfCredits;
    cout << "Please enter the maximal number of students in the course: ";
    cin >> temp -> maxSize;
    cout << "Please enter the day the course will be performed in: ";
    cin.get();
    cin.get(temp -> dow, 1, '\0');
    cin.get();
    cout << "Please enter the session the course will be performed in: ";
    cin >> temp -> session;
    cout << "Course created!" << endl;
}
void Semester::viewTheListOfCourses()
{
    while (course != NULL)
    {
        cout << "Course ID: " << course->id << endl;
        cout << "Course Name: " << course->name << endl;
        cout << "Teacher Name: " << course->teacherName << endl;
        cout << "Number of Credits " << course->numberOfCredits << endl;
        course = course->next;
    }
}
void User::addInformationStudent(){
    ifstream fin;
    fin.open("student.txt");
    students = new Student;
    Student* cur = students;
    Student* before = students;
    string temp;
    while(fin>>temp){
        if(temp ==  "end"){
            break;
        }
        cur->passWord = temp;
        fin >> cur->userName;
        fin >> cur->studentId;
        fin >> cur->socialId;
        fin >> cur->firstName;
        fin >> cur->lastName;
        fin >> cur->gender;
        cur->next = new Student;
        before = cur;
        cur = cur->next;
    }
    before->next = nullptr;
    delete cur;
}
void User::addInformationStaffMembers(){
    ifstream fin;
    fin.open("staffMember.txt");
    staffMembers = new StaffMember;
    StaffMember* cur = staffMembers;
    StaffMember* before = staffMembers;
    string temp;
    while(fin>>temp){
        if(temp ==  "end"){
            break;
        }
        cur->passWord = temp;
        fin >> cur->userName;
        fin >> cur->firstName;
        fin >> cur->lastName;
        cur->next = new StaffMember;
        before = cur;
        cur = cur->next;
    }
    before->next = nullptr;
    delete cur;
}
