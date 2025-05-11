#pragma once
#include "MyString.h"

class User {
protected:
	int id;
	MyString name;
	MyString surname;
	MyString password;
	MyString email;

public:
	int getId() const;
	MyString getName() const;
	MyString getSurname() const;
	MyString getPassword() const;
	MyString getEmail() const;
};
