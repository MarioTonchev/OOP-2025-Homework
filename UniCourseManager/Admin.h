//Mario Tonchev Tonchev 0MI0600460
#pragma once

#include "User.h"
#include "Teacher.h"
#include "Student.h"
#include "MyString.h"
#include "MyVector.hpp"
#include "UserUtils.h"
#include "IOManager.h"
#include "FileConstants.h"


class Admin : public User {
public:
	Admin(const MyString& name, const MyString& surname, const MyString& password = "0000", int id = 0);
	void createTeacher(const MyString& name, const MyString& surname, const MyString& password, MyVector<User*>& users);
	void createStudent(const MyString& name, const MyString& surname, const MyString& password, MyVector<User*>& users);
	void deleteUser(int id, MyVector<User*>& users);
	void messageAll(const MyString& content, MyVector<User*>& users);
	void checkUserMailbox(int id, MyVector<User*>& users);
};