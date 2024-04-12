#include"Struct.h"
void StaffMember::createSchoolYear() {
    SchoolYear* cur = schoolYear;
    bool yearExists = false;

    cout << "Please input school year: ";
    int data;
    cin >> data;

    // Check if the school year already exists
    while (cur) {
        if (cur->yearStart == data) {
            yearExists = true;
            break;
        }
        cur = cur->next;
    }

    if (yearExists) {
        cout << "School year already exists." << endl;
    }
    else {
        SchoolYear* newYear = new SchoolYear;
        newYear->next = nullptr;
        newYear->yearStart = data;
        newYear->yearEnd = data + 1;

        if (schoolYear) {
            newYear->next=schoolYear;
            schoolYear = newYear;
        }
        else {
            schoolYear = newYear;
        }
    }
}

void StaffMember::addSemester(int yearStart, Semester*& cur_semester)
{
    SchoolYear* cur_year = schoolYear;
    while (cur_year)
    {
        if (cur_year->yearStart == yearStart)
        {
            cout << "You want to add semester 1, 2, or 3: ";
            int index;
            cin >> index;

            if (index < 1 || index > 3) {
                cout << "Invalid semester index!" << endl;
                return;
            }

            cur_semester = cur_year->semester + index - 1 ;

            // Check if the semester already exists by examining its courses
            if (cur_semester->course != nullptr) {
                cout << "Semester " << index << " already exists." << endl;
                cur_semester = nullptr;
                return;
            }
            // Input start day
            cout << "Enter start day (dd mm yyyy): ";
            cin >> cur_semester->startDay.day >> cur_semester->startDay.month >> cur_semester->startDay.year;

            // Input end day
            cout << "Enter end day (dd mm yyyy): ";
            cin >> cur_semester->endDay.day >> cur_semester->endDay.month >> cur_semester->endDay.year;

            return;
        }
        cur_year = cur_year->next;
    }
    cout << "No SchoolYear found!" << endl;
}
void StaffMember::changePasswordOrUserName() {
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
                cout << "Similar to the old one" << endl;
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