#include <iostream>
#include <fstream>
#include <ctime>
#include "SystemFunctions.h"
#include "MyString.h"
#include "MyVector.h"
#include "Teacher.h"
#include "Student.h"
#include "Admin.h"

using namespace std;

#pragma warning(disable:4996)

void clearConsole()
{
	cout << "\033[;H";
	cout << "\033[J";
}

User* findUser(int id, MyVector<User*>& users) {
	User* user = nullptr;

	for (size_t i = 0; i < users.getSize(); i++)
	{
		if (users[i]->getId() == id)
		{
			user = users[i];
			break;
		}
	}

	return user;
}

Course* findCourse(const MyString& courseName, MyVector<Course*>& courses) {
	Course* course = nullptr;

	for (size_t i = 0; i < courses.getSize(); i++)
	{
		if (courses[i]->getName() == courseName)
		{
			course = courses[i];
			break;
		}
	}

	return course;
}

Assignment* findAssignment(const MyString& assignmentName, const MyString& courseName, MyVector<Course*>& courses) {
	Course* course = findCourse(courseName, courses);

	if (!course)
	{
		cout << "Course with such name does not exist!" << endl;
		return nullptr;
	}

	Assignment* assignment = nullptr;

	for (size_t i = 0; i < course->getAssignments().getSize(); i++)
	{
		if (course->getAssignments()[i].getName() == assignmentName)
		{
			assignment = (Assignment*)&course->getAssignments()[i];
			break;
		}
	}

	return assignment;
}

const MyString getUserType(User*& user) {
	MyString classType = typeid(*user).name();
	MyString userType = classType.split(' ')[1];

	return userType;
}

void loadUsers(MyVector<User*>& users) {
	ifstream is("users.txt");

	if (!is.is_open())
	{
		throw invalid_argument("File does not exist");
	}

	MyString buffer;
	while (true)
	{
		buffer.getline(is);
		MyVector<MyString> tokens = buffer.split('|');

		if (is.eof())
		{
			break;
		}

		if (tokens[0] == "Teacher")
		{
			Teacher* teacher = new Teacher(tokens[1], tokens[2], tokens[3], tokens[4].toInt());
			users.push_back(teacher);
		}
		else if (tokens[0] == "Student")
		{
			Student* student = new Student(tokens[1], tokens[2], tokens[3], tokens[4].toInt());
			users.push_back(student);
		}
		else if (tokens[0] == "Admin")
		{
			Admin* admin = new Admin(tokens[1], tokens[2], tokens[3], tokens[4].toInt());
			users.push_back(admin);
		}
	}

	is.close();
}

void loadMessages(MyVector<User*>& users) {
	ifstream is("messages.txt");

	if (!is.is_open())
	{
		throw invalid_argument("File does not exist");
	}

	MyString buffer;

	while (true)
	{
		buffer.getline(is);
		MyVector<MyString> tokens = buffer.split('|');

		if (is.eof())
		{
			break;
		}

		int recieverId = tokens[0].toInt();
		Message message(recieverId, tokens[1], tokens[2], tokens[3], tokens[4]);

		for (size_t i = 0; i < users.getSize(); i++)
		{
			if (users[i]->getId() == recieverId)
			{
				users[i]->addMessage(message);
				break;
			}
		}
	}

	is.close();
}

void loadCourses(MyVector<Course*>& courses) {
	ifstream is("courses.txt");

	if (!is.is_open())
	{
		throw invalid_argument("File does not exist!");
	}

	MyString buffer;
	while (true)
	{
		buffer.getline(is);
		MyVector<MyString> tokens = buffer.split('|');

		if (is.eof())
		{
			break;
		}	

		Course* course = new Course(tokens[0], tokens[1], tokens[2].toInt());

		courses.push_back(course);
	}

	is.close();
}

void loadEnrollments(MyVector<User*>& users, MyVector<Course*>& courses) {
	ifstream is("enrollments.txt");

	if (!is.is_open())
	{
		throw invalid_argument("File does not exist!");
	}

	MyString buffer;
	while (true)
	{
		buffer.getline(is);
		MyVector<MyString> tokens = buffer.split('|');

		if (is.eof())
		{
			break;
		}

		int userId = tokens[0].toInt();
		MyString courseName = tokens[1];

		User* user = findUser(userId, users);
		Course* course = findCourse(courseName, courses);

		user->addCourse(course);
		course->addStudent(user);
	}

	is.close();
}

void loadTeacherCourses(MyVector<User*>& users, MyVector<Course*>& courses) {
	for (size_t i = 0; i < courses.getSize(); i++)
	{
		User* teacher = findUser(courses[i]->getTeacherId(), users);

		teacher->addCourse(courses[i]);
	}
}

void loadAssignments(MyVector<Course*>& courses) {
	ifstream is("assignments.txt");

	if (!is.is_open())
	{
		throw invalid_argument("File does not exist!");
	}

	MyString buffer;
	while (true)
	{
		buffer.getline(is);
		MyVector<MyString> tokens = buffer.split('|');

		if (is.eof())
		{
			break;
		}

		Course* course = findCourse(tokens[0], courses);
		
		Assignment assignment(tokens[1]);
		
		for (size_t i = 2; i < tokens.getSize(); i++)
		{
			MyVector<MyString> submissionTokens = tokens[i].split(',');

			if (submissionTokens[1].toDouble() == 0 || submissionTokens[3] == "nocomment")
			{
				Submission submission(submissionTokens[0].toInt(), submissionTokens[2]);

				assignment.addSubmission(submission);
			}
			else
			{
				Submission submission(submissionTokens[0].toInt(), submissionTokens[1].toDouble(), submissionTokens[2], submissionTokens[3]);

				assignment.addSubmission(submission);
			}
			
		}

		course->addAssignment(assignment);
	}

	is.close();
}

bool setCurrentUser(int id, const MyString& password, MyVector<User*>& users, User*& loggedUser) {
	for (size_t i = 0; i < users.getSize(); i++)
	{
		if (users[i]->getId() == id && users[i]->getPassword() == password)
		{
			loggedUser = users[i];
			return true;
		}
	}

	return false;
}

void login(MyString& command, MyVector<User*>& users, User*& loggedUser, MyString& userType) {
	cout << "Please login by entering your id and password (separated by space):" << endl;

	command.getline(cin);

	while (true)
	{
		MyVector<MyString> tokens = command.split(' ');

		if (tokens.getSize() != 2)
		{
			cout << "Invalid input format. Please enter both ID and password separated by space." << endl;
			command.getline(cin);
			continue;
		}

		bool result = setCurrentUser(tokens[0].toInt(), tokens[1], users, loggedUser);

		if (result)
		{
			userType = getUserType(loggedUser);

			clearConsole();

			cout << "You logged in as " << (userType == "Admin" ? "an " : "a ") << userType << "." << endl << endl << "Name: "
			<< loggedUser->getName() << endl << "ID: " << loggedUser->getId() << endl << endl;

			printActions(userType);
			cout << endl;

			break;
		}
		else
		{
			cout << "Account does not exist! Please try again!" << endl;

			command.getline(cin);
		}
	}
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

void deleteUserFromFile(int userId) {
	ifstream is("users.txt");

	if (!is.is_open())
	{
		throw invalid_argument("Files does not exist!");
	}

	ofstream os("temp.txt");

	MyString buffer;
	while (true)
	{
		buffer.getline(is);
		MyVector<MyString> tokens = buffer.split('|');


		if (is.eof())
		{
			break;
		}

		if (tokens[4].toInt() == userId)
		{
			continue;
		}
		else
		{
			os << buffer << endl;
		}
	}

	is.close();
	os.close();

	remove("users.txt");
	rename("temp.txt", "users.txt");
}

void deleteMessageFromFile(int userId) {
	ifstream is("messages.txt");

	if (!is.is_open())
	{
		throw invalid_argument("File does not exist");
	}

	ofstream os("temp.txt");

	MyString buffer;
	while (true)
	{
		buffer.getline(is);

		if (is.eof())
		{
			break;
		}

		MyVector<MyString> tokens = buffer.split('|');

		if (tokens[0].toInt() == userId)
		{
			continue;
		}
		else
		{
			os << buffer << endl;
		}
	}

	is.close();
	os.close();

	remove("messages.txt");
	rename("temp.txt", "messages.txt");
}

void updateUsers(MyVector<User*>& users) {
	ofstream os("users.txt");

	if (!os.is_open())
	{
		throw invalid_argument("File does not exist");
	}

	for (size_t i = 0; i < users.getSize(); i++)
	{
		MyString classType = typeid(*users[i]).name();
		MyString userType = classType.split(' ')[1];

		os << userType << "|" << users[i]->getName() << "|" << users[i]->getSurname()
			<< "|" << users[i]->getPassword() << "|" << users[i]->getId() << endl;
	}

	os.close();
}

void updateMessages(MyVector<User*>& users) {
	ofstream os("messages.txt");

	if (!os.is_open())
	{
		throw invalid_argument("File does not exist");
	}

	for (size_t i = 0; i < users.getSize(); i++)
	{
		for (size_t j = 0; j < users[i]->getMailbox().getSize(); j++)
		{
			os << users[i]->getMailbox()[j].getSenderId() << "|" << users[i]->getMailbox()[j].getSender() 
				<< "|" << users[i]->getMailbox()[j].getContent()
				<< "|" << users[i]->getMailbox()[j].getDate() << "|" << users[i]->getMailbox()[j].getTime() << endl;
		}		
	}

	os.close();
}

void updateCourses(MyVector<Course*>& courses) {
	ofstream os("courses.txt");

	if (!os.is_open())
	{
		throw invalid_argument("File does not exist!");
	}

	for (size_t i = 0; i < courses.getSize(); i++)
	{
		os << courses[i]->getName() << "|" << courses[i]->getPassword() << "|" << courses[i]->getTeacherId() << "|";

		for (size_t j = 0; j < courses[i]->getAssignments().getSize(); j++)
		{
			os << courses[i]->getAssignments()[j].getName() << " ";
		}

		os << endl;
	}

	os.close();
}

void updateAssignments(MyVector<Course*>& courses) {
	ofstream os("assignments.txt");

	if (!os.is_open())
	{
		throw invalid_argument("File does not exist!");
	}

	for (size_t i = 0; i < courses.getSize(); i++)
	{
		MyVector<Assignment> assignments = courses[i]->getAssignments();

		for (size_t j = 0; j < assignments.getSize(); j++)
		{
			os << courses[i]->getName() << "|" << assignments[j].getName();

			for (size_t k = 0; k < assignments[j].getSubmissions().getSize(); k++)
			{
				os << "|";

				if (i < assignments[j].getSubmissions().getSize() - 1)
				{
					os << assignments[j].getSubmissions()[k].getStudentId() << "," << assignments[j].getSubmissions()[k].getGrade()
						<< "," << assignments[j].getSubmissions()[k].getAnswer()
						<< "," << assignments[j].getSubmissions()[k].getTeacherComment() << "|";
				}
				else
				{
					os << assignments[j].getSubmissions()[k].getStudentId() << "," << assignments[j].getSubmissions()[k].getGrade()
						<< "," << assignments[j].getSubmissions()[k].getAnswer()
						<< "," << assignments[j].getSubmissions()[k].getTeacherComment();
				}
			}

			os << endl;
		}
	}

	os.close();
}