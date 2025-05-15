#include "Assignment.h"

Assignment::Assignment(const MyString& name) {
	this->name = name;
}

const MyString& Assignment::getName() const {
	return name;
}

MyVector<Submission>& Assignment::getSubmissions() {
	return submissions;
}

void Assignment::addSubmission(const Submission& answer) {
	submissions.push_back(answer);
}