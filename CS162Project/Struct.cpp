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
        clas = clas->next;
        StudentEnrolled* cur = temp->studentEnroll;
        while(cur){
            StudentEnrolled* temp1 = cur;
            cur = cur->next;
            delete temp1;
        }
        temp->studentEnroll = nullptr;
        delete temp;
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

void StaffMember::addSemester(int yearStart,Semester *&cur_semester)
{
    SchoolYear *cur_year = schoolYear;
                while (cur_year)
                {
                    if (cur_year->yearStart == yearStart)
                    {
                        cur_year->semester = new Semester;
                        cur_semester = cur_year->semester;
                        return;
                    }
                    cur_year = cur_year->next;
                }
                cout << "No SchoolYear found!";
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
void addStudentToClassFromCsvFile(Class*clas, Student*stu){
    string className;
    cout << "Enter class name: ";
    cin >> className;

    bool check = false;
    ifstream fin;
    Class*cur = clas;
    while(cur){
        if(cur->className == className){
            check = true;
            break;
        }
        cur = cur->next;
    }
    className += ".csv";
    fin.open(className);
    if(!fin.is_open()){
        cout << "Doesn't have this class' csv file";
        return;
    }
    if(check){
        while(!fin.eof()){
            string temp;
            getline(fin, temp,',');
            if(temp == "eof"){
                break;
            }
            Student* cur1 = stu;
            while(cur1){
                if(cur1->studentId == temp){
                    StudentEnrolled* temp2 = new StudentEnrolled;
                    temp2->studentId = temp;
                    temp2->next = clas->studentEnroll;
                    clas->studentEnroll = temp2;
                    cur1->className = cur->className;
                    break;
                }
                cur1 = cur1->next;
            }
        }
    }
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
void Semester::addCourse() {
    Course* temp = new Course;
    cout << "Please enter course ID: ";
    cin >> temp->Course_ID;
    cout << "Please enter course name: ";
    cin.ignore();
    getline(cin, temp->Course_name);
    cout << "Please enter class name: ";
    cin >> temp->classname;
    cout << "Please enter teacher's name: ";
    cin.ignore();
    getline(cin, temp->teacherName);
    cout << "Please enter the number of credits: ";
    cin >> temp->numberOfCredits;
    cout << "Please enter the maximal number of students in the course: ";
    cin >> temp->maxSize;
    cout << "Please enter the day the course will be performed in: (M: Monday, T: Tuesday, ..., S: Saturday)";
    cin.ignore();
    cin.get(temp->dow, 2, '\n'); // Increase size to accommodate the null terminator
    cout << "Please enter the session the course will be performed in: ";
    cin >> temp->session;
    if (course == nullptr) {
        course = temp;
        temp->next = nullptr;
    }
    else {
        temp->next = course;
        course = temp;
    }
    cout << "Course created!" << endl;
}
void UpdateCoursetoUser(string StudentID,string CourseName, string newCourseName, User &Head_User)
{
    Student *cur_Student=Head_User.students;
    while(cur_Student)
    {
        if(cur_Student->studentId==StudentID)
        {

            Score *cur_Score=cur_Student->score;
            bool flag=false;
                while(cur_Score)
                {
                    if(cur_Score->courseName==CourseName)
                    {
                        cur_Score->courseName=newCourseName;
                        flag=true;
                    }
                    cur_Score=cur_Score->next;
                }
                if (cur_Score == nullptr)
                {
                    cur_Score = new Score;
                    cur_Score->courseName = newCourseName;
                    flag = true;
                }
                if(flag==false)
                {
                    cur_Score=cur_Student->score;
                    while(cur_Score->next!=nullptr) cur_Score=cur_Score->next;
                    cur_Score->next=new Score;
                    cur_Score=cur_Score->next;
                    cur_Score->courseName=newCourseName;
                    cur_Score->next=nullptr;
                    return;
                }
        }
        cur_Student=cur_Student->next;
    }
}
void Course::inputStudent2CourseFromFile(User &Head_User)
{
    string name1;
    name1=Course_name+".csv";
    ifstream fin;
    fin.open(name1);
    if (!fin.is_open()) {
        cout << "Error! ";
        return;
    }
    string line;
    getline(fin, line);
    string temp;
    while (getline(fin, temp, ',')) {
        if (temp == "endlist") {
            break;
        }
        StudentEnrolled* stu = new StudentEnrolled;
        stu->studentId = temp;
//Get class of the student
        getline(fin, temp, ',');
        string classname;
	classname = temp;
       	UpdateCoursetoUser(stu->studentId,Course_ID,nullptr,Head_User);
        getline(fin, temp);
        //Insert before Head
        stu->next = studentEnrolled;
        studentEnrolled = stu;
    }
    fin.close();
}

