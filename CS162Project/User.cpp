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
    fin.open("student.csv");
    if (!fin)
    {
        cout << "Cannot open file student.csv";
        return;
    }
    students = nullptr;


    string line;
    getline(fin, line);
    string temp;

    while (getline(fin, temp, ','))
    {
        Student* newStudent = new Student;
        newStudent->next = nullptr;
        newStudent->passWord = temp;
        getline(fin, newStudent->userName, ',');
        getline(fin, newStudent->studentId, ',');
        getline(fin, newStudent->socialId, ',');
        getline(fin, newStudent->firstName, ',');
        getline(fin, newStudent->lastName, ',');
        string temp;
        getline(fin, temp, ',');
        newStudent->gender = stoi(temp);
        getline(fin, temp, ',');
        newStudent->schoolYear = stoi(temp);
        //Date
        getline(fin, temp, ',');
        newStudent->dateOfBirth.day = stoi(temp);
        getline(fin, temp, ',');
        newStudent->dateOfBirth.month = stoi(temp);
        getline(fin, temp);
        newStudent->dateOfBirth.year = stoi(temp);

        if (students == nullptr)
        {
            students = newStudent;
        }
        else
        {
            newStudent->next = students;
            students = newStudent;
        }
    }

}
void User::addInformationStaffMembers(){} 
//    ifstream fin;
//    fin.open("staffMember.csv");
//    if (!fin) {
//        cout << "Cannot open file staffMember.csv" << endl;
//        return;
//    }
//
//    staffMembers = nullptr;
//
//    string line;
//    getline(fin, line); // Skip header line (assuming CSV has a header)
//    while (getline(fin, line)) {
//        StaffMember* newStaffMember = new StaffMember;
//        newStaffMember->next = nullptr;
//
//        stringstream ss(line); // Use stringstream to parse comma-separated values
//
//        getline(ss, newStaffMember->userName, ',');
//        getline(ss, newStaffMember->passwWord, ',');
//        getline(ss, newStaffMember->firstName, ',');
//        getline(ss, newStaffMember->lastName, ',');
//
//        // Handle additional staff member fields (assuming no comma in these fields)
//        fin >> newStaffMember->schoolYear; // Assuming schoolYear can be directly read from file
//        newStaffMember->createSchoolYear(); // Call function to process schoolYear data (if needed)
//
//        if (staffMembers == nullptr) {
//            staffMembers = newStaffMember;
//        }
//        else {
//            newStaffMember->next = staffMembers;
//            staffMembers = newStaffMember;
//        }
//    }
//}
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