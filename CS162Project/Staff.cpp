#include"Struct.h"
void StaffMember::createSchoolYear() {
  SchoolYear* cur = schoolYear;
  bool yearExists = false;
  int data;

  do {
    cout << "Please input a valid school year (positive integer): ";
    cin >> data;

    // Check if input is valid (positive integer)
    if (!cin || data <= 0) {
      cout << "Invalid input. Please enter a positive integer." << endl;
      cin.clear(); // Clear error state from cin
      cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
    }
  } while (!cin || data <= 0); // Repeat until valid input is entered

  // Check if the school year already exists (same as before)
  while (cur) {
    if (cur->yearStart == data) {
      yearExists = true;
      break;
    }
    cur = cur->next;
  }

  if (yearExists) {
    cout << "School year already exists." << endl;
  } else {
    SchoolYear* newYear = new SchoolYear;
    newYear->next = nullptr;
    newYear->yearStart = data;
    newYear->yearEnd = data + 1;

    if (schoolYear) {
      newYear->next = schoolYear;
      schoolYear = newYear;
    } else {
      schoolYear = newYear;
    }
  }
}


void StaffMember::addSemester(int yearStart, Semester*& cur_semester) {
  SchoolYear* cur_year = schoolYear;
  while (cur_year) {
    if (cur_year->yearStart == yearStart) {
      int index;
      bool validInput = false;

      // Input validation loop for semester index
      while (!validInput) {
        cout << "You want to add semester 1, 2, or 3: ";
        cin >> index;

        if (cin.fail() || index < 1 || index > 3) {
            cout << "Invalid semester index! Please enter 1, 2, or 3." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            // Check if creating semester makes sense based on previous semesters
            if (index > 1) {
                // Check if semester 1 already exists
                if (cur_year->semester[0].startDay.year == 0) {
                    cout << "Please create Semester 1 before Semester " << index << endl;
                    return; // Exit without adding semester
                }
            }
            if (index > 2) {
                // Check if semester 2 already exists (assuming semesters are added sequentially)
                if (cur_year->semester[1].startDay.year == 0) {
                    cout << "Please create Semester 2 before Semester " << index << endl;
                    return; // Exit without adding semester
                }
            }
            validInput = true;
        }
      }
      

      // Check if the semester already exists
      if (cur_semester->startDay.year != 0) {
        cout << "Semester " << index << " already exists." << endl;
        return;
      }

      //Check if the semester is in the present or not


      //Update cur semester
      cur_semester = cur_year->semester + index - 1;

      // Input validation loop for start date
      validInput = false;
      while (!validInput) {
        cout << "Enter start day (dd mm yyyy): ";
        cin >> cur_semester->startDay.day >> cur_semester->startDay.month >> cur_semester->startDay.year;

        if (cin.fail() || !isValidDate(cur_semester->startDay)) {
          cout << "Invalid start date format! Please enter in dd mm yyyy format." << endl;
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
          validInput = true;
        }
      }

      // Input validation loop for end date (similar to start date)
      validInput = false;
      while (!validInput) {
        cout << "Enter end day (dd mm yyyy): ";
        cin >> cur_semester->endDay.day >> cur_semester->endDay.month >> cur_semester->endDay.year;

        if (cin.fail() || !isValidDate(cur_semester->endDay)) {
          cout << "Invalid end date format! Please enter in dd mm yyyy format." << endl;
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
          validInput = true;
        }
      }

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
void StaffMember::viewProfile() {
    cout << "Staff Member Profile:" << endl;
    cout << "  Name: " << firstName << " " << lastName << endl;
    cout << "  Username: " << userName << endl;  // Mask username
}