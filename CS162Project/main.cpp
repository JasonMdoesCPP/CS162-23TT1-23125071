//#include"Struct.h"
//using namespace std;
//int main()
//{
//    User user;
//    Semester* cur_semester=nullptr;
//    Class *HeadClass = nullptr;
//    user.addInformationStudent();
//    user.addInformationStaffMembers();
//    user.login();
//    if(user.user1){
//        Student* stu = user.user1;
//    }
//    if(user.user2){
//        StaffMember * staf = user.user2;
//        cout << "1. Create a school year " << endl;
//        cout << "2. Create several classes for 1st-year students" << endl;
//        cout << "3. Add new 1st year students to 1st-year classes." << endl;
//        cout << "4. Adding student to class from csv file" << endl;
//        cout << "5. Add Semester to School Year" << endl;
//        cout << "6 Add new Course"<<endl;
//        cout << "7. Add Student to Course" << endl;
//        cout << "0. Ending program!" << endl;
//        int ca;
//        cin >> ca;
//        while(ca){
//            if(ca == 1){
//                staf->createSchoolYear();
//            }else if(ca == 2){
//                createSeveralClasses(HeadClass);
//            }else if(ca == 3){
//                addStudentToClass(HeadClass, user.students);
//            }else if(ca == 4){
//                addStudentToClassFromCsvFile(HeadClass, user.students);
//            }
//            else if (ca == 5)
//            {
//                int yearStart=0;
//                cout << "Enter SchoolYear (Start Year):";
//                cin >> yearStart;
//                staf->addSemester(yearStart, cur_semester);
//            }
//            else if (ca == 6)
//            {
//                cur_semester->addCourse();
//            }
//            else if (ca == 7)
//            {
//                string CourseID;
//                cout << "Enter Course ID:";
//                cin.ignore();
//                getline(cin, CourseID);
//                Course* cur_Course=cur_semester->findCourseinSemester(CourseID);
//                if (cur_Course)
//                {
//                    cur_Course->inputStudent2CourseFromFile(user);
//                }
//            }
//            else if (ca == 10) {
//                string courseId;
//                cout << "Enter the Course ID to update: ";
//                cin >> courseId;
//                Course* curCourse = cur_semester->findCourseinSemester(courseId);
//                if (curCourse) {
//                    curCourse->UpdateCourseInfo();
//                    cout << "Course information updated successfully!" << endl;
//                }
//                else {
//                    cout << "Course not found!" << endl;
//                }
//            }
//            else if (ca == 11) {
//                // Add student to the course
//                string courseId;
//                cout << "Enter the Course ID to add student: ";
//                cin >> courseId;
//                Course* curCourse = cur_semester->findCourseinSemester(courseId);
//                if (curCourse) {
//                    // Prompt for student ID
//                    string studentId;
//                    cout << "Enter the Student ID to add to the course: ";
//                    cin >> studentId;
//                    // Find the student
//                    Student* curStudent = user.students;
//                    while (curStudent) {
//                        if (curStudent->studentId == studentId) {
//                            // Add student to the course
//                            curCourse->AddStudentToCourse(curStudent);
//                            cout << "Student added to the course successfully!" << endl;
//                            break;
//                        }
//                        curStudent = curStudent->next;
//                    }
//                    if (!curStudent) {
//                        cout << "Student not found!" << endl;
//                    }
//                }
//                else {
//                    cout << "Course not found!" << endl;
//                }
//            }
//            else if (ca == 12) {
//                // Remove student from the course
//                string courseId;
//                cout << "Enter the Course ID to remove student: ";
//                cin >> courseId;
//                Course* curCourse = cur_semester->findCourseinSemester(courseId);
//                if (curCourse) {
//                    // Prompt for student ID
//                    string studentId;
//                    cout << "Enter the Student ID to remove from the course: ";
//                    cin >> studentId;
//                    // Remove student from the course
//                    curCourse->RemoveStudentFromCourse(studentId);
//                    cout << "Student removed from the course successfully!" << endl;
//                }
//                else {
//                    cout << "Course not found!" << endl;
//                }
//            }
//            else if (ca == 13) {
//                // Delete a course
//                string courseId;
//                cout << "Enter the Course ID to delete: ";
//                cin >> courseId;
//                cur_semester->DeleteACourse(courseId);
//                cout << "Course deleted successfully!" << endl;
//            }
//            else
//                cout << "Enter wrong number!"  << endl;
//
//            cout << "1. Create a school year (2020-2021, for example)" << endl;
//            cout << "2. Create several classes for 1st-year students" << endl;
//            cout << "3. Add new 1st year students to 1st-year classes." << endl;
//            cout << "4. Adding student to class from csv file" << endl;
//            cout << "0. Ending program!" << endl;
//            cin >> ca;
//        }
//    }
//    cout << "finish";
//    user.deleteUser();
//    deleteClass(HeadClass);
//}
#include"Struct.h"
using namespace std;

int main() {
    User user;
    Semester* cur_semester = nullptr;
    Class* HeadClass = nullptr;
    user.addInformationStudent();
    user.addInformationStaffMembers();
    int op;
    cout << "1. Log in" << endl;
    cout << "0. End program!" << endl;
    cout << "Enter: " ;
    cin >> op;
    while(op){
        user.login();
        if (user.user1) {
            Student* stu = user.user1;
            int ca;
            do {
                cout << "1. View a list of courses you will study" << endl;
                cout << "2. View score" << endl;
                cout << "3. Change username or password" << endl;
                cout << "0. Log in with another account" << endl;
                cout << "Enter your choice: ";
                cin >> ca;
                switch (ca) {
                    case 1: {
                        Course* cur = cur_semester->course;
                        if (cur) {
                            cout << "The courses you will study are: " << endl;
                            while (cur) {
                                StudentEnrolled* curStudent = cur->studentEnrolled;
                                while (curStudent) {
                                    if (curStudent->studentId == stu->studentId) cout << cur->Course_ID << endl;
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
                        Course* temp = user.staffMembers->schoolYear->semester->course;
                        stu->ViewScore(temp);
                        break;
                    }
                    case 3:
                        stu->changePasswordOrUserName();
                    case 0:
                        break;
                    default:
                        cout << "Invalid choice!" << endl;
                        break;
                }
            } while (ca!=0);
            user.user1 = nullptr;
        }
        if (user.user2) {
            StaffMember* staf = user.user2;
            
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
                        addStudentToClassFromCsvFile(HeadClass, user.students);
                        break;
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
                        if(!staf->schoolYear->semester){
                            cout << "Semester hasn't created yet" << endl;
                            break;
                        }
                        exportStudentInCourseToCsvFile(staf->schoolYear->semester);
                        break;
                    }
                    case 18: {
                        if(!staf->schoolYear->semester){
                            cout << "No semester created" << endl;
                            break;
                        }
                        importScoreBoard(user.students, staf->schoolYear->semester);
                        break;
                    }
                    case 19:{
                        viewScoreOfCourse(staf->schoolYear->semester, user.students);
                        break;
                    }
                    case 20:{
                        updateStudentRes(user.students);
                        break;
                    }
                    case 21: {
                        publishScore();
                        break;
                    }
                    case 22:
                        staf->changePasswordOrUserName();
                        break;
                        
                        
                    case 0:
                        break;
                    default:
                        cout << "Invalid choice!" << endl;
                        break;
                }
            } while (ca != 0);
            user.user2 = nullptr;
        }
        cout << "1. Log in" << endl;
        cout << "0. End program!" << endl;
        cout << "Enter: " ;
        cin >> op;
    }
    cout << "Finish";
    UpdateUser(user);
    user.deleteUser();
    deleteClass(HeadClass);
    return 0;
}

