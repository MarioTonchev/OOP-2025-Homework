//Mario Tonchev Tonchev 0MI0600460
#include <iostream>
#include <fstream>

#include "User.h"
#include "UserUtils.h"
#include "IOManager.h"

using namespace std;

User::~User() {}

int User::getId() const {
	return id;
}

const MyString& User::getName() const {
	return name;
}

const MyString& User::getSurname() const {
	return surname;
}

const MyString& User::getPassword() const {
	return password;
}

const MyVector<Message>& User::getMailbox() const {
	return mailbox;
}

const MyVector<Course*>& User::getCourses() const {
	return courses;
}

void User::addMessage(const Message& message) {
	mailbox.push_back(message);
}

void User::addCourse(Course* course) {
	courses.push_back(course);
}

void User::changePassword(const MyString& currentPass, const MyString& newPass) {
	if (currentPass == "" || newPass == "")
	{
		cout << "Current password and new password cannot be empty!" << endl;
		return;
	}

	if (currentPass != password)
	{
		cout << "Your current password does not match!" << endl;
		return;
	}
	
	password = newPass;

	cout << "Password successfully changed!" << endl;
}

void User::checkMailbox() const {
	if (mailbox.getSize() == 0)
	{
		cout << "Your mailbox is empty!" << endl;
		return;
	}
	
	for (size_t i = 0; i < mailbox.getSize(); i++)
	{
		cout << mailbox[i].getTime() << " " << mailbox[i].getDate() << ", sent by " << mailbox[i].getSender()
			<< ": " << mailbox[i].getContent() << endl;
	}
}

void User::message(int id, const MyString& content, MyVector<User*>& users) const {
	if (content == "")
	{
		cout << "Content cannot be empty!" << endl;
		return;
	}

	if (id == this->id)
	{
		cout << "You cannot message yourself!" << endl;
		return;
	}

	MyString sender;
	sender += this->name;
	sender += " ";
	sender += this->surname;

	Message message(id, sender, content);

	User* user = findUser(id, users);

	if (!user)
	{
		cout << "User with such ID does not exist!" << endl;
		return;
	}

	user->addMessage(message);
	updateMessages(users);

	cout << "Message successfully sent!" << endl;
}

void User::clearMailbox() {
	while (mailbox.getSize() > 0)
	{
		mailbox.pop_back();
	}

	cout << "Mailbox successfully cleared!" << endl;
}