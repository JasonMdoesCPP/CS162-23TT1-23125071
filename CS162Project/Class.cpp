#include"Struct.h"
void Class::addStudents(Student* stu) {
    cout << "Adding students (only student IDs required)." << endl;

    cout << "Enter number of students: ";
    int n;
    cin >> n;

    if (n <= 0) {
        cout << "Please input a positive integer number." << endl;
        cout << "Enter: ";
        cin >> n;
    }

    while (n--) {
        string temp;
        cout << "Student ID: ";
        cin >> temp;

        StudentEnrolled* curStudentEnroll = studentEnroll;
        bool check = false;

        // Check if student already enrolled in this class
        while (curStudentEnroll) {
            if (temp == curStudentEnroll->studentId) {
                check = true;
                cout << "This student (" << temp << ") has already been added to this class!" << endl;
                break;
            }
            curStudentEnroll = curStudentEnroll->next;
        }

        if (!check) {
            Student* cur = stu;

            // Find student by ID
            while (cur) {
                if (cur->studentId == temp) {
                    check = true;
                    if (cur->schoolYear != 1) {
                        cout << "Student with ID " << temp << " is not a 1st year student." << endl;
                    }
                    else if (!cur->className.empty()) {
                        cout << "Student with ID " << temp << " has already been added to class " << cur->className << "." << endl;
                    }
                    else {
                        // Add student to class and update file
                        cur->className = className;
                        StudentEnrolled* temp1 = new StudentEnrolled;
                        temp1->studentId = temp;
                        temp1->next = studentEnroll;
                        studentEnroll = temp1;

                        ofstream fout("Class/" + this->className + ".csv");
                        if (!fout) {
                            cout << "Cannot update student " << temp << " to file Class/" << this->className << ".csv" << endl;
                        }
                        else {
                            fout << "StudentID" << endl;
                            curStudentEnroll = studentEnroll;
                            while (curStudentEnroll) {
                                fout << curStudentEnroll->studentId << endl;
                                curStudentEnroll = curStudentEnroll->next;
                            }
                            fout.close();
                            cout << "Student with ID " << temp << " added to class " << className << "." << endl;
                        }
                    }
                    break;
                }
                cur = cur->next;
            }

            if (!check) {
                cout << "Student with ID " << temp << " not found." << endl;
            }
        }
    }
}
void Class::viewScore(Student* stu, Course* headCourse, bool publishedScore) {
    StudentEnrolled* curClasStu = studentEnroll;
    while (curClasStu) {
        Student* curStu = stu;
        while (curStu) {
            if (curStu->studentId == curClasStu->studentId) {
                cout << "Full name: " << curStu->firstName << " " << curStu->lastName << endl;
                cout << " ID: " << curStu->studentId << endl;
                curStu->ViewScore(headCourse, publishedScore);
                cout << "GPA: " << curStu->calGPA();
                break;
            }
            curStu = curStu->next;
        }
        curClasStu = curClasStu->next;
    }
}