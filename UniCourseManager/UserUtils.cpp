//Mario Tonchev Tonchev 0MI0600460
#include <iostream>

#include "UserUtils.h"
#include "User.h"

using namespace std;

User* findUser(int id, MyVector<User*>& users) {
	User* user = nullptr;

	for (size_t i = 0; i < users.getSize(); i++)
	{
		if (users[i]->getId() == id)
		{
			user = users[i];
			break;
		}
	}

	return user;
}

const MyString getUserType(User*& user) {
	MyString classType = typeid(*user).name();
	MyString userType = classType.split(' ')[1];

	return userType;
}

bool setCurrentUser(int id, const MyString& password, MyVector<User*>& users, User*& loggedUser) {
	for (size_t i = 0; i < users.getSize(); i++)
	{
		if (users[i]->getId() == id && users[i]->getPassword() == password)
		{
			loggedUser = users[i];
			return true;
		}
	}

	return false;
}

void login(MyString& command, MyVector<User*>& users, User*& loggedUser, MyString& userType) {
	cout << "Please login by entering your id and password (separated by space):" << endl;

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

		bool result = setCurrentUser(tokens[0].toInt(), tokens[1], users, loggedUser);

		if (result)
		{
			userType = getUserType(loggedUser);

			clearConsole();

			cout << "You logged in as " << (userType == "Admin" ? "an " : "a ") << userType << "." << endl << endl << "Name: "
				<< loggedUser->getName() << endl << "ID: " << loggedUser->getId() << endl << endl;

			printActions(userType);
			cout << endl;

			break;
		}
		else
		{
			cout << "Account does not exist! Please try again!" << endl;

			command.getline(cin);
		}
	}
}