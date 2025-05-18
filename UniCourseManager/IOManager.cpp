//Mario Tonchev Tonchev 0MI0600460
#include <iostream>
#include <fstream>

#include "IOManager.h"

using namespace std;

#pragma warning(disable:4996)

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