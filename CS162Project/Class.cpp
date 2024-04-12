#include"Struct.h"
void Class::addStudents(Student* stu)
{
    cout << "Only need the Id of students for adding" << endl;
    cout << "Enter number of students: ";
    int n;
    cin >> n;
    if (n <= 0) {
        cout << "Pls input the positive integer number" << endl;
        cout << "Enter: ";
    }
    while (n--) {
        Student* cur = stu;
        string temp;
        cout << "Student Id: ";
        cin >> temp;
        StudentEnrolled* curStudentEnroll = studentEnroll;
        // check if in class ?
        bool check = false;
        while (curStudentEnroll) {
            if (temp == curStudentEnroll->studentId) {
                check = true;
                break;
            }
            curStudentEnroll = curStudentEnroll->next;
        }
        if (check) {
            cout << "This student has been added in this class!" << endl;
        }
        if (!check) {
            while (cur) {
                if (cur->studentId == temp) {
                    if (cur->schoolYear == 1) {
                        cur->className = className;
                        check = true;
                        break;
                    }
                    else
                        break;
                }
                cur = cur->next;
            }
            if (check) {
                StudentEnrolled* temp1 = new StudentEnrolled;
                temp1->studentId = temp;
                temp1->next = studentEnroll;
                studentEnroll = temp1;
            }
            else {
                cout << "Doesn't find any student having this id" << endl;
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