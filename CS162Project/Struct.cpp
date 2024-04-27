#include "Struct.h"
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
    Class* cur_class = clas;
    //Check if Class exists
    while(cur_class){
        if(cur_class->className == className){
            check = true;
            break;
        }
        cur_class = cur_class->next;
    }
   
    fin.open("Class/"+className+".csv");
    if(!fin.is_open()){
        cout << "Doesn't have this class' csv file";
        return;
    }
    //Read file
    if(check){
        string line;
        getline(fin, line); // Read and discard header line
        while(getline(fin,line)){
            bool flag = false;
            string studentId;
            studentId = line;
            StudentEnrolled* curStudentEnrolled = cur_class->studentEnroll;
    //Check if student had been here or not
            while(curStudentEnrolled){
                if(studentId == curStudentEnrolled->studentId){
                    cout << "The student with ID " << studentId << " has been added in this class!" << endl;
                    flag = true;
                }
                curStudentEnrolled=curStudentEnrolled->next;
            }
    //If it is new Student
            if(!flag){
                Student* cur_student = stu;
                while(cur_student){
                    if(cur_student->studentId == studentId){
                        if (!cur_student->className.empty())
                        {
                            cout << "The student with ID:" << cur_student->studentId << " is already in class " << cur_student->className<<endl;
                            flag = true;
                            break;
                        }
                        StudentEnrolled* newStudent = new StudentEnrolled;
                        newStudent->studentId = studentId;
                        newStudent->next = cur_class->studentEnroll;
                        cur_class->studentEnroll = newStudent;
                        cur_student->className = cur_class->className;
                        flag = true;
                        break;
                    }
                    cur_student = cur_student->next;
                }
                if (flag == false) cout << "Student with ID " << studentId << " doesn't exist!"<<endl;
            }
        }
    }
    else
        cout << "The class doesn't exist " << endl;
    
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
                        cur_Student->score = nullptr;
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
void publishScore(bool &publishedScore){
    publishedScore = true;
}
void exportStudentInCourseToCsvFile(Semester* semester)
{ string CourseId;
    cout << "Enter Course ID:";
    cin.ignore();
    getline(cin, CourseId);
    Course* curCourse = semester->course;
    while(curCourse){
        if(curCourse->Course_ID == CourseId){
            break;
        }
        curCourse = curCourse->next;
    }
    if(!curCourse){
        cout << "Don't have any course having this name!" <<endl;
        return;
    }
    string filename = CourseId + "Students.csv";
    ofstream fout(filename, ios::trunc);
    if (!fout.is_open())
    {
        cout << "Error opening file: " << filename << endl;
        return;
    }
    fout<<"StudentID"<<endl;
    StudentEnrolled* curStu = curCourse->studentEnrolled;
    while (curStu){
        fout << curStu->studentId << endl;
        curStu = curStu->next;
    }
    fout.close();
}
void importScoreBoard(Student* stu, Semester* semester)
{
    string CourseId;
    cout << "Enter Course ID:";
    cin.ignore();
    getline(cin, CourseId);
    string filename = "Course/"+CourseId + "Score.csv";
    ifstream fin(filename);
    if (!fin.is_open())
    {
        cout << "Error opening file: " << filename << endl;
        return;
    }
    string line;
    getline(fin, line);
    string temp;
    while (getline(fin, temp, ','))
    {
        Student* curStudent = stu;
        bool studentFound = false;
        while (curStudent != NULL)
        {
            if (curStudent->studentId == temp)
            {
                studentFound = true;
                break;
            }
            curStudent = curStudent->next;
        }
        if (!studentFound)
        {
            // Print out the student ID of the unmatched student
            cout << "Unmatched student ID: " << temp << endl<<endl;
            getline(fin, temp); // Ignore the rest of the line
            continue; // Move to the next line
        }

        getline(fin, temp, ',');
        string courseID = temp;
        Score* curScore = curStudent->score;
        if (courseID != CourseId)
        {
            cout << "Problem with student " << curStudent->studentId << endl;
            cout << "We are updating for course "<< CourseId<<" not course "<<courseID<<endl<<endl;
            getline(fin, temp);
            continue;
        }
        bool courseFound = false;
        while (curScore)
        {
            if (curScore->Course_ID == courseID)
            {
                courseFound = true;
                break;
            }
            curScore = curScore->next;
        }
        if (!courseFound)
        {
            // Print out the course ID that doesn't match
            cout << "Student with ID " << curStudent->studentId<<" has not attended to course "<< courseID<<endl<<endl;
            getline(fin, temp); // Ignore the rest of the line
            continue; // Move to the next line
        }

        getline(fin, temp, ',');
        curScore->midtermMark = stod(temp);
        getline(fin, temp, ',');
        curScore->finalMark = stod(temp);
        getline(fin, temp, ',');
        curScore->otherMark = stod(temp);
        getline(fin, temp);
        curScore->totalMark = stod(temp);
    
    }
    fin.close();
    cout << "Scoreboard imported successfully." << endl;
}
void UpdateUser(User user){
    ofstream fout;
    fout.open("student.txt", ios::trunc);
    if(!fout.is_open()){
        cout << "Error update file" << endl;
        return;
    }
    Student* cur = user.students;
    while(cur){
        fout << cur->passWord << " ";
        fout << cur->userName << " ";
        fout <<  cur->studentId<< " ";
        fout <<  cur->socialId<< " ";
        fout <<  cur->firstName<< " ";
        fout <<  cur->lastName<< " ";
        fout <<  cur->gender<< " ";
        fout <<  cur->schoolYear;
        cur = cur->next;
        fout << endl;
    }
    fout << "eof" << endl;
    fout.close();
    fout.open("staffMember.txt", ios::trunc);
    if(!fout.is_open()){
        cout << "Error update file" << endl;
        return;
    }
    StaffMember* cur1 = user.staffMembers;
    while(cur1){
        fout << cur1->passWord<< " ";
        fout << cur1->userName<< " ";
        fout <<cur1->firstName<< " ";
        fout <<cur1->lastName;
        cur1 = cur1->next;
        fout << endl;
    }
    fout << "eof" << endl;
    fout.close();
}
void viewScoreOfCourse(Semester* semester, Student* student){
    string courseID;
    cout << "Enter course ID: " ;
    cin >> courseID;
    Course *curCourse = semester->course;
    while(curCourse){
        if(curCourse->Course_ID == courseID){
            break;
        }
        curCourse = curCourse->next;
    }
    if(!curCourse){
        cout << "Doesn't have this course name!" << endl;
        return;
    }
    Student* curStu=student;
    Score* res = new Score;
    res->finalMark = 0;
    res->midtermMark = 0;
    res->otherMark = 0;
    res->totalMark = 0;
    int cnt = 0;
    while(curStu){
        Score* curScore = curStu->score;
        while(curScore){
            if(curScore->Course_ID == curCourse->Course_ID){
                cnt++;
                res->finalMark += curScore->finalMark;
                res->midtermMark += curScore->midtermMark;
                res->otherMark += curScore->otherMark;
                res->totalMark +=curScore->totalMark;
            }
            curScore = curScore->next;
        }
        curStu = curStu->next;
    }
    cout <<"This " << curCourse->Course_name << " course has the score board: " << endl;
    cout << "Midterm: " << (float)res->midtermMark/cnt << endl;
    cout << "Final: " << (float)res->finalMark/cnt << endl;
    cout << "Other: " << (float)res->totalMark/cnt << endl;
    cout << "Total: " << (float)res->finalMark/cnt << endl;
    delete res;
}
void updateStudentRes(Student *stu){
    string studentID;
    cout << "Enter Student ID you want to update: ";
    cin >> studentID;
    Student* curStu = stu;
    while(curStu){
        if(curStu->studentId == studentID){
            break;
        }
        curStu = curStu->next;
    }
    if(!curStu){
        cout << "Don't have any student have this ID"<< endl;
        return;
    }
    Score* curScore = curStu->score;
    while(curScore){
        char ca;
        cout << "Do you want to update the result of the course have ID:" << curScore->Course_ID << endl;
        cout << "(y/n): ";
        cin >> ca;
        if(ca == 'y'){
            cout << "Midterm:";
            cin >> curScore->midtermMark;
            cout << "Final: ";
            cin >> curScore->finalMark;
            cout << "Other: ";
            cin >> curScore->otherMark;
            cout << "Total: ";
            cin >> curScore->totalMark;
            curScore=curScore->next;
        }else if(ca == 'n'){
            curScore=curScore->next;
        }else{
            cout << "Choose y/n only " << endl;
        }
    }
}
void deleteAll(User& user, Class* headClass) {
    // Delete all students in User
    Student* studentPtr = user.students;
    while (studentPtr != nullptr) {
        // Delete scores
        Score* scorePtr = studentPtr->score;
        while (scorePtr != nullptr) {
            Score* temp = scorePtr;
            scorePtr = scorePtr->next;
            delete temp;
        }
        // Delete the student
        Student* temp = studentPtr;
        studentPtr = studentPtr->next;
        delete temp;
    }
    user.students = nullptr; // Set user's students pointer to null

    // Delete all staff members in User
    StaffMember* staffPtr = user.staffMembers;
    while (staffPtr != nullptr) {
        // Delete school years
        SchoolYear* yearPtr = staffPtr->schoolYear;
        while (yearPtr != nullptr) {
            // Delete semesters
            Semester* semesterPtr = yearPtr->semester;
            while (semesterPtr != nullptr) {
                // Delete courses
                Course* coursePtr = semesterPtr->course;
                while (coursePtr != nullptr) {
                    // Delete students enrolled in the course
                    StudentEnrolled* enrolledPtr = coursePtr->studentEnrolled;
                    while (enrolledPtr != nullptr) {
                        StudentEnrolled* temp = enrolledPtr;
                        enrolledPtr = enrolledPtr->next;
                        delete temp;
                    }
                    // Delete the course
                    Course* temp = coursePtr;
                    coursePtr = coursePtr->next;
                    delete temp;
                }
                // Delete the semester
                Semester* temp = semesterPtr;
                delete temp;
            }
            // Delete the school year
            SchoolYear* temp = yearPtr;
            yearPtr = yearPtr->next;
            delete temp;
        }
        // Delete the staff member
        StaffMember* temp = staffPtr;
        staffPtr = staffPtr->next;
        delete temp;
    }
    user.staffMembers = nullptr; // Set user's staff members pointer to null

    // Delete all classes
    Class* classPtr = headClass;
    while (classPtr != nullptr) {
        // Delete enrolled students
        StudentEnrolled* enrolledPtr = classPtr->studentEnroll;
        while (enrolledPtr != nullptr) {
            StudentEnrolled* temp = enrolledPtr;
            enrolledPtr = enrolledPtr->next;
            delete temp;
        }
        // Delete class scores
        Score* scorePtr = classPtr->classScore;
        while (scorePtr != nullptr) {
            Score* temp = scorePtr;
            scorePtr = scorePtr->next;
            delete temp;
        }
        // Delete the class
        Class* temp = classPtr;
        classPtr = classPtr->next;
        delete temp;
    }
}
