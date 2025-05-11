#include <iostream>
#include <fstream>
#include "MyString.h"
#include "Admin.h"
#include "Teacher.h"
#include "Student.h"
#include "SystemFunctions.h"

using namespace std;

int main()
{
	/*
	1. Load all different types of users, courses and mails from corresponding files
	2. Log in with id and password
	3. Use system functionalities depending on user type
	4. Save course info and email info to corresponding files
	5. Can log out and login with another account
	*/

	Admin admin("Admin", "Adminov", "admin@adminov");
	MyVector<User*> users;
	users.push_back(&admin);
	admin.loadUsers(users);

	User* user = nullptr;

	cout << "Please login by entering your id and password (separated by space):" << endl;
	MyString command;

	command.getline(cin);

	while (true)
	{
		MyVector<MyString> tokens = command.split(' ');

		if (tokens.getSize() != 2) 
		{
			cout << "Invalid input format. Please enter both ID and password separated by space." << endl;
			command.getline(cin);
			continue;
		}

		bool result = login(tokens[0].toInt(), tokens[1], users, user);

		if (result)
		{
			cout << "You logged in as " << user->getName() << " with ID " << user->getId() << endl;
			break;	
		}
		else
		{
			cout << "Account does not exist! Please try again!" << endl;

			command.getline(cin);
		}
	}

	for (size_t i = 0; i < users.getSize(); i++)
	{
		cout << users[i]->getName() << " " << users[i]->getId() << endl;
	}
}