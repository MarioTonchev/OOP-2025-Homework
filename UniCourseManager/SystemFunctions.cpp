#include <iostream>
#include "SystemFunctions.h"
#include "User.h"

using namespace std;

bool login(int id, MyString& password, MyVector<User*>& users, User*& loggedUser) {
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