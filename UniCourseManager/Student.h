#pragma once
#include "User.h"

class Student : public User {
public:
	Student(MyString name, MyString surname, MyString password, int id);
};