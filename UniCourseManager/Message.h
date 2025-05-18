//Mario Tonchev Tonchev 0MI0600460
#pragma once

#include <ctime>

#include "MyString.h"
#include "HelperFunctions.h"

class Message {
private:
	int receiverId;
	MyString sender;
	MyString content;
	MyString date;
	MyString time;

public:
	Message(int receiverId = 0, const MyString& sender = "", const MyString& content = "");
	Message(int receiverId, const MyString& sender, const MyString& content, const MyString& date, const MyString& time);

	int getSenderId() const;
	const MyString& getSender() const;
	const MyString& getContent() const;
	const MyString& getDate() const;
	const MyString& getTime() const;
};