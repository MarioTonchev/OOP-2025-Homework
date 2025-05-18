//Mario Tonchev Tonchev 0MI0600460
#pragma once

#include "MyString.h"
#include "MyVector.hpp"
#include "Assignment.h"

class User;
class Teacher;
class Student;

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