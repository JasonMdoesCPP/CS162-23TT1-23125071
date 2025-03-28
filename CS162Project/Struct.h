#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string.h>
#include<string>
#include<sstream>
#include<limits>
#include<vector>
#include <iomanip>
#include<algorithm>
#include <conio.h>
using namespace std;
struct Student;
struct Date{
    int day;
    int year=0;
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
    char dow[3] ;// day of week
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
    void viewProfile();
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
    void viewProfile();
//All Updating function hlere
    void updateSchoolYear(Semester *&cur_semester);
    void importSchoolYear();
    void importCourse();
    void updateCourse(User& Head_User);
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

void addStudentToClassFromCsvFile(Class*clas, Student*stu, string className);
void createSeveralClasses(Class *&HeadClass);
void deleteClass(Class *&clas);
void addStudentToClass(Class* clas, Student* stu);
void UpdateCoursetoUser(string StudentID,string CourseID, string newCourseID, User &Head_User, int choice);
void CopyCourseInfo(Course cur_Course, Course newCourse);
void viewClasses(Class* HeadClass);
void viewStudentInClass(Class* HeadClass, Student* headStudent);
void exportStudentInCourseToCsvFile(Semester* semester, string CourseId);
void importScoreBoard(Student* stu, Semester *semester,string CourseId);
void publishScore();
void UpdateUser(User user);
void viewScoreOfCourse(Semester* semester, Student* student);
void updateStudentRes(Student *stu, string &course_ID, Semester *cur_semester);
void deleteAll(User& user, Class* headClass);
bool isValidDate(Date& date);
void UpdateClass(Class* &headClass, Student*stu);
void ImportClass(Class* headClass);
void viewScoreOfClass(Semester* semester, Student* student, Course* HeadCourse);
bool checkPublish();
void exportScoreBoard(Semester* semester, const string& filename, User head_User);
void viewYourCourse(Semester* cur_semester, Student* stu);
string takePasswdFromUser();
#endif // STRUCT_H_INCLUDED
