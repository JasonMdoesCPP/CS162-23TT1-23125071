#include"Struct.h"
int main()
{
	User *Head_User = new User;
	Class* Head_Class = nullptr;
	if (Head_User->user1) cout << "Sth wrong in user 1";
	Head_User->addInformationStaffMembers();
	Head_User->addInformationStudent();
	Head_User->login();
	if (Head_User->user1)
	{

	}
	if (Head_User->user2)
	{

		int choice = 0;
		while (choice != 6)
		{
			cout << "Enter choices:";
			cout << " 1.Create school year." << endl;
			cout << "2.Create several Classes." << endl;
			cin >> choice;
			switch (choice)
			{
			case 1:
				Head_User->user2->createSchoolYear();
				break;

			case 2:
				createSeveralClasses(Head_Class);
				break;
			}
		}
		cout << "fin";
	}
}
