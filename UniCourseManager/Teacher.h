#pragma once
#include "User.h"

class Teacher : public User {
public:
	Teacher(MyString name, MyString surname, MyString password, int id);
};