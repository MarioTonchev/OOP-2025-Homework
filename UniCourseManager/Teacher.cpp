//Mario Tonchev Tonchev 0MI0600460
#include <iostream>
#include <fstream>
#include <stdexcept>

#include "Teacher.h"

using namespace std;

Teacher::Teacher(const MyString& name, const MyString& surname, const MyString& password, int id) {
	this->name = name;
	this->surname = surname;
	this->password = password;
	this->id = id;
}

void Teacher::createCourse(const MyString& courseName, const MyString& coursePassword, MyVector<Course*>& courses) {
	if (courseName == "" || coursePassword == "")
	{
		cout << "Course name and password cannot be empty!" << endl;
		return;
	}
	
	if (findCourse(courseName, courses))
	{
		cout << "Course with such name already exists!" << endl;
		return;
	}

	Course* course = new Course(courseName, coursePassword, id);

	courses.push_back(course);

	ofstream os(coursesFile, ios::app);

	if (!os.is_open())	
	{
		throw invalid_argument("File does not exist!");
	}
	
	os << course->getName() << "|" << course->getPassword() << "|" << id << endl;

	os.close();

	cout << "Course successfully created!" << endl;
}

void Teacher::addToCourse(const MyString& courseName, int userId, MyVector<User*>& users, MyVector<Course*>& courses) {
	if (courseName == "")
	{
		cout << "Course name cannot be empty!" << endl;
		return;
	}
	
	if (userId == 0)
	{
		cout << "You cannot add the admin!" << endl;
		return;
	}

	if (userId == id)
	{
		cout << "You cannot add yourself to the course!" << endl;
		return;
	}

	User* userToAdd = findUser(userId, users);
	Course* course = findCourse(courseName, courses);

	MyString userType = getUserType(userToAdd);

	if (userType == "Teacher")
	{
		cout << "You can't add another teacher to your course!" << endl;
		return;
	}

	if (!userToAdd)
	{
		cout << "User with such id does not exist!" << endl;
		return;
	}

	if (!course)
	{
		cout << "Course with such name does not exist!" << endl;
		return;
	}

	if (course->getTeacherId() != id)
	{
		cout << "You don't have access to this course!" << endl;
		return;
	}

	for (size_t i = 0; i < course->getStudents().getSize(); i++)
	{
		if (course->getStudents()[i]->getId() == userId)
		{
			cout << "Student has already been enrolled in this course!" << endl;
			return;
		}
	}
	
	userToAdd->addCourse(course);
	course->addStudent(userToAdd);

	ofstream os(enrollmentsFile, ios::app);

	if (!os.is_open())
	{
		throw invalid_argument("Files does not exist!");
	}

	os << userId << "|" << courseName << endl;

	os.close();

	cout << "Student successfully enrolled to course!" << endl;
}

void Teacher::createAssignment(const MyString& courseName, const MyString& assignmentName, MyVector<Course*>& courses) {
	if (courseName == "" || assignmentName == "")
	{
		cout << "Course name and assignment name cannot be empty!" << endl;
		return;
	}
	
	Course* course = findCourse(courseName, courses);

	if (!course)
	{
		cout << "Course with such name does not exist!" << endl;
		return;
	}

	if (course->getTeacherId() != id)
	{
		cout << "You don't have access to this course!" << endl;
		return;
	}

	Assignment* foundAssignment = findAssignment(assignmentName, courseName, courses);

	if (foundAssignment)
	{
		cout << "Assignment with such name already exist!" << endl;
		return;
	}

	Assignment assignment(assignmentName);
	course->addAssignment(assignment);
	updateCourses(courses);

	ofstream os(assignmentsFile, ios::app);

	if (!os.is_open())
	{
		throw invalid_argument("File does not exist!");
	}

	os << courseName << "|" << assignment.getName() << endl;

	os.close();

	cout << "Assignment successfully created!" << endl;
}

void Teacher::previewAssignmentWork(const MyString& courseName, const MyString& assignmentName, MyVector<Course*>& courses, MyVector<User*>& users) {
	if (courseName == "" || assignmentName == "")
	{
		cout << "Course name and assignment name cannot be empty!" << endl;
		return;
	}
	
	Course* course = findCourse(courseName, courses);

	if (!course)
	{
		cout << "Course with such name does not exist!" << endl;
		return;
	}

	if (course->getTeacherId() != id)
	{
		cout << "You don't have access to this course!" << endl;
		return;
	}

	bool assignmentExists = false;

	for (size_t i = 0; i < course->getAssignments().getSize(); i++)
	{
		if (course->getAssignments()[i].getName() == assignmentName)
		{
			assignmentExists = true;

			if (course->getAssignments()[i].getSubmissions().getSize() == 0)
			{
				cout << "Assignment does not have any submissions yet!" << endl;
				return;
			}

			for (size_t j = 0; j < course->getAssignments()[i].getSubmissions().getSize(); j++)
			{
				Submission currentSubmission = course->getAssignments()[i].getSubmissions()[j];
				User* user = findUser(currentSubmission.getStudentId(), users);
				cout << user->getName() << " " << user->getSurname() << ", " << user->getId() << ": "
					<< currentSubmission.getAnswer() << endl;
			}

			break;
		}
	}

	if (!assignmentExists)
	{
		cout << "Assignment with such name in this course does not exist!" << endl;
	}
}

void Teacher::gradeStudent(const MyString& courseName, const MyString& assignmentName, int userId, double grade, const MyString& teacherComment, MyVector<Course*>& courses) {
	if (courseName == "" || assignmentName == "" || teacherComment == "")
	{
		cout << "Course name, assignment name and teacher comment cannot be empty!" << endl;
		return;
	}
	
	Course* course = findCourse(courseName, courses);
	Assignment* assignment = findAssignment(assignmentName, courseName, courses);

	if (!course)
	{
		cout << "Course with such name does not exist!" << endl;
		return;
	}

	if (course->getTeacherId() != id)
	{
		cout << "You don't have access to this course!" << endl;
		return;
	}

	if (!assignment)
	{
		cout << "Assignment with such name does not exist!" << endl;
		return;
	}

	for (size_t i = 0; i < assignment->getSubmissions().getSize(); i++)
	{
		if (assignment->getSubmissions()[i].getStudentId() == userId)
		{
			assignment->getSubmissions()[i].setGrade(grade);
			assignment->getSubmissions()[i].setTeacherComment(teacherComment);
			updateAssignments(courses);

			cout << "Assignment successfully graded!" << endl;

			return;
		}
	}

	cout << "User with such id either is not in the course or has not turned his submission in." << endl;
}

void Teacher::messageStudents(const MyString& courseName, const MyString& content, MyVector<User*>& users, MyVector<Course*>& courses) {
	if (courseName == "" || content == "")
	{
		cout << "Course name and content cannot be empty!" << endl;
		return;
	}

	Course* course = findCourse(courseName, courses);

	if (!course)
	{
		cout << "Course with such name does not exist!" << endl;
		return;
	}

	if (course->getTeacherId() != id)
	{
		cout << "You don't have access to this course!" << endl;
		return;
	}

	MyString sender;
	sender += this->name;
	sender += " ";
	sender += this->surname;

	for (size_t i = 0; i < users.getSize(); i++)
	{
		if (users[i]->getId() == id)
		{
			continue;
		}

		for (size_t j = 0; j < users[i]->getCourses().getSize(); j++)
		{
			if (users[i]->getCourses()[j]->getName() == courseName)
			{
				Message message(users[i]->getId(), sender, content);
				users[i]->addMessage(message);
			}
		}
	}

	updateMessages(users);

	cout << "Message successfully sent!" << endl;
}