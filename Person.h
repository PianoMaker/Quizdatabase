// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include"global.h"
#include"Login.h"
#include"Password.h"
#include "Phone.h"
#include "Mail.h"

class Person
{
protected:
	Login login;
	Password password;
	Phone phone;
	Mail mail;
public:
	//Person() { Message(10, "Person destructor is running"); };
	string GetPassword()
	{
		return password.GetPassword();
	}
	string GetLogin()
	{
		return login.GetLogin();
	}
	string GetPhone()
	{
		return phone.GetPhone();
	}
	string GetMail()
	{
		return mail.GetMail();
	}
	Person(string login, string password, string phone, string mail)
	{
		this->login.SetLogin(login);
		this->password.SetPassword(password);
		this->phone.SetPhone(phone);
		this->mail.SetMail(mail);
	}
	Person(Login login, Password password, Phone phone, Mail mail)
	{
		cout << "\n\t������ ����������� ������� � �����������";
		this->login.SetLogin(login.GetLogin());
		this->password.SetPassword(password.GetPassword());
		this->mail.SetMail(mail.GetMail());
		this->phone.SetPhone(phone.GetPhone());
	}
	~Person() { GrayMessage("Person destructor is running \n"); Sleep(10); };
};

class Student : public Person
{
private:
	int marks;
public:
	Student(Login login, Password password, Phone phone, Mail mail) : 
		Person(login, password, phone, mail)
	{
		marks = 0;
	}
	Student(string login, string password, string phone, string mail)
		: Person(login, password, phone, mail) {};

	void SetMarks(int marks)
	{
		this->marks = marks;
	}

};

class Admin : public Person
{
public:
	Admin(Login login, Password password, Phone phone, Mail mail) :
		Person(login, password, phone, mail) {};
	Admin(string login, string password, string phone, string mail)
		: Person(login, password, phone, mail) {};


};