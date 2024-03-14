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

void Class::createSeveralClasses(Class *&HeadClass){
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
void Class::addStudents()
{
    Student *stu = new Student;
    cin >> stu->No;
    cin >> stu->studentId;
    cin >> stu->firstName;
    cin >> stu->lastName;
    cin >> stu->gender;
    cin >> stu->dateOfBirth.day;
    cin >> stu -> dateOfBirth.month;
    cin >> stu->dateOfBirth.year;
    cin >> stu->socialId;
    stu->next = this->student;
    this->student = stu;
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
    return;
}
