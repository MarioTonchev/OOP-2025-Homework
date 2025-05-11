#include <fstream>
#include <iostream>
#include <stdexcept>
#include "Admin.h"

using namespace std;


Admin::Admin(MyString name, MyString surname, MyString email, MyString password, int id)
{
	this->name = name;
	this->surname = surname;
	this->email = email;
	this->password = password;
	this->id = id;
}

void Admin::createTeacher(MyString name, MyString surname, MyString password, MyVector<User*>& users) {
	Teacher* teacher = new Teacher(name, surname, password, users.getSize());
	users.push_back(teacher);

	ofstream os("users.txt", ios::app);

	if (!os.is_open())
	{
		throw invalid_argument("File does not exist!");
	}

	os << "Teacher " << name << " " << surname << " " << password << " " << teacher->getId() << endl;

	os.close();
}

void Admin::createStudent(MyString name, MyString surname, MyString password, MyVector<User*>& users) {
	Student* student = new Student(name, surname, password, users.getSize());
	users.push_back(student);

	ofstream os("users.txt", ios::app);

	if (!os.is_open())
	{
		throw invalid_argument("File does not exist!");
	}

	os << "Student " << name << " " << surname << " " << password << " " << student->getId() << endl;

	os.close();
}

void Admin::loadUsers(MyVector<User*>& users) {
	ifstream is("users.txt");

	MyString buffer;
	while (true)
	{
		if (is.eof())
		{
			break;
		}

		buffer.getline(is);
		MyVector<MyString> tokens = buffer.split(' ');

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
	}

	is.close();
}

void Admin::deleteUser(int id, MyVector<User*>& users) {
	for (size_t i = 0; i < users.getSize(); i++)
	{
		if (users[i]->getId() == id)
		{
			users.remove_at(i);
			break;
		}
	}

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

		if (is.eof())
		{
			break;
		}

		MyVector<MyString> tokens = buffer.split(' ');

		if (tokens[4].toInt() == id)
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