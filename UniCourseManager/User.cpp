#include "User.h"

int User::getId() const {
	return id;
}

MyString User::getName() const {
	return name;
}

MyString User::getSurname() const {
	return surname;
}

MyString User::getPassword() const {
	return password;
}

MyString User::getEmail() const {
	return email;
}