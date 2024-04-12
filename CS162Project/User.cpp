#include"Struct.h"
void User::login() {
    cout << "1: Student" << endl;
    cout << "2: Staff member" << endl;
    cout << "Enter: ";
    int ca;
    cin >> ca;
    while (ca != 1 && ca != 2) {
        cout << "Wrong number !" << endl;
        cout << "1: Student" << endl;
        cout << "2: Staff member" << endl;
        cout << "Enter: ";
        cin >> ca;
    }
    string x, y;
    cout << "Username: ";
    cin.ignore();
    getline(cin, x);
    cout << "Password: ";
    getline(cin, y);
    if (ca == 1) {
        Student* cur = students;
        while (cur) {
            if (x == cur->userName)
                if (y == cur->passWord) {
                    user1 = cur;
                    return;
                }
            cur = cur->next;
        }
    }
    else {
        StaffMember* cur = staffMembers;
        while (cur) {
            if (x == cur->userName)
                if (y == cur->passWord) {
                    user2 = cur;
                    return;
                }
            cur = cur->next;
        }
    }
    if (!user1 && !user2) {
        cout << " Wrong Username or Password" << endl;
        login();
    }
}
void User::addInformationStudent() {
    ifstream fin;
    fin.open("student.txt");
    students = new Student;
    Student* cur = students;
    Student* before = students;
    string temp;
    while (fin >> temp) {
        if (temp == "eof") {
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
void User::addInformationStaffMembers() {
    ifstream fin;
    fin.open("staffMember.txt");
    staffMembers = new StaffMember;
    StaffMember* cur = staffMembers;
    StaffMember* before = staffMembers;
    string temp;
    while (fin >> temp) {
        if (temp == "eof") {
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
void User::deleteUser() {
    while (students) {
        Student* temp = students;
        students = students->next;
        delete temp;
    }
    while (staffMembers) {
        StaffMember* temp = staffMembers;
        staffMembers = staffMembers->next;
        delete temp;
    }
    students = nullptr;
    staffMembers = nullptr;
}