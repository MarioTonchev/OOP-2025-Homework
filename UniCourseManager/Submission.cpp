//Mario Tonchev Tonchev 0MI0600460
#include "Submission.h"

Submission::Submission(int studentId, const MyString& answer)
{
	this->studentId = studentId;
	this->answer = answer;

	grade = 0;
	teacherComment = "nocomment";
}

Submission::Submission(int studentId, double grade, const MyString& answer, const MyString& teacherComment)
{
	this->studentId = studentId;
	this->answer = answer;
	this->grade = grade;
	this->teacherComment = teacherComment;
}

int Submission::getStudentId() const {
	return studentId;
}

double Submission::getGrade() const {
	return grade;
}

const MyString& Submission::getAnswer() const {
	return answer;
}

const MyString& Submission::getTeacherComment() const {
	return teacherComment;
}

void Submission::setGrade(double grade) {
	if (grade < 2 || grade > 6)
	{
		throw std::invalid_argument("Grade must be between 2 and 6!");
	}

	this->grade = grade;
}

void Submission::setTeacherComment(const MyString& teacherComment) {
	this->teacherComment = teacherComment;
}