#include"Struct.h"
void Course::inputStudent2CourseFromFile(User& Head_User)
{
    string filename = Course_ID + "Students.csv";
    ifstream fin(filename);
    if (!fin.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return;
    }
    string line;
    getline(fin, line); // Read and discard header line
    string studentId;
    while (getline(fin, studentId)) {

        //Check in user
        bool check = false;
        Student *cur = Head_User.students;
        while (cur)
        {
            if (cur->studentId==studentId)
            {   
                check = true;
                break;
            }
            cur = cur->next;
        }
        
        // Check if the student is already enrolled
        StudentEnrolled* curEnrollment = studentEnrolled;
        bool alreadyEnrolled = false;
        while (curEnrollment != nullptr) {
            if (curEnrollment->studentId == studentId) {
                alreadyEnrolled = true;
                break;
            }
            curEnrollment = curEnrollment->next;
        }

        if (!alreadyEnrolled && check) {
            // Create a new StudentEnrolled node
            StudentEnrolled* newEnrollment = new StudentEnrolled;
            newEnrollment->studentId = studentId;
            newEnrollment->next = studentEnrolled;
            studentEnrolled = newEnrollment;

            // Update to User
            UpdateCoursetoUser(studentId, Course_ID, Course_ID, Head_User, 1);
        }

    }
    fin.close();
}
// Member function to update course information
void Course::UpdateCourseInfo(User& Head_User)
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
    cin >> dow;
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
    StudentEnrolled* cur_student = studentEnrolled;

    while (cur_student)
    {
        if (cur_student->studentId == student->studentId)
        {
            cout << "Student's already in the course!" << endl;
            return;
        }
        cur_student = cur_student->next;
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
void Course::viewStudent(Student* headStu) {
    StudentEnrolled* cur = studentEnrolled;
    if (!cur) {
        cout << "No students have been added to the course yet!" << endl;
        return;
    }
    cout << "The students in this course have their full name to be:" << endl;
    while (cur) {
        Student* temp = headStu;
        while (temp) {
            if (temp->studentId == cur->studentId) {
                cout << temp->studentId << "- " << temp->firstName << " " << temp->lastName << endl;
                break;
            }
            temp = temp->next;
        }
        cur = cur->next;
    }
    cout << endl;

}
