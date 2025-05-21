//Mario Tonchev Tonchev 0MI0600460
#include "Course.h"

Course::Course(const MyString& name, const MyString& password, int teacherId) {
	this->name = name;
	this->password = password;
	this->teacherId = teacherId;
}

const MyString& Course::getPassword() const {
	return password;
}

const MyString& Course::getName() const {
	return name;
}

int Course::getTeacherId() const {
	return teacherId;
}

MyVector<Assignment>& Course::getAssignments() {
	return assignments;
}

MyVector<User*>& Course::getStudents() {
	return students;
}

void Course::addAssignment(const Assignment& assignment) {
	assignments.push_back(assignment);
}

void Course::addStudent(const User* student) {
	students.push_back((User*)student);
}