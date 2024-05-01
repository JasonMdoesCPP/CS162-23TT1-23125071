#include"Struct.h"
using namespace std;

int main() {

    bool publish = checkPublish();

    User user;
    Semester *cur_semester=nullptr;
    Class* HeadClass = nullptr;
    user.addInformationStudent();
    user.addInformationStaffMembers();
    UpdateClass(HeadClass, user.students);
    int op;
    cout << "1. Log in" << endl;
    cout << "0. End program!" << endl;
    cout << "Enter: " ;
    cin >> op;
    bool checkUpdate = false;
    while(op){
        user.login();
        if (user.user1) {
            Student* stu = user.user1;
            if(!checkUpdate){
                user.staffMembers->updateSchoolYear(cur_semester);
                user.staffMembers->updateCourse(user);
                checkUpdate = true;
            }
//Update information


    //
            int ca;
            do {
                cout << "1. View a list of courses you will study" << endl;
                cout << "2. View score" << endl;
                cout << "3. Change username or password" << endl;
                cout << "4. View your profile" << endl;
                cout << "0. Log in with another account" << endl;
                cout << "Enter your choice: ";
                cin >> ca;
                switch (ca) {
                    case 1: {
                        Course* cur = cur_semester->course;
                        if (cur) {
                            cout << "The courses you will study in this course are: " << endl;
                            while (cur) {
                                StudentEnrolled* curStudent = cur->studentEnrolled;
                                while (curStudent) {
                                    if (curStudent->studentId == stu->studentId) {
                                        cout <<  "- "<< cur->Course_name << endl;
                                        break;
                                    }
                                    curStudent = curStudent->next;
                                }
                                cur = cur -> next;
                            }
                        }
                        else {
                            cout << "You have not enrolled any courses yet!" << endl;

                        }
                        break;
                    }
                    case 2: {
                        Course* temp = cur_semester->course;
                        stu->ViewScore(temp, publish);
                        break;
                    }
                    case 3:
                        stu->changePasswordOrUserName();
                        break;
                    case 4:
                        stu->viewProfile();
                        break;
                    case 0:
                        break;
                    default:
                        cout << "Invalid choice!" << endl;
                        break;
                }
            } while (ca!=0);
            user.user1 = nullptr; //What is it for?
            //Update all the files
        }
        if (user.user2) {
            StaffMember* staf = user.user2;
 // Update information
            if(!checkUpdate){
                staf->updateSchoolYear(cur_semester);
                staf->updateCourse(user);
                checkUpdate = true;
            }
            int ca;
            do {
                cout << "1. Create a school year" << endl;
                cout << "2. Create several classes for 1st-year students" << endl;
                cout << "3. Add new 1st year students to 1st-year classes." << endl;
                cout << "4. Adding student to class from csv file" << endl;
                cout << "5. Add Semester to School Year" << endl;

                cout << "6. Add new Course" << endl;
                cout << "7. Add Student to Course from csv file" << endl;
                cout << "9. Update course information" << endl;
                cout << "10. Add a student to the course" << endl;
                cout << "11. Remove a student from the course" << endl;
                cout << "12. Delete a course" << endl;

                cout << "13. View a list of classes" << endl;
                cout << "14. View a list of students in a class" << endl;
                cout << "15. View a list of courses" << endl;
                cout << "16. View a list of students in a course" << endl;
                cout << "17. Export the student in course to csv file" << endl;
                cout << "18. Import a score board" << endl;
                cout << "19. View score board of the course" << endl;
                cout << "20. Update a student's result " << endl;
                cout << "21. publish student score!!" << endl;
                cout << "22. Change username or password" << endl;
                cout << "23. View the scoreboard of a class" << endl;
                cout << "24. View your profile" << endl;
                cout << "0. Log in another account" << endl;

                cout << "Enter your choice: ";
                cin >> ca;

                switch (ca) {
                    case 1:
                        staf->createSchoolYear();
                        break;
                    case 2:
                        createSeveralClasses(HeadClass);
                        break;
                    case 3:
                        addStudentToClass(HeadClass, user.students);
                        break;
                    case 4:
                    {
                        string className;
                        cout << "Enter class name: ";
                        cin >> className;
                        addStudentToClassFromCsvFile(HeadClass, user.students, className);
                        break;
                    }
                    case 5: {
                        int yearStart = 0;
                        cout << "Enter SchoolYear (Start Year):";
                        cin >> yearStart;
                        staf->addSemester(yearStart, cur_semester);
                        break;
                    }
                    case 6:
                        cur_semester->addCourse();
                        break;
                    case 7: {
                        string CourseID;
                        cout << "Enter Course ID:";
                        cin.ignore();
                        getline(cin, CourseID);
                        Course* cur_Course = cur_semester->findCourseinSemester(CourseID);
                        if (cur_Course) {
                            cur_Course->inputStudent2CourseFromFile(user);
                        }
                        else cout << "No Course found!";
                        break;
                    }
                    case 9: {
                        string courseId;
                        cout << "Enter the Course ID to update: ";
                        cin >> courseId;
                        Course* curCourse = cur_semester->findCourseinSemester(courseId);
                        if (curCourse) {
                            curCourse->UpdateCourseInfo(user);
                            cout << "Course information updated successfully!" << endl;
                        }
                        else {
                            cout << "Course not found!" << endl;
                        }
                        break;
                    }
                    case 10: {
                        string courseId;
                        cout << "Enter the Course ID to add student: ";
                        cin >> courseId;
                        Course* curCourse = cur_semester->findCourseinSemester(courseId);
                        if (curCourse) {
                            string studentId;
                            cout << "Enter the Student ID to add to the course: ";
                            cin >> studentId;
                            Student* curStudent = user.students;
                            while (curStudent) {
                                if (curStudent->studentId == studentId) {
                                    curCourse->AddStudentToCourse(curStudent);
                                    break;
                                }
                                curStudent = curStudent->next;
                            }
                            if (!curStudent) {
                                cout << "Student not found!" << endl;
                            }
                        }
                        else {
                            cout << "Course not found!" << endl;
                        }
                        break;
                    }
                    case 11: {
                        string courseId;
                        cout << "Enter the Course ID to remove student: ";
                        cin >> courseId;
                        Course* curCourse = cur_semester->findCourseinSemester(courseId);
                        if (curCourse) {
                            string studentId;
                            cout << "Enter the Student ID to remove from the course: ";
                            cin >> studentId;
                            curCourse->RemoveStudentFromCourse(studentId);
                            //Update to User
                            UpdateCoursetoUser(studentId, courseId, courseId, user, 2);
                            cout << "Student removed from the course successfully!" << endl;
                        }
                        else {
                            cout << "Course not found!" << endl;
                        }
                        break;
                    }
                    case 12: {
                        string courseId;
                        cout << "Enter the Course ID to delete: ";
                        cin >> courseId;
                        cur_semester->DeleteACourse(courseId,user);
                        cout << "Course deleted successfully!" << endl;
                        break;
                    }
                    case 13:
                        viewClasses(HeadClass);
                        break;
                    case 14:
                        viewStudentInClass(HeadClass, user.students);
                        break;
                    case 15:
                        cur_semester->viewCourse();
                        break;
                    case 16: {
                        string courseID;
                        cout << "Enter the course ID: ";
                        cin >> courseID;
                        Course* curCourse = cur_semester->findCourseinSemester(courseID);
                        if (curCourse) curCourse->viewStudent(user.students);
                        else {
                            cout << "Course not found!" << endl;


                        }
                        break;
                    }
                    case 17: {
                        if(!cur_semester){
                            cout << "Semester hasn't created yet" << endl;
                            break;
                        }
                        exportStudentInCourseToCsvFile(cur_semester);
                        break;
                    }
                    case 18: {
                        if(!staf->schoolYear->semester){
                            cout << "No semester created" << endl;
                            break;
                        }
                        string CourseId;
                        cout << "Enter Course ID:";
                        cin.ignore();
                        getline(cin, CourseId);
                        importScoreBoard(user.students, staf->schoolYear->semester, CourseId);
                        break;
                    }
                    case 19:{
                        viewScoreOfCourse(cur_semester, user.students);
                        break;
                    }
                    case 20:{
                        string tempCourse;
                        updateStudentRes(user.students, tempCourse, cur_semester);
                        exportScoreBoard(cur_semester, tempCourse, user);
                        break;
                    }
                    case 21: {
                        publishScore();
                        publish = checkPublish();
                        break;
                    }
                    case 22:
                        staf->changePasswordOrUserName();
                        break;
                    case 23:
                        viewScoreOfClass(cur_semester, user.students, cur_semester->course);
                        break;
                    case 24:
                        staf->viewProfile();
                        break;
                    case 0:
                        break;
                    default:
                        cout << "Invalid choice!" << endl;
                        break;
                }
            } while (ca != 0);
            //What is it for?
            //Create and Update all the files
            user.user2->importSchoolYear();
            user.staffMembers->importCourse();
            user.user2 = nullptr;
        }
        cout << "1. Log in" << endl;
        cout << "0. End program!" << endl;
        cout << "Enter: " ;
        cin >> op;
    }
    cout << "Finish";
    UpdateUser(user);
    ImportClass(HeadClass);
    user.deleteUser();
    deleteClass(HeadClass);
    deleteAll(user, HeadClass);
    return 0;
}

