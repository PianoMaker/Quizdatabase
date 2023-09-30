// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include"global.h"
#include"Login.h"
#include"Password.h"
#include "Phone.h"
#include "Mail.h"
#include"Results.h"

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
		Message(gray,"+p ");
		this->login.SetLogin(login);
		this->password.SetPassword(password);
		this->phone.SetPhone(phone);
		this->mail.SetMail(mail);
	}
	Person(Login login, Password password, Phone phone, Mail mail)
	{
		Message(gray,"+p ");
		this->login.SetLogin(login.GetLogin());
		this->password.SetPassword(password.GetPassword());
		this->mail.SetMail(mail.GetMail());
		this->phone.SetPhone(phone.GetPhone());
	}
	~Person() { Message(gray,"~p\n"); Sleep(10); };
};

class Student : public Person
{
private:
	vector<Results> results;
	int progress;
public:
	Student(Login login, Password password, Phone phone, Mail mail) : 
		Person(login, password, phone, mail)
	{
		Message(gray,"+p ");
		
	}
	Student(string login, string password, string phone, string mail, string tempresults)
		: Person(login, password, phone, mail) 
	{
		/* застосовується під час зчитування файлу */
		ReadResults(tempresults);
		Message(gray,"+p ");
	};
	string StringResults()
	{
		string allresult;
		for (int i = 0; i < results.size(); i++)
			allresult.append(results[i].GetString()).append(";");
		return allresult;
	}
	vector<Results> GetResults()
	{
		Message(yellow, "Імпорт результатів");
		system("pause");
		return results;
	}

	int ResultsSize()
	{
		return results.size();
	}
	
	void SetResults(vector<Results> results)
	{
		this->results = results;
		Message(gray, "результати записано в базу даних\n");
		cout << "size = " << results.size() << endl;
		system("pause");
	}

	


	int GetProgress()
	{ return progress; }

	void ReadResults(string tempresults)
	{
		istringstream iss(tempresults);
		string token;

		progress = 0;
		while (getline(iss, token, ';')) {
			// Розділяємо вичитаний з файлу рядок на числа та знаки за ":"
			size_t pos = token.find(":");
			if (pos != string::npos && pos > 0 && pos < token.length() - 1) {
				int number = stoi(token.substr(0, pos));
				char sign = token[pos + 1];
				Results newresult(number, sign);
				results.push_back(newresult);
				progress = newresult.GetQID() + 1;
			}
		}
	}


};

class Admin : public Person
{
public:
	Admin(Login login, Password password, Phone phone, Mail mail) :
		Person(login, password, phone, mail) {
		Message(gray,"+p ");
	};
	Admin(string login, string password, string phone, string mail)
		: Person(login, password, phone, mail) {
		Message(gray,"+p ");
	};


};