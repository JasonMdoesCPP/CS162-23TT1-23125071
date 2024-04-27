#include"Struct.h"
void User::login() {
    bool validInput = false; // Flag to track valid case selection

    while (!validInput) {
        cout << "1: Student" << endl;
        cout << "2: Staff member" << endl;
        cout << "Enter: ";

        // Validate case selection (integer between 1 and 2)
        int ca;
        if (cin >> ca) {
            if (ca == 1 || ca == 2) {
                validInput = true;
                this->ca = ca; // Store valid case selection
            }
            else {
                cout << "Wrong number! Please enter 1 for student or 2 for staff member." << endl;
                cin.clear(); // Clear error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            }
        }
        else {
            cout << "Invalid input! Please enter a number (1 or 2)." << endl;
            cin.clear(); // Clear error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }
    }

    string x, y;

    cout << "Username: ";
    cin.ignore(); // Discard any remaining newline character
    getline(cin, x);

    cout << "Password: ";
    getline(cin, y);

    Student* curStudent = students;
    StaffMember* curStaff = staffMembers;

    if (ca == 1) {
        while (curStudent) {
            if (x == curStudent->userName && y == curStudent->passWord) {
                user1 = curStudent;
                return;
            }
            curStudent = curStudent->next;
        }
    }
    else {
        while (curStaff) {
            if (x == curStaff->userName && y == curStaff->passWord) {
                user2 = curStaff;
                return;
            }
            curStaff = curStaff->next;
        }
    }

    cout << "Wrong Username or Password." << endl;
    // Offer retry or exit option
    char choice;
    do {
        cout << "Try again (y/n)? ";
        cin >> choice;
        choice = tolower(choice); // Convert input to lowercase for case-insensitive comparison
    } while (choice != 'y' && choice != 'n');

    if (choice == 'y') {
        login(); // Recursive call to retry login
    }
    else {
        cout << "Exiting login." << endl;
    }
}

void User::addInformationStudent() {
    ifstream fin;
    fin.open("User/student.csv");
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
void User::addInformationStaffMembers(){
    ifstream fin;
    fin.open("User/staffMember.csv");
    if(!fin) {
        cout << "Cannot open file staffMember.csv" << endl;
        return;
    }
    staffMembers = nullptr;
    string line;
    getline(fin, line); // Skip header line (assuming CSV has a header)
    while (getline(fin, line)) {
        StaffMember* newStaffMember = new StaffMember;
        newStaffMember->next = nullptr;
        stringstream ss(line); // Use stringstream to parse comma-separated values
        getline(ss, newStaffMember->passWord, ',');
        getline(ss, newStaffMember->userName, ',');
        getline(ss, newStaffMember->firstName, ',');
        getline(ss, newStaffMember->lastName, ',');
        // Handle additional staff member fields (assuming no comma in these fields
        if (staffMembers == nullptr) {
            staffMembers = newStaffMember;
        }
        else {
            newStaffMember->next = staffMembers;
            staffMembers = newStaffMember;
        }
    }
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
