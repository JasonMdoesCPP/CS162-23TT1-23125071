#include"Struct.h"
void Student::ViewScore(Course* HeadCourse,bool publishedScore) {
    if (publishedScore) {
        Score* cur = score;
        while (cur) {
            Course* curCourse = HeadCourse;
            while (curCourse) {
                if (curCourse->Course_ID == cur->Course_ID)
                    break;
                curCourse = curCourse->next;
            }
            cout << "Course: " << curCourse->Course_name << endl;
            cout << "Mid term: " << cur->midtermMark << endl;
            cout << "Final: " << cur->finalMark << endl;
            cout << "Other: " << cur->otherMark << endl;
            cout << "Total: " << cur->totalMark << endl;
            cur = cur->next;
        }
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