//Mario Tonchev Tonchev 0MI0600460
#pragma once

#include "MyString.h"
#include "MyVector.hpp"
#include "Course.h"

Course* findCourse(const MyString& courseName, MyVector<Course*>& courses);

Assignment* findAssignment(const MyString& assignmentName, const MyString& courseName, MyVector<Course*>& courses);