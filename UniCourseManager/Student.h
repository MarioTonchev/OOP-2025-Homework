#pragma once
#include "User.h"
#include "MyString.h"
#include "Course.h"

class Student : public User {
public:
	Student(const MyString& name = "", const MyString& surname = "", const MyString& password = "", int id = 0);
	void enroll(const MyString& courseName, const MyString& coursePassword, MyVector<Course*>& courses);
	void finishAssignment(const MyString& courseName, const MyString& assignmentName, const MyString& answer, MyVector<Course*>& courses);
	void checkGrades() const;
};