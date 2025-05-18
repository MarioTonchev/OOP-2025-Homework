//Mario Tonchev Tonchev 0MI0600460
#include <iostream>

#include "CourseUtils.h"

using namespace std;

Course* findCourse(const MyString& courseName, MyVector<Course*>& courses) {
	Course* course = nullptr;

	for (size_t i = 0; i < courses.getSize(); i++)
	{
		if (courses[i]->getName() == courseName)
		{
			course = courses[i];
			break;
		}
	}

	return course;
}

Assignment* findAssignment(const MyString& assignmentName, const MyString& courseName, MyVector<Course*>& courses) {
	Course* course = findCourse(courseName, courses);

	if (!course)
	{
		cout << "Course with such name does not exist!" << endl;
		return nullptr;
	}

	Assignment* assignment = nullptr;

	for (size_t i = 0; i < course->getAssignments().getSize(); i++)
	{
		if (course->getAssignments()[i].getName() == assignmentName)
		{
			assignment = (Assignment*)&course->getAssignments()[i];
			break;
		}
	}

	return assignment;
}