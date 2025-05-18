//Mario Tonchev Tonchev 0MI0600460
#include <iostream>
#include <ctime>

#include "HelperFunctions.h"

using namespace std;

#pragma warning(disable:4996)

void clearConsole()
{
	cout << "\033[;H";
	cout << "\033[J";
}

void printActions(const MyString& userType) {
	cout << "You are able to use the following commands:" << endl << endl;

	if (userType == "Admin")
	{
		cout << "add_teacher <name> <surname> <password>" << endl;
		cout << "add_student <name> <surname> <password>" << endl;
		cout << "delete_user <id>" << endl;
		cout << "message_all <content>" << endl;
		cout << "mailbox <id>" << endl;
	}
	else if (userType == "Teacher")
	{
		cout << "create_course <course name> <course password>" << endl;
		cout << "add_to_course <course name> <user id>" << endl;
		cout << "assign_homework <course name> <homework name>" << endl;
		cout << "message_students <course name> <content>" << endl;
		cout << "preview_assignment_works <course name> <assignment name>" << endl;
		cout << "grade_assignment <course name> <assignment name> <user id> <grade> <message>" << endl;
	}
	else if (userType == "Student")
	{
		cout << "enroll <course name> <course password>" << endl;
		cout << "finish_assignment <course name> <assignment name> <answer>" << endl;
		cout << "grades" << endl;
	}

	cout << "message <id> <content>" << endl;
	cout << "mailbox" << endl;
	cout << "clear_mailbox" << endl;
	cout << "change_password <current pass> <new pass>" << endl;
	cout << "logout" << endl;
	cout << "quit" << endl;
}

MyString getCurrentDate() {
	time_t t = time(nullptr);
	tm* now = localtime(&t);

	MyString date;
	date += now->tm_mday;
	date += '.';
	date += (now->tm_mon + 1);
	date += '.';
	date += (now->tm_year + 1900);

	return date;
}

MyString getCurrentTime() {
	time_t t = time(nullptr);
	tm* now = localtime(&t);

	MyString time;
	time += now->tm_hour;
	time += ':';

	if (now->tm_min < 10) {
		time += '0';
	}

	time += now->tm_min;

	return time;
}

MyString vectorToString(MyVector<MyString>& vector, int start) {
	MyString result;

	for (size_t i = start; i < vector.getSize(); i++)
	{
		result += vector[i];
		i < vector.getSize() - 1 ? result += " " : result;
	}

	return result;
}

void freeUsers(MyVector<User*>& users) {
	for (size_t i = 0; i < users.getSize(); i++)
	{
		delete users[i];
	}
}

void freeCourses(MyVector<Course*>& courses) {
	for (size_t i = 0; i < courses.getSize(); i++)
	{
		delete courses[i];
	}
}