#pragma once
#include "User.h" //may cause circular dependency so be sure to check later
#include <ctime>

class Message {
private:
	User* sender;
	char* content;
	//add date
};