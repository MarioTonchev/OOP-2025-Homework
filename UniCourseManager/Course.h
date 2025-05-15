#pragma once
#include "MyVector.h"
#include "MyString.h"
#include "Assignment.h"
#include "User.h"

class Teacher;

class Course {
private:
	MyString name;
	MyString password;
	int teacherId;

	MyVector<User*> students;
	MyVector<Assignment> assignments;

public:
	Course(const MyString& name = "", const MyString& password = "", int teacherId = 0);
	const MyString& getName() const;
	const MyString& getPassword() const;
	int getTeacherId() const;
	MyVector<Assignment>& getAssignments();
	const MyVector<User*>& getStudents() const;
	void addAssignment(const Assignment& assignment);
	void addStudent(const User* student);
};