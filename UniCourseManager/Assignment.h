#pragma once

#include "MyVector.h"
#include "MyString.h"

struct Submission {
private:
	int studentId;
	double grade;
	MyString answer;
	MyString teacherComment;

public:
	Submission(int studentId = 0, const MyString& answer = "")
	{
		this->studentId = studentId;
		this->answer = answer;

		grade = 0;
		teacherComment = "nocomment";
	}
	
	Submission(int studentId, double grade, const MyString& answer, const MyString& teacherComment)
	{
		this->studentId = studentId;
		this->answer = answer;
		this->grade = grade;
		this->teacherComment = teacherComment;
	}

	int getStudentId() const {
		return studentId;
	}

	double getGrade() const {
		return grade;
	}

	const MyString& getAnswer() const {
		return answer;
	}
	
	const MyString& getTeacherComment() const {
		return teacherComment;
	}

	void setGrade(double grade) {
		if (grade < 2 || grade > 6)
		{
			throw std::invalid_argument("Grade must be between 2 and 6!");
		}

		this->grade = grade;
	}

	void setTeacherComment(const MyString& teacherComment) {
		this->teacherComment = teacherComment;
	}
};

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