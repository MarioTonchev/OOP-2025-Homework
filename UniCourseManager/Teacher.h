//Mario Tonchev Tonchev 0MI0600460
#pragma once

#include "User.h"
#include "MyVector.hpp"
#include "MyString.h"
#include "UserUtils.h"
#include "CourseUtils.h"
#include "IOManager.h"
#include "Assignment.h"
#include "Course.h"
#include "FileConstants.h"

class Teacher : public User {
public:
	Teacher(const MyString& name = "", const MyString& surname = "", const MyString& password = "", int id = 0);
	void createCourse(const MyString& courseName, const MyString& coursePassword, MyVector<Course*>& courses);
	void addToCourse(const MyString& courseName, int userId, MyVector<User*>& users, MyVector<Course*>& courses);
	void createAssignment(const MyString& courseName, const MyString& assignmentName, MyVector<Course*>& courses);
	void previewAssignmentWork(const MyString& courseName, const MyString& assignmentName, MyVector<Course*>& courses, MyVector<User*>& users);
	void gradeStudent(const MyString& courseName, const MyString& assignmentName, int userId, double grade, const MyString& message, MyVector<Course*>& courses);
	void messageStudents(const MyString& courseName, const MyString& content, MyVector<User*>& users);
};