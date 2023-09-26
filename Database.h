// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include"global.h"
#include"Person.h"

class Database
{
private:
	int role;
	string filename;
	vector<Student> students;
	vector<Admin> admins;
	ifstream read;
	ofstream write;


public:
	Database(string filename) : filename(filename)
	{
		/* Під час ініціалізації системи БД зчитується з файлу */
		Read();
		Sleep(500);
		cout << "\nініціалізували базу даних за адресою файлу " << filename;
		Sleep(500);
	}
	void AddStudent(Student newstudent)
	{
		/* додавання студента до БД */
		students.push_back(newstudent);
		Write();
	}
	void AddAdmin(Admin newadmin)
	{
		/* додавання адміністратора до БД */
		admins.push_back(newadmin);
		Write();
	}
	vector<Student> Getstudents()
	{
		return students;
	}
	Student Getstudents(int num)
	{
		//cout << "\nдає інфо про еклемпляр класу студент за номером num";
		return students[num];
	}
	vector<Admin> Getadmins()
	{
		return admins;
	}
	Admin Getadmins(int num)
	{
		//cout << "\nдає інфо про еклемпляр класу адммін за номером num";
		return admins[num];
	}
	void Show()
	{
	/* БД виводиться на екран */
		WelcomeMessage("\n\tПеревірка бази даних\n");
		cout << "\nусі студенти (знайдено " << students.size() << ")\n";
		for (int i = 0; i < students.size(); i++)
			cout << students[i].GetLogin() 
			<< "\t" << students[i].GetPassword() 
			<< "\t" << students[i].GetMail() 
			<< "\t" << students[i].GetPhone() << endl;

		cout << "\nусі адміни(знайдено " << admins.size() << ")\n";
		for (int i = 0; i < admins.size(); i++)
			cout << admins[i].GetLogin()
			<< "\t" << admins[i].GetPassword()
			<< "\t" << admins[i].GetMail()
			<< "\t" << admins[i].GetPhone() << endl;
		CINIGNORE;

	}
	bool SearchStudent(int& index, string log)
	{
		/* пошук студента зі збереження ID */
		for (int i = 0; i < students.size(); i++)
			if (!log.compare(students[i].GetLogin()))
			{
				index = i;
				return true;
			}
		return false;
	}
	bool SearchStudent(string log)
	{
		/* простий пошук студента */
		for (int i = 0; i < students.size(); i++)
			if (!log.compare(students[i].GetLogin())) return true;
		return false;
	}
	bool SearchAdmin(int& index, string log)
	{
		/* пошук адміністратора зі збереження ID */
		for (int i = 0; i < admins.size(); i++)
			if (!log.compare(admins[i].GetLogin()))
			{
				index = i;
				return true;
			}
		return false;
	}
	bool SearchAdmin(string log)
	{
		/* простий пошук адміністратора */
		for (int i = 0; i < admins.size(); i++)
			if (!log.compare(admins[i].GetLogin())) return true;
		return false;
	}

	void Write()
	{
		/* запис БД у файл */
		write.open(filename);

		for (int i = 0; i < admins.size(); i++)
			write << "admin" << "\t" << i 
			<< "\t" << admins[i].GetLogin() 
			<< "\t" << admins[i].GetPassword() 
			<< "\t" << admins[i].GetMail()
			<< "\t" << admins[i].GetPhone()
			<< endl;
		for (int i = 0; i < students.size(); i++)
			write << "student" << "\t" << i 
			<< "\t" << admins[i].GetLogin()
			<< "\t" << admins[i].GetPassword()
			<< "\t" << admins[i].GetMail()
			<< "\t" << admins[i].GetPhone()
			<< endl;
		GrayMessage("\nDatabase has been updated\n");
		Sleep(1000);
	}

	void Read()
	{
		/* завантаження БД з файлу */

		read.open(filename);
		if (!read) ErrorMessage("\nFile is inaccessible\n");
		else cout << "\nreading file\n";

		string line; int temprole; string templogin; string temppassword; string tempmail; string tempphone;
		while (getline(read, line))
		{
			istringstream iss(line);
			string token;
			getline(iss, token, '\t');
			if (token == "admin") temprole = admin;
			else if (token == "student") temprole = student;
			else throw 7;
			getline(iss, token, '\t');
			cout << ".";
			getline(iss, token, '\t');
			templogin = token;
			getline(iss, token, '\t');
			temppassword = token;
			getline(iss, token, '\t');
			tempmail = token;
			getline(iss, token, '\t');
			tempphone = token;
			if (temprole == admin)
			{
				Admin newadmin(templogin, temppassword, tempphone, tempmail);
				admins.push_back(newadmin);
			}
			else if (temprole == student)
			{
				Student newstudent(templogin, temppassword, tempphone, tempmail);
				students.push_back(newstudent);
			}
			else throw 7;
		}

	}

	string GetFilename()
	{
		return filename;
	}

	~Database()
	{
		GrayMessage("DB destructor is running\n"); 
		write.close();
	}
};
