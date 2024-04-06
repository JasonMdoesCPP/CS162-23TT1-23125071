#include "struct.h"

bool publishedScore = false;
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
        if(temp ==  "eof"){
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
        if(temp ==  "eof"){
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
    cout << "No SchoolYear found!" << endl;
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
        string line;
        getline(fin, line); // Read and discard header line
        while(!fin.eof()){
            bool flag = false;
            string temp;
            getline(fin, temp,',');
            fin.ignore();
            if(temp == "eof"){
                break;
            }
            StudentEnrolled* curStudentEnrolled = cur->studentEnroll;
            while(curStudentEnrolled){
                if(temp == curStudentEnrolled->studentId){
                    cout << "The student with ID " << temp << " has been added in this class!" << endl;
                    flag = true;
                }
                curStudentEnrolled=curStudentEnrolled->next;
            }
            if(!flag){
                Student* cur1 = stu;
                while(cur1){
                    if(cur1->studentId == temp){
                        StudentEnrolled* temp2 = new StudentEnrolled;
                        temp2->studentId = temp;
                        temp2->next = clas->studentEnroll;
                        cur->studentEnroll = temp2;
                        cur1->className = cur->className;
                        clas->studentEnroll = temp2;
                        flag = true;
                        break;
                    }
                    cur1 = cur1->next;
                }
                if (flag == false) cout << "Student with ID " << temp << " doesn't exist!"<<endl;
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
        StudentEnrolled* curStudentEnroll = studentEnroll;
        // check if in class ?
        bool check = false;
        while(curStudentEnroll){
            if(temp == curStudentEnroll->studentId){
                check = true;
                break;
            }
            curStudentEnroll=curStudentEnroll->next;
        }
        if(check){
            cout << "This student has been added in this class!" << endl;
        }
        if(!check){
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
                cout << "Doesn't find any student having this id" << endl;
            }
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
    cout << "Please enter the day the course will be performed in (M/T/W/Th/F/Sa/Su):";
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
//1 for adding, 2 for deleting
void UpdateCoursetoUser(string StudentID,string CourseID, string newCourseID, User &Head_User,int choice)
{
    Student *cur_Student=Head_User.students;
    switch (choice)
        {
    case 1:
        while (cur_Student)
        {
            if (cur_Student->studentId == StudentID)
            {

                Score* cur_Score = cur_Student->score;
                if (cur_Score == nullptr)
                {
                    cur_Student->score = new Score;
                    cur_Student->score->Course_ID = newCourseID; // Update to newCourseID instead of CourseID
                    cur_Student->score->next = nullptr;
                    return;
                }
                while (cur_Score)
                {
                    if (cur_Score->Course_ID == CourseID)
                    {
                        cur_Score->Course_ID = newCourseID;
                        return;
                    }
                    if (cur_Score->next == nullptr)
                    {
                        cur_Score->next = new Score;
                        cur_Score = cur_Score->next;
                        cur_Score->Course_ID = newCourseID; // Update to newCourseID instead of newCourseName
                        cur_Score->next = nullptr;
                        return;
                    }
                    cur_Score = cur_Score->next;
                }


            }
            cur_Student = cur_Student->next;
        }
        break;
    case 2:
        while (cur_Student)
        {
            if (cur_Student->studentId == StudentID)
            {

                Score* cur_Score = cur_Student->score;
                if (cur_Score == nullptr)
                {
                    return;
                }
                if (cur_Score->Course_ID == CourseID)
                {
                    delete cur_Score;
                    cur_Score = nullptr;
                    return;
                }
                while (cur_Score)
                {
                    if (cur_Score->next->Course_ID == CourseID)
                    {
                        Score *tempScore = cur_Score->next;
                        cur_Score->next = tempScore->next;
                        delete tempScore;
                        return;
                    }
                    if (cur_Score->next == nullptr)
                    {
                        return;
                    }
                    cur_Score = cur_Score->next;
                }


            }
            cur_Student = cur_Student->next;
        }
        }

}
void Course::inputStudent2CourseFromFile(User &Head_User)
{
string filename = Course_ID + ".csv";
    ifstream fin(filename);

    if (!fin.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    getline(fin, line); // Read and discard header line

    string studentId;
    while (getline(fin, studentId, ',')) {
        if (studentId == "endlist") {
            break;
        }

        // Check if the student is already enrolled
        StudentEnrolled *curEnrollment = studentEnrolled;
        bool alreadyEnrolled = false;
        while (curEnrollment != nullptr) {
            if (curEnrollment->studentId == studentId) {
                alreadyEnrolled = true;
                break;
            }
            curEnrollment = curEnrollment->next;
        }

        if (!alreadyEnrolled) {
            // Create a new StudentEnrolled node
            StudentEnrolled *newEnrollment = new StudentEnrolled;
            newEnrollment->studentId = studentId;
            newEnrollment->next = studentEnrolled;
            studentEnrolled = newEnrollment;

            // Update to User
            UpdateCoursetoUser(studentId, Course_ID, Course_ID, Head_User,1);
        }
        fin.ignore();
    }

    fin.close();
}
//03/04
Course* Semester::findCourseinSemester(string CourseID)
{
    Course *cur_Course = course;
    while (cur_Course != nullptr)
    {
        if (cur_Course->Course_ID == CourseID)
            return cur_Course;
        cur_Course = cur_Course->next;
    }
    return nullptr;
}
// Member function to update course information
void Course::UpdateCourseInfo(User &Head_User)
{
    cout << "Please enter updated information for the course:" << endl;
    cout << "Course ID: ";
    string newCourseID;
    cin >> newCourseID;
    cout << "Course Name: ";
    cin.ignore();
    getline(cin, Course_name);
    cout << "Class Name: ";
    cin >> classname;
    cout << "Teacher's Name: ";
    cin.ignore();
    getline(cin, teacherName);
    cout << "Number of Credits: ";
    cin >> numberOfCredits;
    cout << "Maximal Number of Students: ";
    cin >> maxSize;
    cout << "Day of Week (M/T/W/Th/F/Sa/Su): ";
    cin.ignore();
    cin.get(dow, 2, '\n');
    cout << "Session: ";
    cin >> session;

    // Update course ID in student scores if necessary
    if (newCourseID != Course_ID) {
        Course* tempCourse = this;
        while (tempCourse) {
            StudentEnrolled* tempStudent = tempCourse->studentEnrolled;
            while (tempStudent) {
                Student* curStudent = Head_User.students;
                while (curStudent) {
                    Score* curScore = curStudent->score;
                    while (curScore) {
                        if (curScore->Course_ID == Course_ID) {
                            curScore->Course_ID = newCourseID;
                        }
                        curScore = curScore->next;
                    }
                    curStudent = curStudent->next;
                }
                tempStudent = tempStudent->next;
            }
            tempCourse = tempCourse->next;
        }
    }

    // Update course ID
    Course_ID = newCourseID;

}

// Member function to add a student to the course
void Course::AddStudentToCourse(Student* student) {

    while (studentEnrolled)
    {
        if (studentEnrolled->studentId == student->studentId)
            cout << "Student's already in the course!";
        return;
    }
    StudentEnrolled* newEnrollment = new StudentEnrolled;
    newEnrollment->studentId = student->studentId;
    newEnrollment->next = studentEnrolled;
    studentEnrolled = newEnrollment;

    // Update student's score with this course
    Score* newScore = new Score;
    newScore->Course_ID = Course_ID;
    newScore->next = student->score;
    student->score = newScore;
}

// Member function to remove a student from the course
void Course::RemoveStudentFromCourse(const string& studentId) {
    StudentEnrolled* prev = nullptr;
    StudentEnrolled* current = studentEnrolled;

    // Find the student in the enrollment list
    while (current != nullptr) {
        if (current->studentId == studentId) {
            // If found, remove the enrollment
            if (prev == nullptr) {
                studentEnrolled = current->next;
            }
            else {
                prev->next = current->next;
            }
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }
}

// Member function to delete a course from a semester
void Semester::DeleteACourse(const string& courseId) {
    Course* prev = nullptr;
    Course* current = course;

    // Traverse the list to find the course
    while (current != nullptr) {
        if (current->Course_ID == courseId) {
            // If found, remove it from the list
            if (prev == nullptr) {
                course = current->next;
            }
            else {
                prev->next = current->next;
            }
            // Delete all associated memory
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }
}

void viewClasses(Class* HeadClass){
    if(!HeadClass){
        cout << "There are no class having created yet!" << endl;
        return;
    }
    cout << "The currently registered classes are: " << endl;
    Class* cur = HeadClass;
    while (cur) {
        cout << cur -> className << endl;
        cur = cur -> next;
    }
}

void viewStudentInClass(Class* HeadClass, Student* headStudent){
    Class* cur = HeadClass;
    if (!cur) {
        cout << "There are no registered class." << endl;


        return;
    }
    cout << "Please enter the class you want to view: ";
    string temp;
    cin >> temp;
    while (cur) {
        if (cur->className == temp) break;
        cur = cur -> next;
    }
    if (!cur) {
        cout << "There are no classes with this name" << endl;


        return;
    }
    cout << "The students in class " << temp << " have their full name/id to be: " << endl;
    StudentEnrolled* curStudent = cur->studentEnroll;
    while (curStudent) {
        Student* curUserStudent = headStudent;
        while(curUserStudent){
            if(curUserStudent->studentId == curStudent->studentId){
                cout << curUserStudent->firstName << " " << curUserStudent->lastName << endl;
                break;
            }
            curUserStudent = curUserStudent->next;
        }
        cout << curStudent->studentId << endl;
        curStudent = curStudent -> next;
    }


}

void Semester::viewCourse(){
    Course* cur = course;
    if (!cur) {
        cout << "There are no courses added yet." << endl;


    }
    cout << "The added courses in this semester have their courses' name to be: " << endl;
    while (cur) {
        cout << "- "<< cur->Course_name << endl;
        cur = cur -> next;
    }


}

void Course::viewStudent(Student* headStu){
    StudentEnrolled* cur = studentEnrolled;
    if (!cur){
        cout << "No students have been added to the course yet!" << endl;
        return;
    }
    cout << "The students in this course have their full name to be:" << endl;
    while (cur){
        Student* temp = headStu;
        while(temp){
            if(temp->studentId == cur->studentId){
                cout <<"- "<< temp->firstName << " " << temp->lastName;
                break;
            }
            temp = temp->next;
        }
        cur = cur->next;
    }
    cout << endl;

}
void publishScore(){
    publishedScore = true;
}

void Student::ViewScore(Course* HeadCourse){
    if(publishedScore){
        Score* cur = score;
        while(cur){
            Course * curCourse = HeadCourse;
            while(curCourse){
                if(curCourse->Course_ID == cur->Course_ID)
                    break;
                curCourse = curCourse->next;
            }
            cout << "Course: " << curCourse->Course_name << endl;
            cout << "Mid term: "<< cur->midtermMark << endl;
            cout << "Final: "<<cur->finalMark << endl;
            cout <<"Other: " <<cur->otherMark << endl;
            cout <<"Total: " << cur->totalMark << endl;
        }
    }else{
        cout << "Scores haven't published " << endl;
    }
}

void Class::viewScore(Student* stu, Course* headCourse){
    StudentEnrolled* curClasStu = studentEnroll;
    while(curClasStu){
        Student*curStu = stu;
        while(curStu){
            if(curStu->studentId == curClasStu->studentId){
                cout <<"Full name: "<<curStu->firstName << " " << curStu->lastName << endl;
                cout << " ID: "<< curStu->studentId << endl;
                curStu->ViewScore(headCourse);
                cout << "GPA: " << curStu->calGPA();
                break;
            }
            curStu = curStu->next;
        }
        curClasStu = curClasStu->next;
    }

}
void exportStudentInCourseToCsvFile(Student* stu)
{ string CourseId;
  cout << "Enter Course ID:";
  cin.ignore();
  getline(cin, CourseId);
  string filename = CourseId + ".csv";
  ofstream fout(filename);
  if (!fout.is_open())
  {
                cout << "Error opening file: " << filename << endl;
                return;
  }
  Student* curStudent = stu;
  while (curStudent!=nullptr)
  {
    if (curStudent->score->Course_ID==CourseId)
        {
            fout << curStudent->firstName <<" "<< curStudent->lastName << ",";
        }
    curStudent=curStudent->next;
  }
  fout.close();
}
void importScoreBoard(Student* stu)
{
    string CourseId;
    cout << "Enter Course ID:";
    cin.ignore();
    getline(cin, CourseId);
    string filename = CourseId + ".csv";
    ifstream fin(filename);
    if (!fin.is_open())
        {
            cout << "Error opening file: " << filename << endl;
            return;
        }
    string line;
    getline(fin, line);
    while (getline(fin, line))
            {
                string temp;
                Student* curStudent=stu;
                getline(fin, temp, ',');
                getline(fin, temp, ',');
                while (curStudent!=NULL&& curStudent->studentId!=temp)
                {
                    curStudent=curStudent->next;
                }
                getline(fin, temp, ',');
                curStudent->score->totalMark = stod(temp);
                getline(fin, temp, ',');
                curStudent->score->finalMark= stod(temp);
                getline(fin, temp, ',');
                curStudent->score->midtermMark = stod(temp);
                getline(fin, temp);
                curStudent->score->otherMark= stod(temp);
            }
    fin.close();
    cout << "Scoreboard imported successfully." << endl;
}


double Student::calGPA(){
    Score* curScore = score;
    double total = 0;
    int cnt = 0;
    while(curScore){
        total+=curScore->totalMark;
        curScore = curScore->next;
        cnt++;
    }
    total/=cnt;
    return total/10*4;
}
