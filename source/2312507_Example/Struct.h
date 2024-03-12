#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

#include <string>

struct Date{
    int day;
    int month;
    int year;
};

struct Course{
    Course* next;
    string name;
    string className;
    string lecturerName;
    int numberOfCredits;
    int maxSize = 50;
    Student* student;
};

struct Semester{
    Date startDay;
    Date endDay;
    Course* course;
};

struct SchoolYear{
    Semester* Semester;
    int yearStart;
    int yearEnd = yearStart+1;
};

struct Student{
    Student* next;
    string className;
    int No;
    string studentID;
    string firstName;
    string lastName;
    bool gender; //here I say 1 if is man, 0 if is woman
    Date DoB;
};

struct Staff{
    Staff* next;
    string staffID;
    string firstName;
    string lastName;
    SchoolYear sYear;
    Student* student;
};

struct User{
    User* next;
    Staff* next;
    Student* student;

    string username;
    string password;
};

#endif // STRUCT_H_INCLUDED
