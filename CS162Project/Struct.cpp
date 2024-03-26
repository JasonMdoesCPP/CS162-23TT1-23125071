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
    newYear -> yearEnd = data + 1;
    if (cur) cur -> next = newYear; else schoolYear = newYear;
}

void createSeveralClasses(Class *&HeadClass){
    string temp;
    cout<<"Enter name of classes separated by space. Finish by entering Q"<<endl;
    while(true){
        cin>>temp;
        if(temp=="Q") break;  //exit loop when user enters 'Q'.
        Class *newOne = new Class;
        newOne->classname = temp;
        newOne->next=nullptr;
        if(HeadClass==nullptr){
            HeadClass=newOne;
        }else{
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

void Course::inputStudent2CourseFromFile(User* &Head){
   string name1;
   name1 = Course_name+".csv";
   ifstream fin;
   fin.open(name1);
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
       StudentEnrolled *stu = new StudentEnrolled;
       stu->studentId = temp;
       UpdateCourse4StuInUser(temp,Head,Course_name);
       getline(fin, temp, ',');
       stu->socialId = temp;
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
       //Insert before Head
       stu->next = studentEnrolled;
       studentEnrolled=stu;

   }
   fin.close();
}
void UpdateCourse4StuInUser(string ID,User* &Head_User,string Course_name)
{
    Student *cur=Head_User->students;
    while(cur!=nullptr)
    {
        string temp=cur->studentId;
        if(temp.compare(ID)==0)
        {
            CourseOfStudent *newCourse=new CourseOfStudent;
            newCourse->CourseOfStu_name=Course_name;
            return;
        }
    }
}

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
    cin >> temp -> Course_ID;
    cout << "Please enter course name: ";
    cin >> temp->Course_name;
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
    if (course == nullptr) {
        course = temp;
        temp -> next = nullptr;
    }
    else {
        temp -> next = course;
        course = temp;
    }
    cout << "Course created!" << endl;
}
void Semester::viewTheListOfCourses()
{
    Course* cur = course;
    while (cur != NULL)
    {
        cout << "Course ID: " << cur->Course_name << endl;
        cout << "Course Name: " << cur->Course_name << endl;
        cout << "Teacher Name: " << cur->teacherName << endl;
        cout << "Number of Credits " << cur->numberOfCredits << endl;
        cur = cur->next;
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

//This function use for updating the course of each student
//While input student into course
Student* FindStudentinClass(Class *headClass,string ID)
{
    Class *currentClass=headClass;
    Student *currentStudent;
    while(currentClass!=nullptr)
    {
        currentStudent=currentClass->student;
        while(currentStudent!=nullptr)
        {
            if(currentStudent->studentId==ID)
            return currentStudent;
        }
    }
    return nullptr;
}

void Course::updateStudentResult(User user){
    StudentEnrolled* cur1 = studentEnrolled;
    Student* cur2;
    while(cur1){
        cur2 = user.students;
        while(cur2){
            if(cur1->studentId == cur2->studentId){
                CourseOfStudent* cur3 = cur2->courses;
                while(cur3){
                    if(cur3->CourseOfStu_name == Course_name){
                        cur3->score.finalMark = cur1->score.finalMark;
                        cur3->score.midtermMark =cur1->score.midtermMark;
                        cur3->score.otherMark =cur1->score.otherMark;
                        cur3->score.totalMark = cur1->score.totalMark;
                        break;
                    }
                    cur3 = cur3->next;
                }
                break;
            }
            cur2 = cur2->next;
        }
        cur1 = cur1->next;
    }
}

void User::deleteUser(){
    while(students){
        Student *temp=students;
        students =  students->next;
        delete temp;
    }
    while(staffMembers){
        StaffMember *temp = staffMembers;
        staffMembers = staffMembers->next;
        delete temp;
    }
    students = nullptr;
    staffMembers = nullptr;
}

void deleteClass(Class *&clas){
    while(clas){
        Class* temp = clas;
        clas = clas->next; 
    }
    clas = nullptr;
}
