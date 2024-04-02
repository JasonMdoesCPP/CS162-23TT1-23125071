#include"Struct.h"
using namespace std;
int main()
{
    User user;
    Class *HeadClass = nullptr;
    user.addInformationStudent();
    user.addInformationStaffMembers();
    user.login();
    if(user.user1){
        Student* stu = user.user1;
    }
    if(user.user2){
        StaffMember * staf = user.user2;
        cout << "1. Create a school year " << endl;
        cout << "2. Create several classes for 1st-year students" << endl;
        cout << "3. Add new 1st year students to 1st-year classes." << endl;
        cout << "4. Adding student to class from csv file" << endl;
        cout << "0. Ending program!" << endl;
        int ca;
        cin >> ca;
        while(ca){
            if(ca == 1){
                staf->createSchoolYear();
            }else if(ca == 2){
                createSeveralClasses(HeadClass);
            }else if(ca == 3){
                addStudentToClass(HeadClass, user.students);
            }else if(ca == 4){
                addStudentToClassFromCsvFile(HeadClass, user.students); 
            }else
                cout << "Enter wrong number!"  << endl;
            
            cout << "1. Create a school year (2020-2021, for example)" << endl;
            cout << "2. Create several classes for 1st-year students" << endl;
            cout << "3. Add new 1st year students to 1st-year classes." << endl;
            cout << "4. Adding student to class from csv file" << endl;
            cout << "0. Ending program!" << endl;
            cin >> ca;
        }
    }
    user.deleteUser();
    deleteClass(HeadClass);
    
}
