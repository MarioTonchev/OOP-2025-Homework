//Mario Tonchev Tonchev 0MI0600460
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "Admin.h"

using namespace std;

Admin::Admin(const MyString& name, const MyString& surname, const MyString& password, int id)
{
	this->name = name;
	this->surname = surname;
	this->password = password;
	this->id = id;
}

void Admin::createTeacher(const MyString& name, const MyString& surname, const MyString& password, MyVector<User*>& users) {
	int id = 0;

	for (size_t i = 0; i < users.getSize(); i++)
	{
		if (users[i]->getId() > id)
		{
			id = users[i]->getId();
		}
	}

	Teacher* teacher = new Teacher(name, surname, password, ++id);
	users.push_back(teacher);

	ofstream os(usersFile, ios::app);

	if (!os.is_open())
	{
		throw invalid_argument("File does not exist!");
	}

	os << "Teacher|" << name << "|" << surname << "|" << password << "|" << teacher->getId() << endl;

	os.close();
}

void Admin::createStudent(const MyString& name, const MyString& surname, const MyString& password, MyVector<User*>& users) {
	int id = 0;

	for (size_t i = 0; i < users.getSize(); i++)
	{
		if (users[i]->getId() > id)
		{
			id = users[i]->getId();
		}
	}

	Student* student = new Student(name, surname, password, ++id);
	users.push_back(student);

	ofstream os(usersFile, ios::app);

	if (!os.is_open())
	{
		throw invalid_argument("File does not exist!");
	}

	os << "Student|" << name << "|" << surname << "|" << password << "|" << student->getId() << endl;

	os.close();
}

void Admin::deleteUser(int id, MyVector<User*>& users, MyVector<Course*>& courses) {
	if (id == 0)
	{
		cout << "You can't delete yourself..." << endl;
		return;
	}

	User* userToDelete = findUser(id, users);

	if (!userToDelete)
	{
		cout << "User with such ID does not exist!" << endl;
		return;
	}

	for (size_t i = 0; i < users.getSize(); i++)
	{
		if (users[i]->getId() == id)
		{
			users.remove_at(i);
			break;
		}
	}

	for (size_t i = 0; i < courses.getSize(); i++)
	{
		bool isRemoved = false;

		for (size_t j = 0; j < courses[i]->getStudents().getSize(); j++)
		{
			if (courses[i]->getStudents()[j]->getId() == id)
			{
				courses[i]->getStudents().remove_at(j);
				isRemoved = true;
				break;
			}
		}

		if (isRemoved)
		{
			break;
		}
	}

	for (size_t i = 0; i < courses.getSize(); i++)
	{
		bool isRemoved = false;

		for (size_t j = 0; j < courses[i]->getAssignments().getSize(); j++)
		{
			for (size_t k = 0; k < courses[i]->getAssignments()[j].getSubmissions().getSize(); k++)
			{
				if (courses[i]->getAssignments()[j].getSubmissions()[k].getStudentId() == id)
				{
					courses[i]->getAssignments()[j].getSubmissions().remove_at(k);
					isRemoved = true;
					break;
				}
			}

			if (isRemoved)
			{
				break;
			}
		}

		if (isRemoved)
		{
			break;
		}
	}

	updateUsers(users);
	updateAssignments(courses);
	updateMessages(users);
	deleteUserFromEnrollmentFile(id);
}

void Admin::messageAll(const MyString& content, MyVector<User*>& users) {
	MyString sender;
	sender += this->name;
	sender += " ";
	sender += this->surname;

	for (size_t i = 0; i < users.getSize(); i++)
	{
		if (users[i]->getId() == this->id)
		{
			continue;
		}

		Message message(users[i]->getId(), sender, content);

		users[i]->addMessage(message);
	}

	updateMessages(users);
}

void Admin::checkUserMailbox(int id, MyVector<User*>& users) {
	User* user = findUser(id, users);

	if (!user)
	{
		cout << "User with such ID does not exist!" << endl;
		return;
	}

	if (user->getMailbox().getSize() == 0)
	{
		cout << "This user's mailbox is empty." << endl;
		return;
	}

	user->checkMailbox();
}