#pragma once
#include "User.h"
#include "Teacher.h"
#include "Student.h"
#include "MyVector.h"

class Admin : public User {
public:
	Admin(MyString name, MyString surname, MyString email, MyString password = "0000", int id = 0);
	void loadUsers(MyVector<User*>& users);
	void createTeacher(MyString name, MyString surname, MyString password, MyVector<User*>& users);
	void createStudent(MyString name, MyString surname, MyString password, MyVector<User*>& users);
	void deleteUser(int id, MyVector<User*>& users);
	void sendMessage();
	void checkMailbox();
};