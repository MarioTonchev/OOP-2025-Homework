#pragma once
#include "MyString.h"
#include "MyVector.h"
#include "Message.h"
#include "Assignment.h"

class User;
class Course;

void clearConsole();

User* findUser(int id, MyVector<User*>& users);
Course* findCourse(const MyString& courseName, MyVector<Course*>& courses);
Assignment* findAssignment(const MyString& assignmentName, const MyString& courseName, MyVector<Course*>& courses);
const MyString getUserType(User*& user);

bool setCurrentUser(int id, const MyString& password, MyVector<User*>& users, User*& loggedUser);
void login(MyString& command, MyVector<User*>& users, User*& loggedUser, MyString& userType);
void printActions(const MyString& userType);

MyString getCurrentDate();
MyString getCurrentTime();

MyString vectorToString(MyVector<MyString>& vector, int start = 0);

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