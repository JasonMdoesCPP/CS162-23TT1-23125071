#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

#include <string>
#include <fstream>
#include <iostream>
using namespace std;

struct DateOfBirth{
    int day;
    int year;
    int month;
};

/*Add a course to this semester: course id, course name, class name, teacher name, number of credits, the maximum number of students in the course (default 50), day of the week, and the session that the course will be performed (MON / TUE / WED / THU / FRI / SAT, S1 (07:30), S2 (09:30), S3(13:30) and S4 (15:30)). A course will be taught in only one session in a week.
 */
struct Score{
    double totalMark;
    double finalMark;
    double midtermMark;
    double otherMark;
};

struct StudentEnrolled{
    StudentEnrolled* next;
    string type; //20CLC1�, class 20CLC11, class 20VP�
    int No;
    string studentId;
    string socialId;
    string firstName;
    string lastName;
    string gender;
    DateOfBirth dateOfBirth;
    Score score;
};

struct CourseOfStudent{
    CourseOfStudent*next;
    string name; // View a list of his/her courses. He/she will study these courses in this semester.
    int semester;
    Score score;
};

//Then he/she will upload a CSV file, containing a list of students enrolled in the course.
struct Course{
    Course* next;
    StudentEnrolled *studentEnrolled;
    string id;
    string name;
    string classname;
    string teacherName;
    int numberOfCredits;
    int maxSize = 50;
    char dow ;// day of week
    int session;
    void inputStudent2CourseFromFile();
};

struct Semester{//3 only 
    int startDay;
    int endDay;
    Course *course;
    void addCourse();
    void viewTheListOfCourses();
    
};

struct SchoolYear{
    SchoolYear* next;
    Semester *semester = nullptr;
    int yearStart;
    int yearEnd = yearStart+1;
    void createSemester();
};

struct Student{
    string passWord;
    string userName;
    Student *next = nullptr;
    CourseOfStudent *courses;
    string type; //20CLC1�, class 20CLC11, class 20VP�
    int No;
    string studentId;
    string socialId;
    string firstName;
    string lastName;
    string gender;
    int schoolYear;
    DateOfBirth dateOfBirth;
};

struct StaffMember{
    string passWord;
    string userName;
    StaffMember*next = nullptr;
    string firstName;
    string lastName;
    SchoolYear* schoolYear;
    void createSchoolYear();
};


struct Class{
    Class* next;
    string classname; // 23tt1, 223tt2
    Student *student;
    void addStudents();
    void inputFromFile();
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

};




// External functions 

void inputFromFile(Class *clas, string name); 
void inputCourseFromFile();

#endif // STRUCT_H_INCLUDED


