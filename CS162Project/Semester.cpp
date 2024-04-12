#include"Struct.h"
void Semester::addCourse() {
    if (this == nullptr)
    {
        cout << "There's no Semester to add Course to";
        return;
    }
    Course* temp = new Course;
    cout << "Please enter course ID: ";
    cin >> temp->Course_ID;
    cout << "Please enter course name: ";
    cin.ignore();
    getline(cin, temp->Course_name);
    cout << "Please enter class name: ";
    cin >> temp->classname;
    cout << "Please enter teacher's name: ";
    cin.ignore();
    getline(cin, temp->teacherName);
    cout << "Please enter the number of credits: ";
    cin >> temp->numberOfCredits;
    cout << "Please enter the maximal number of students in the course: ";
    cin >> temp->maxSize;
    cout << "Please enter the day the course will be performed in (M/T/W/Th/F/Sa/Su):";
    cin >> temp->dow; // Increase size to accommodate the null terminator
    cout << "Please enter the session the course will be performed in: ";
    cin >> temp->session;
    if (course == nullptr) {
        course = temp;
        temp->next = nullptr;
    }
    else {
        temp->next = course;
        course = temp;
    }
    cout << "Course created!" << endl;
}
Course* Semester::findCourseinSemester(string CourseID)
{
    Course* cur_Course = course;
    while (cur_Course != nullptr)
    {
        if (cur_Course->Course_ID == CourseID)
            return cur_Course;
        cur_Course = cur_Course->next;
    }
    return nullptr;
}
// Member function to delete a course from a semester
void Semester::DeleteACourse(const string& courseId, User Head_User) {
    Course* prev = nullptr;
    Course* current = course;

    // Traverse the list to find the course
    while (current != nullptr) {
        if (current->Course_ID == courseId) {
            // If found, remove it from the list
            if (prev == nullptr) {
                course = current->next;
            }
            else {
                prev->next = current->next;
            }
            // Delete all associated memory
            delete current;
            break;
        }
        prev = current;
        current = current->next;
    }
    //Update to User
    Student* cur_student = Head_User.students;
    while (cur_student)
    {
        Score* prev_score = nullptr;
        Score* cur_score = cur_student->score;
        while (cur_score)
        {
            if (cur_score->Course_ID == courseId)
            {
                if (prev_score == nullptr)
                {
                    cur_student->score = cur_score->next;
                }
                else prev_score->next = cur_score->next;

                delete cur_score;
                break;
            }
            prev_score = cur_score;
            cur_score = cur_score->next;
        }
        cur_student = cur_student->next;
    }
}
void Semester::viewCourse() {
    Course* cur = course;
    if (!cur) {
        cout << "There are no courses added yet." << endl;
    }
    cout << "The added courses in this semester have their courses' name to be: " << endl;
    while (cur) {
        cout << "- " << cur->Course_name << endl;
        cur = cur->next;
    }


}
