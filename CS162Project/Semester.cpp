#include"Struct.h"
void Semester::addCourse() {
    if (this == nullptr) {
        std::cout << "There's no Semester to add Course to" << std::endl;
        return;
    }

    Course* temp = new Course;

    // Get course ID
    std::cout << "Please enter course ID: ";
    std::cin >> temp->Course_ID;

    //Check if a course with the same ID alreadu exists
    Course* current = course;
    while (current != nullptr) {
        if (current->Course_ID == temp->Course_ID) {
            std::cout << "Error: A course with ID " << temp->Course_ID << " already exists." << std::endl;
            delete temp; // Clean up temporary course
            return;
        }
        current = current->next;
    }

    // Get course name
    std::cout << "Please enter course name: ";
    std::cin.ignore(); // Clear input buffer
    std::getline(std::cin, temp->Course_name);

    // Get class name
    std::cout << "Please enter class name: ";
    std::cin >> temp->classname;

    // Get teacher's name
    std::cout << "Please enter teacher's name: ";
    std::cin.ignore();
    std::getline(std::cin, temp->teacherName);

    // Get number of credits with validation
    bool validCredits = false;
    while (!validCredits) {
        std::cout << "Please enter the number of credits (positive integer): ";
        std::cin >> temp->numberOfCredits;

        if (std::cin.fail() || temp->numberOfCredits <= 0) {
            std::cin.clear(); // Clear error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Invalid input. Please enter a positive integer." << std::endl;
        }
        else {
            validCredits = true;
        }
    }


    // Get maximum number of students with validation
    bool validMaxSize = false;
    while (!validMaxSize) {
        std::cout << "Please enter the maximal number of students in the course (positive integer): ";
        std::cin >> temp->maxSize;

        if (std::cin.fail() || temp->maxSize <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a positive integer." << std::endl;
        }
        else {
            validMaxSize = true;
        }
    }

    // Get day of week with validation
    bool validDow = false;
    while (!validDow) {
        std::cout << "Please enter the day the course will be performed in (M/T/W/Th/F/Sa/Su): ";
        std::cin.ignore(); // Clear input buffer
        std::cin.get(temp->dow, 3); // Read up to 2 characters + null terminator
        validDow = true;
       
    }
    // Input session

    bool validSession = false;
    while (!validSession) {
        cout << "Please enter the session (1 to 3): ";
        cin >> temp->session;

        if (std::cin.fail() || temp->session <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a positive integer." << std::endl;
        }
        else {
            validSession = true;
        }
    }
    if (course == nullptr)
    {
        temp->next = nullptr;
        course = temp;
    }
    else
    {
        temp->next = course;
        course = temp;
    }
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
