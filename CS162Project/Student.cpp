#include"Struct.h"
void Student::ViewScore(Course* HeadCourse,bool publishedScore) {
    if (publishedScore) {
        bool check = false;
        Course* curCourse = HeadCourse;
        while (curCourse) {
            Score* cur = score;
            while (cur) {
                if (curCourse->Course_ID == cur->Course_ID)
                    break;
                cur = cur->next;
            }
            if(cur){
                check = true;
                cout << "Course: " << curCourse->Course_name << endl;
                cout << "Mid term: " << cur->midtermMark << endl;
                cout << "Final: " << cur->finalMark << endl;
                cout << "Other: " << cur->otherMark << endl;
                cout << "Total: " << cur->totalMark << endl;
            }
            curCourse = curCourse->next;
        }
        if (check == false) cout << "You haven't joined any course";
    }
    else {
        cout << "Scores haven't published " << endl;
    }
}
double Student::calGPA() {
    Score* curScore = score;
    double total = 0;
    int cnt = 0;
    while (curScore) {
        total += curScore->totalMark;
        curScore = curScore->next;
        cnt++;
    }
    if (cnt==0) return -1;
    total /= cnt;
    return total / 10 * 4;
}

void Student::changePasswordOrUserName() {
    string temp;
    int ca;
    char c;
    do {
        cout << "1: Username" << endl;
        cout << "2: Password" << endl;
        cout << "Enter: ";
        cin >> ca;
        if (ca == 1) {
            cout << "New username: ";
            cin >> temp;
            if (temp == userName) {
                cout << "Similar to the old one" << endl;
                break;
            }
            cout << "Your new username: " << temp << endl;
            cout << "Are you sure?(y/n)";
            cin >> c;
            if (c == 'y') {
                userName = temp;
                cout << "Successful!" << endl;
            }
            else
                cout << "Cancel the operation!" << endl;
            break;
        }
        else if (ca == 2) {
            cout << "New password: ";
            cin >> temp;
            if (temp == passWord) {
                cout << "Similar to the old one!" << endl;
                break;
            }
            cout << "Your new password: " << temp << endl;
            cout << "Are you sure?(y/n)";
            cin >> c;
            if (c == 'y') {
                passWord = temp;
                cout << "Successful!" << endl;
            }
            else
                cout << "Cancel the operation!" << endl;
            break;
        }
        else
            cout << "Only choose (1|2)" << endl;
    } while (true);
}
void Student::viewProfile() {
    cout << "Student Profile:" << endl;
    cout << "  Student ID: " << studentId << endl;
    cout << "  Social ID: " << socialId<< endl;  // Mask social ID
    cout << "  Name: " << firstName << " " << lastName << endl;
    cout << "  Gender: " << (gender ? "Male" : "Female") << endl;
    cout << "  School Year: " << schoolYear << endl;
    cout << "  Class Name: " << className << endl;
    cout << "  Date of Birth: " << dateOfBirth.day << "/" << dateOfBirth.month << "/" << dateOfBirth.year << endl;
}
void viewYourCourse(Semester* cur_semester, Student* stu) {
    Course* cur = cur_semester->course;

    if (cur) {
        // Print table header
        cout << setw(20) << left << "Course ID" << setw(30) << left << "Course Name"
             << setw(20) << left << "Teacher"
            << setw(10) << right << "Credits" << endl;
        cout << setfill('-') << setw(20+30+20+10) << ""
            << setfill(' ') << endl;

        while (cur) {
            StudentEnrolled* curStudent = cur->studentEnrolled;

            while (curStudent) {
                if (curStudent->studentId == stu->studentId) {
                    // Print course information in each row
                    cout << setw(20) << left << cur->Course_ID << setw(30) << left << cur->Course_name
                        << setw(20) << left << cur->teacherName
                        << setw(10) << right << cur->numberOfCredits << endl;
                    break;
                }
                curStudent = curStudent->next;
            }
            cur = cur->next;
        }
    }
    else {
        cout << "You have not enrolled any courses yet!" << endl;
    }
}