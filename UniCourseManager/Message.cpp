//Mario Tonchev Tonchev 0MI0600460
#include "Message.h"

Message::Message(int receiverId, const MyString& sender, const MyString& content) {
	this->receiverId = receiverId;
	this->sender = sender;
	this->content = content;
	date = getCurrentDate();
	time = getCurrentTime();
}

Message::Message(int receiverId, const MyString& sender, const MyString& content, const MyString& date, const MyString& time) {
	this->receiverId = receiverId;
	this->sender = sender;
	this->content = content;
	this->date = date;
	this->time = time;
}

int Message::getSenderId() const {
	return receiverId;
}

const MyString& Message::getSender() const {
	return sender;
}

const MyString& Message::getContent() const {
	return content;
}

const MyString& Message::getDate() const {
	return date;
}

const MyString& Message::getTime() const {
	return time;
}