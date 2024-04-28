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
            cur_schoolYear->next = newSchoolYear;
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
