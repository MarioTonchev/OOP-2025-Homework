//Mario Tonchev Tonchev 0MI0600460
#pragma once

#include "MyString.h"
#include "MyVector.hpp"
#include "Submission.h"

class Assignment {
private:
	MyString name;
	MyVector<Submission> submissions;

public:
	Assignment(const MyString& name = "");
	const MyString& getName() const;
	MyVector<Submission>& getSubmissions();
	void addSubmission(const Submission& submission);
};