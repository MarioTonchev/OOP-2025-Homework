//Mario Tonchev Tonchev 0MI0600460
#pragma once

#include "MyString.h"

struct Submission {
private:
	int studentId;
	double grade;
	MyString answer;
	MyString teacherComment;

public:
	Submission(int studentId = 0, const MyString& answer = "");

	Submission(int studentId, double grade, const MyString& answer, const MyString& teacherComment);

	int getStudentId() const;

	double getGrade() const;

	const MyString& getAnswer() const;

	const MyString& getTeacherComment() const;

	void setGrade(double grade);

	void setTeacherComment(const MyString& teacherComment);
};
