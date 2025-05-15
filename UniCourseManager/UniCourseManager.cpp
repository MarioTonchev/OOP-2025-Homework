#include <iostream>
#include <fstream>
#include <typeinfo>

#include "Admin.h"
#include "Course.h"
#include "SystemFunctions.h"
#include "MyVector.h"
#include "MyString.h"

using namespace std;

int main()
{
	//Make sure to add admin in users.txt before starting the program! Admin|admin|adminov|0000|0
	MyVector<User*> users;
	MyVector<Course*> courses;

	try
	{
		loadUsers(users);
		loadMessages(users);
		loadCourses(courses);
		loadEnrollments(users, courses);
		loadTeacherCourses(users, courses);
		loadAssignments(courses);

		User* user = nullptr;
		MyString userType;

		MyString command;

		login(command, users, user, userType);

		command = "";
		command.getline(cin);

		while (true)
		{
			MyVector<MyString> tokens = command.split(' ');
			MyString action = tokens[0];

			if (userType == "Admin")
			{
				Admin* admin = dynamic_cast<Admin*>(user);

				if (action == "add_teacher" && tokens.getSize() == 4)
				{
					admin->createTeacher(tokens[1], tokens[2], tokens[3], users);
				}
				else if (action == "add_student" && tokens.getSize() == 4)
				{
					admin->createStudent(tokens[1], tokens[2], tokens[3], users);
				}
				else if (action == "delete_user" && tokens.getSize() == 2)
				{
					admin->deleteUser(tokens[1].toInt(), users);
				}
				else if (action == "message_all")
				{
					MyString content = vectorToString(tokens, 1);
					admin->messageAll(content, users);
				}
				else if (action == "mailbox" && tokens.getSize() == 2)
				{
					admin->checkUserMailbox(tokens[1].toInt(), users);
				}

			}
			else if (userType == "Teacher")
			{
				Teacher* teacher = dynamic_cast<Teacher*>(user);

				if (action == "create_course" && tokens.getSize() == 3)
				{
					teacher->createCourse(tokens[1], tokens[2], courses);
				}
				else if (action == "add_to_course" && tokens.getSize() == 3)
				{
					teacher->addToCourse(tokens[1], tokens[2].toInt(), users, courses);
				}
				else if (action == "assign_homework" && tokens.getSize() == 3)
				{
					teacher->createAssignment(tokens[1], tokens[2], courses);
				}
				else if (action == "preview_assignment_works" && tokens.getSize() == 3)
				{
					teacher->previewAssignmentWork(tokens[1], tokens[2], courses, users);
				}
				else if (action == "grade_assignment" && tokens.getSize() >= 6)
				{
					MyString comment = vectorToString(tokens, 5);
					teacher->gradeStudent(tokens[1], tokens[2], tokens[3].toInt(), tokens[4].toDouble(), comment, courses);
				}
				else if (action == "message_students" && tokens.getSize() >= 3)
				{
					MyString content = vectorToString(tokens, 2);
					teacher->messageStudents(tokens[1], content, users);
				}
			}
			else if (userType == "Student")
			{
				Student* student = dynamic_cast<Student*>(user);

				if (action == "enroll" && tokens.getSize() == 3)
				{
					student->enroll(tokens[1], tokens[2], courses);
				}
				else if (action == "finish_assignment" && tokens.getSize() >= 4)
				{
					MyString answer = vectorToString(tokens, 3);
					student->finishAssignment(tokens[1], tokens[2], answer, courses);
				}
				else if (action == "grades" && tokens.getSize() == 1)
				{
					student->checkGrades();
				}
			}

			if (action == "message" && tokens.getSize() >= 3)
			{
				MyString content = vectorToString(tokens, 2);
				user->message(tokens[1].toInt(), content, users);
			}
			else if (action == "mailbox" && tokens.getSize() == 1)
			{
				user->checkMailbox();
			}
			else if (action == "clear_mailbox")
			{
				user->clearMailbox();
				updateMessages(users);
			}
			else if (action == "change_password" && tokens.getSize() == 3)
			{
				user->changePassword(tokens[1], tokens[2]);
				updateUsers(users);
			}
			else if (action == "logout")
			{
				user = nullptr;
				userType = "";
				command = "";

				clearConsole();
				cout << "Logout successful!" << endl << endl;

				login(command, users, user, userType);
			}
			else if (action == "quit")
			{
				return 0;
			}

			command.getline(cin);
		}
	}
	catch (const std::exception& e)
	{
		cout << e.what();
	}	
}