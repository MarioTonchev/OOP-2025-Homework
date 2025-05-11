#pragma once
#include "User.h"
#include "MyString.h"
#include "MyVector.h"

bool login(int id, MyString& password, MyVector<User*>& users, User*& loggedUser);