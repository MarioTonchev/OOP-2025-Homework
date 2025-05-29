//Mario Tonchev Tonchev 0MI0600460
#include <iostream>
#include <fstream>

#include "Student.h"

using namespace std;

Student::Student(const MyString& name, const MyString& surname, const MyString& password, int id) {
	this->name = name;
	this->surname = surname;
	this->password = password;
	this->id = id;
}

void Student::enroll(const MyString& courseName, const MyString& coursePassword, MyVector<Course*>& courses) {
	if (courseName == "" || coursePassword == "")
	{
		cout << "Course name and password cannot be empty!" << endl;
		return;
	}

	Course* course = findCourse(courseName, courses);

	if (!course)
	{
		cout << "Course with such name does not exist!" << endl;
		return;
	}

	for (size_t i = 0; i < this->courses.getSize(); i++)
	{
		if (this->courses[i]->getName() == courseName)
		{
			cout << "You are already enrolled in this course!" << endl;
			return;
		}
	}

	if (course->getPassword() != coursePassword)
	{
		cout << "Wrong course password entered!" << endl;
		return;
	}

	course->addStudent(this);
	this->addCourse(course);
	
	ofstream os(enrollmentsFile, ios::app);

	if (!os.is_open())
	{
		throw invalid_argument("Files does not exist!");
	}

	os << id << "|" << courseName << endl;

	os.close();

	cout << "Successfully enrolled!" << endl;
}

void Student::finishAssignment(const MyString& courseName, const MyString& assignmentName, const MyString& answer, MyVector<Course*>& courses) {
	if (courseName == "" || assignmentName == "" || answer == "")
	{
		cout << "Course name, assignment name and answer cannot be empty!" << endl;
		return;
	}
	
	Course* course = findCourse(courseName, this->courses);
	Assignment* assignment = findAssignment(assignmentName, courseName, this->courses);

	if (!course)
	{
		cout << "You are not enrolled in a course with such name!" << endl;
		return;
	}

	if (!assignment)
	{
		cout << "Course does not have an assignment with such name!" << endl;
		return;
	}

	for (size_t i = 0; i < assignment->getSubmissions().getSize(); i++)
	{
		if (assignment->getSubmissions()[i].getStudentId() == this->id)
		{
			cout << "You have already turned a submission in for this assignment!" << endl;
			return;
		}
	}

	Submission submission(this->id, answer);
	assignment->addSubmission(submission);

	updateAssignments(courses);

	cout << "Assignment successfully finished!" << endl;
}

void Student::checkGrades() const {
	for (size_t i = 0; i < courses.getSize(); i++)
	{
		for (size_t j = 0; j < courses[i]->getAssignments().getSize(); j++)
		{
			for (size_t k = 0; k < courses[i]->getAssignments()[j].getSubmissions().getSize(); k++)
			{
				if (courses[i]->getAssignments()[j].getSubmissions()[k].getStudentId() == id)
				{
					double grade = courses[i]->getAssignments()[j].getSubmissions()[k].getGrade();
					MyString comment = courses[i]->getAssignments()[j].getSubmissions()[k].getTeacherComment();

					cout << courses[i]->getName() << " | " << courses[i]->getAssignments()[j].getName()
						<< " | ";

					if (grade == 0)
					{
						cout << "No grade yet" << " | ";
					}
					else
					{
						cout << grade << " | ";
					}

					if (comment == "nocomment")
					{
						cout << "No teacher comment yet" << endl;
					}
					else
					{
						cout << comment << endl;
					}
				}
			}
		}
	}
}