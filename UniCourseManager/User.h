//Mario Tonchev Tonchev 0MI0600460
#pragma once

#include "MyString.h"
#include "MyVector.hpp"
#include "Message.h"

class Course;
class Student;

class User {
protected:
	int id;
	MyString name;
	MyString surname;
	MyString password;
	MyVector<Message> mailbox;
	MyVector<Course*> courses;

public:
	virtual ~User();
	int getId() const;
	const MyString& getName() const;
	const MyString& getSurname() const;
	const MyString& getPassword() const;
	const MyVector<Message>& getMailbox() const;
	const MyVector<Course*>& getCourses() const;
	void addMessage(const Message& message);
	void addCourse(const Course* course);

	void changePassword(const MyString& currentPass, const MyString& newPass);

	void checkMailbox() const;
	void message(int id, const MyString& content, MyVector<User*>& users) const;
	void clearMailbox();
};
