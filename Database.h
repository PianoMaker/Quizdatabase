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
	vector<Results> results;


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
	vector<Student> StudentInfo()
	{
		return students;
	}
	Student StudentInfo(int num)
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
	void RefreshResluts(int index, vector<Results> results)
	{
		students[index].SetResults(results);
		Message(yellow, "Оновлення результатів\n");
		system("pause");
	}

	void Show()
	{
	/* БД виводиться на екран */
		Message(green,"\n\tПеревірка бази даних\n");
		cout << "\nусі студенти (знайдено " << students.size() << ")\n";
		for (int i = 0; i < students.size(); i++)
			cout << students[i].GetLogin() 
			<< "\t" << students[i].GetPassword() 
			<< "\t" << students[i].GetMail() 
			<< "\t" << students[i].GetPhone() 
			<< "\t" << students[i].ResultsSize()
			<< endl;


		cout << "\nусі адміни(знайдено " << admins.size() << ")\n";
		for (int i = 0; i < admins.size(); i++)
			cout << admins[i].GetLogin()
			<< "\t" << admins[i].GetPassword()
			<< "\t" << admins[i].GetMail()
			<< "\t" << admins[i].GetPhone() << endl;
		CINIGNORE;

	}
	bool SearchStudent(int& index, string log, int& progress)
	{
		/* пошук студента зі збереження ID  та здобутків */
		for (int i = 0; i < students.size(); i++)
			if (!log.compare(students[i].GetLogin()))
			{
				index = i;
				progress = students[i].GetProgress();
				return true;
			}
		return false;
	}
	bool SearchStudent(string log)
	{
		/* простий пошук студента */
		for (int i = 0; i < students.size(); i++)
			if (!log.compare(students[i].GetLogin())) 							
				return true;
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
			<< "\t" << students[i].GetLogin()
			<< "\t" << students[i].GetPassword()
			<< "\t" << students[i].GetMail()
			<< "\t" << students[i].GetPhone()
			<< "\t" << students[i].StringResults()
			<< endl;
		Message(gray,"\nDatabase has been updated\n");
		Sleep(1000);
	}

	void Read()
	{
		/* завантаження БД з файлу */

		read.open(filename);
		if (!read) Message(red,"\nFile is inaccessible\n");
		else cout << "\nreading file\n";

		string line; int temprole; string templogin, temppassword, tempmail, tempphone; 
		string tempresults;
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
			if (temprole == student)
			{
				getline(iss, token, '\t');
				tempresults = token;
				Student newstudent(templogin, temppassword, tempphone, tempmail, tempresults);
				students.push_back(newstudent);
			}
			else if (temprole == admin)
			{
				Admin newadmin(templogin, temppassword, tempphone, tempmail);
				admins.push_back(newadmin);
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
		Message(gray,"DB destructor is running\n"); 
		write.close();
	}
};
