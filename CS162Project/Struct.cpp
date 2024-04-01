#include "struct.h"

void createSeveralClasses(Class *&HeadClass){
    string temp;
    cout<<"Enter name of classes separated by space. Finish by entering Q"<<endl;
    while(true){
        cin>>temp;
        if(temp=="Q") break;  //exit loop when user enters 'Q'.
        Class *newOne = new Class;
        newOne->className = temp;
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
        fin >> cur->schoolYear;
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
        delete temp;
        clas = clas->next;
    }
    clas = nullptr;
}
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



void addStudentToClass(Class* clas, Student* stu){
    string className;
    cout << "Enter class name: ";
    cin >> className;
    bool check = false;
    Class*cur = clas;
    while(cur){
        if(cur->className == className){
            check = true;
            break;
        }
        cur = cur->next;
    }
    if(check)
        cur->addStudents(stu);
    else
        cout << "The class doesn't exist " << endl;
}

void Class::addStudents(Student* stu)
{
    cout << "Only need the Id of students for adding"  << endl;
    cout << "Enter number of students: ";
    int n;
    cin >> n;
    if(n <= 0){
        cout << "Pls input the positive integer number" << endl;
        cout << "Enter: ";
    }
    while(n--){
        Student* cur = stu;
        string temp;
        cout << "Student Id: ";
        cin >> temp;
        bool check = false;
        while(cur){
            if(cur->studentId == temp){
                if(cur->schoolYear == 1){
                    cur->className = className;
                    check = true;
                    break;
                }else
                    break;
            }
            cur = cur->next;
        }
        if(check){
            StudentEnrolled *temp1 = new StudentEnrolled;
            temp1->studentId = temp;
            temp1->next = studentEnroll;
            studentEnroll = temp1;
        }else{
            n++;
            cout << "Doesn't find any student having this Id" << endl;
        }
    }
}
