#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED


#include <iostream>
#include <fstream>
#include <string.h>
#include<string>

using namespace std;
struct Student;
struct DateOfBirth{
    int day;
    int year;
    int month;
};
struct Score{
    Score* next;
    string courseName;
    double totalMark;
    double finalMark;
    double midtermMark;
    double otherMark;
};
struct StudentEnrolled{
    StudentEnrolled* next;
    string studentId;
};
struct User;
struct Course{
    Course* next;
    StudentEnrolled *studentEnrolled=nullptr;
    string Course_ID;
    string Course_name;
    string classname;
    string teacherName;
    int numberOfCredits;
    int maxSize = 50;
    char dow[1] ;// day of week
    int session;
    void inputStudent2CourseFromFile(User &Head_User);
};
struct Semester{
    Course *course = nullptr;
    int startDay;
    int endDay;
    void addCourse();
};
struct SchoolYear{
    SchoolYear* next;
    Semester *semester = nullptr;
    int yearStart;
    int yearEnd;
};
struct Class{
    Class* next;
    string className; // 23tt1, 223tt2
    StudentEnrolled* studentEnroll = nullptr;  // include file has list of studentID(check if there are exist or not)
    Score *classScore = nullptr;  // create function caculates the classScore
    void addStudents(Student* stu);
};
struct Student{
    Student *next = nullptr;
    Score *score; /*include courses name so if wanting to allocate the course enrolled allocate this*/
    DateOfBirth dateOfBirth;
    string className;
    string passWord;
    string userName;
    string studentId;
    string socialId;
    string firstName;
    string lastName;
    string gender;
    int No;
    int schoolYear;
};
struct StaffMember{
    string passWord;
    string userName;
    StaffMember*next = nullptr;
    SchoolYear* schoolYear = nullptr;
    string firstName;
    string lastName;
    void createSchoolYear();
};
struct User{
    StaffMember *staffMembers;
    Student *students;
    int ca; // case 1: student case 2: staffMember
    StaffMember *user2 = nullptr;
    Student *user1 = nullptr;
    void login();
    void addInformationStudent();
    void addInformationStaffMembers();
    void deleteUser();
};

void addStudentToClassFromCsvFile(Class*clas, Student*stu);
void createSeveralClasses(Class *&HeadClass);
void deleteClass(Class *&clas);
void addStudentToClass(Class* clas, Student* stu);
void UpdateCoursetoUser(string StudentID,string CourseName,string newCourseName, User &Head_User);
#endif // STRUCT_H_INCLUDED
