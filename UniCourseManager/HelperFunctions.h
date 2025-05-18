//Mario Tonchev Tonchev 0MI0600460
#pragma once

#include "MyString.h"
#include "MyVector.hpp"

class User;
class Course;

void clearConsole();

void printActions(const MyString& userType);

MyString getCurrentDate();
MyString getCurrentTime();

MyString vectorToString(MyVector<MyString>& vector, int start = 0);

void freeUsers(MyVector<User*>& users);
void freeCourses(MyVector<Course*>& courses);