#include"Struct.h"
void UpdateClass(Class*& headClass, Student* stu) {
    ifstream fin;
    fin.open("Class/class.txt");
    if (!fin.is_open()) {
        cout << "Error!" << endl;
    }
    string className;
    while (getline(fin, className)) {
        Class* newClass = new Class;
        newClass->className = className;
        newClass->next = headClass;
        headClass = newClass;
        addStudentToClassFromCsvFile(headClass, stu, className);
    }
    fin.close();
}

void ImportClass(Class* headClass) {
    ofstream fout;
    fout.open("Class/class.txt", ios::trunc);
    if (!fout.is_open()) {
        cout << "Error!" << endl;
    }
    Class* cur_Class = headClass;
    while (cur_Class) {
        fout << cur_Class->className << endl;
        cur_Class = cur_Class->next;
    }
    fout.close();
}

void StaffMember::updateSchoolYear(Semester*& cur_semester) {
    ifstream fin;
    fin.open("User/SchoolYear.txt");
    if (!fin.is_open()) {
        cout << "error!" << endl;
        return;
    }
    int Year, numSem;
    bool flag = false;
    SchoolYear* cur_schoolYear = nullptr;
    while (fin >> Year) {
        SchoolYear* newSchoolYear = new SchoolYear;
        newSchoolYear->yearStart = Year;
        newSchoolYear->yearEnd = Year + 1;
        fin >> numSem;
        for (int i = 0; i < numSem; i++) {
            fin >> newSchoolYear->semester[i].startDay.day;
            fin >> newSchoolYear->semester[i].startDay.month;
            fin >> newSchoolYear->semester[i].startDay.year;
            fin >> newSchoolYear->semester[i].endDay.day;
            fin >> newSchoolYear->semester[i].endDay.month;
            fin >> newSchoolYear->semester[i].endDay.year;
        }
        if (!schoolYear) {
            schoolYear = newSchoolYear;
            cur_schoolYear = schoolYear;
        }
        else
        {
            cur_schoolYear->next = newSchoolYear;
            cur_schoolYear = newSchoolYear;
        }

        if (!flag) {
            cur_semester = &(newSchoolYear->semester[numSem - 1]);
            flag = true;
        }
    }
    fin.close();
}
void StaffMember::importSchoolYear() {
    ofstream fout;
    fout.open("User/SchoolYear.txt", ios::trunc);
    SchoolYear* curSchoolYear;
    if (!fout.is_open()) {
        cout << "error!" << endl;
    }
    curSchoolYear = schoolYear;
    while (curSchoolYear) {
        int n = 0;
        fout << curSchoolYear->yearStart << endl;
        while (curSchoolYear->semester[n].course || n < 3)
            n++;
        fout << n << endl;
        for (int i = 0; i < n; i++) {
            fout << curSchoolYear->semester[i].startDay.day << " ";
            fout << curSchoolYear->semester[i].startDay.month << " ";
            fout << curSchoolYear->semester[i].startDay.year << " ";
            fout << curSchoolYear->semester[i].endDay.day << " ";
            fout << curSchoolYear->semester[i].endDay.month << " ";
            fout << curSchoolYear->semester[i].endDay.year << endl;
        }
        curSchoolYear = curSchoolYear->next;
    }
}
void StaffMember::importCourse()
{
    ofstream fout;
    fout.open("Course/Course.csv", ios::trunc);
    SchoolYear* curSchoolYear = schoolYear;
    bool flag = true;
    while (curSchoolYear)
    {
        for (int i = 0; i < 3; i++)
        {
            Semester curSemester = curSchoolYear->semester[i];
            if (curSemester.course == nullptr) continue;//The condition to check if semester is null or not
            Course* curCourse = curSemester.course;
            while (curCourse)
            {
                if (flag)
                {
                    fout << "SchoolYear,Semester,Course_ID,Course_name,classname,teacherName,numberOfCredits,maxSize,dow,session\n";
                    flag = false;
                }
                fout << curSchoolYear->yearStart << ","
                    << i + 1 << "," // Semester (1-based indexing)
                    << curCourse->Course_ID << ","
                    << curCourse->Course_name << ","
                    << curCourse->classname << ","
                    << curCourse->teacherName << ","
                    << curCourse->numberOfCredits << ","
                    << curCourse->maxSize << ","
                    << curCourse->dow << ","
                    << curCourse->session << endl;

                curCourse = curCourse->next;
            }
        }
        curSchoolYear = curSchoolYear->next;
    }

    fout.close();
}
void StaffMember::updateCourse(User& Head_User) {
    ifstream fin("Course/Course.csv");

    if (!fin.is_open()) {
        cerr << "Error: Could not open course file." << endl;
        return;
    }

    // Skip the header line
    string header;
    getline(fin, header);

    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        vector<string> tokens;

        // Split the line into tokens based on commas
        while (getline(ss, header, ',')) {
            tokens.push_back(header);
        }

        if (tokens.size() != 10) {
            cerr << "Warning: Invalid line format in course file." << endl;
            continue;
        }

        // Extract course information from tokens
        int yearStart = stoi(tokens[0]);
        int semester = stoi(tokens[1]);
        string courseID = tokens[2];
        string courseName = tokens[3];
        string className = tokens[4];
        string teacherName = tokens[5];
        int numberOfCredits = stoi(tokens[6]);
        int maxSize = stoi(tokens[7]);
        string dow = tokens[8];
        int session = stoi(tokens[9]);

        // Find the corresponding semester in SchoolYear
        SchoolYear* currentYear = schoolYear;
        bool foundYear = false;
        while (currentYear) {
            if (currentYear->yearStart == yearStart) {
                foundYear = true;
                break;
            }
            currentYear = currentYear->next;
        }

        if (!foundYear) {
            cerr << "Warning: School year " << yearStart << " not found." << endl;
            continue;
        }

        // Check if semester index is valid (1-based indexing)
        if (semester < 1 || semester > 3) {
            cerr << "Warning: Invalid semester number: " << semester << endl;
            continue;
        }


        // Create a new course node
        Course* newCourse = new Course;
        newCourse->Course_ID = courseID;
        newCourse->Course_name = courseName;
        newCourse->classname = className;
        newCourse->teacherName = teacherName;
        newCourse->numberOfCredits = numberOfCredits;
        newCourse->maxSize = maxSize;
        int index=0;
        while((dow[index]>='A'&&dow[index]<='Z')||(dow[index]>='a'&&dow[index]<='z'))
        {
            newCourse->dow[index]=dow[index];
            index++;
        }
        newCourse->dow[index] = '\0';
        newCourse->session = session;
        newCourse->next = nullptr;

        //Add Student to Course
        newCourse->inputStudent2CourseFromFile(Head_User);

        //Add Score
        importScoreBoard(Head_User.students,nullptr, courseID);

        // Add the course to the linked list of the semester
        if (currentYear->semester[semester - 1].course == nullptr) {
            currentYear->semester[semester - 1].course = newCourse;
        }
        else {
            Course* temp = currentYear->semester[semester - 1].course;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newCourse;
        }
    }

    fin.close();
    cout << "Courses read from file successfully." << endl;
}
