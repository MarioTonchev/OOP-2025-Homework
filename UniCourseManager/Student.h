//Mario Tonchev Tonchev 0MI0600460
#pragma once

#include "User.h"
#include "MyVector.hpp"
#include "MyString.h"
#include "Course.h"
#include "CourseUtils.h"
#include "Assignment.h"
#include "IOManager.h"
#include "Submission.h"
#include "FileConstants.h"

class Student : public User {
public:
	Student(const MyString& name = "", const MyString& surname = "", const MyString& password = "", int id = 0);
	void enroll(const MyString& courseName, const MyString& coursePassword, MyVector<Course*>& courses);
	void finishAssignment(const MyString& courseName, const MyString& assignmentName, const MyString& answer, MyVector<Course*>& courses);
	void checkGrades() const;
};