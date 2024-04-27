#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string.h>
#include<string>
#include<sstream>
#include<limits>
using namespace std;
struct Student;
struct Date{
    int day;
    int year;
    int month;
};
struct Score{
    Score* next=nullptr;
    string Course_ID;
    double totalMark=0;
    double finalMark=0;
    double midtermMark=0;
    double otherMark=0;
};
struct StudentEnrolled{
    StudentEnrolled* next=nullptr;
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
    char dow[2] ;// day of week
    int session;
    void inputStudent2CourseFromFile(User &Head_User);
    void UpdateCourseInfo(User &Head_User);
    void AddStudentToCourse(Student* student);
    void RemoveStudentFromCourse(const string& studentId);
    void viewStudent(Student* headStu);
};
struct Semester{
    Course *course = nullptr;
    Date startDay;
    Date endDay;
    void addCourse();
    void viewCourse();
    Course* findCourseinSemester(string CourseID);
    void DeleteACourse(const string& courseId, User Head_User);
};
struct SchoolYear{
    SchoolYear* next=nullptr;
    Semester *semester = new Semester[3]; //3 semester only
    int yearStart;
    int yearEnd;


};
struct Class{
    Class* next=nullptr;
    string className; // 23tt1, 223tt2
    StudentEnrolled* studentEnroll = nullptr;  // include file has list of studentID(check if there are exist or not)
    Score *classScore = nullptr;  // create function that calculates the classScore
    void addStudents(Student* stu);
    void viewScore(Student* stu, Course* headCourse, bool publishedScore);
};
struct Student{
    Student *next = nullptr;
    Score *score=nullptr; /*include courses name so if wanting to allocate the course enrolled allocate this*/
    Date dateOfBirth;
    string className;
    string passWord;
    string userName;
    string studentId;
    string socialId;
    string firstName;
    string lastName;
    bool gender;
    int No;
    int schoolYear;
    void ViewScore(Course* HeadCourse, bool publishedScore);
    double calGPA();
    void changePasswordOrUserName();
};
struct StaffMember{
    string passWord;
    string userName;
    StaffMember*next = nullptr;
    SchoolYear* schoolYear = nullptr;
    string firstName;
    string lastName;
    void createSchoolYear();
    void addSemester(int yearStart,Semester *&cur_semester);
    void changePasswordOrUserName();

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
void UpdateCoursetoUser(string StudentID,string CourseID, string newCourseID, User &Head_User, int choice);
void CopyCourseInfo(Course cur_Course, Course newCourse);
void viewClasses(Class* HeadClass);
void viewStudentInClass(Class* HeadClass, Student* headStudent);
void exportStudentInCourseToCsvFile(Semester* semester);
void importScoreBoard(Student* stu, Semester *semester);
void publishScore(bool &publishedScore);
void UpdateUser(User user);
void viewScoreOfCourse(Semester* semester, Student* student);
void updateStudentRes(Student *stu);
void deleteAll(User& user, Class* headClass);
bool isValidDate(Date& date);
#endif // STRUCT_H_INCLUDED
