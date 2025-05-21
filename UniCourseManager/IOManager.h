//Mario Tonchev Tonchev 0MI0600460
#pragma once

#include "MyString.h"
#include "User.h"
#include "Student.h"
#include "Admin.h"
#include "Teacher.h"
#include "Message.h"
#include "CourseUtils.h"
#include "UserUtils.h"
#include "MyVector.hpp"
#include "FileConstants.h"

void loadUsers(MyVector<User*>& users);
void loadMessages(MyVector<User*>& users);
void loadCourses(MyVector<Course*>& courses);
void loadEnrollments(MyVector<User*>& users, MyVector<Course*>& courses);
void loadTeacherCourses(MyVector<User*>& users, MyVector<Course*>& courses);
void loadAssignments(MyVector<Course*>& courses);

void updateUsers(MyVector<User*>& users);
void updateMessages(MyVector<User*>& users);
void updateCourses(MyVector<Course*>& courses);
void updateAssignments(MyVector<Course*>& courses);

void deleteUserFromFile(int userId);
void deleteMessageFromFile(int userId);
void deleteUserFromEnrollmentFile(int userId);