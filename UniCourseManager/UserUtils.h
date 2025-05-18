//Mario Tonchev Tonchev 0MI0600460
#pragma once

#include "MyString.h"
#include "MyVector.hpp"

class User;

User* findUser(int id, MyVector<User*>& users);
const MyString getUserType(User*& user);
bool setCurrentUser(int id, const MyString& password, MyVector<User*>& users, User*& loggedUser);
void login(MyString& command, MyVector<User*>& users, User*& loggedUser, MyString& userType);