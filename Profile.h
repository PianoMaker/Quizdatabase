#pragma once
#include"global.h"
#include"Quiz.h"
#include "Menues.h"
class Menues;

class Profile
{
private:
	Login login;
	Password password;
	Mail mail;
	Phone phone;
	Database* database;
	Quiz* quiz;
	int role;
	int currentID;


public:
	Profile(Database* database, Quiz* quiz) : database(database), quiz(quiz)
	{
		role = unlogged;
		Menu();
	}
	void Menu()
	{
		Menues menu;
		menu.Show(role, login.GetLogin());
		int choice = menu.choice(role);
		switch (choice)
		{
		case 0:Exit(); break;
		case 1:LogIn(); break;
		case 2:SignUp(); break;
		case 3:UnLog(); break;
		case 4:database->Show(); break;
		case 5:Quiz(); break;
		case 6:Write(); break;
		case 7:database->Read(); break;
		default:Menu(); break;
		}
	}

	void LogIn()
	{
		/*
		Вхід у систему для зареєстрованих користувачів
		*/

		//cout << "\n\tзапущено LogIn\n";
		int index = 0;
		WelcomeMessage( "Type login\n");
		CINIGNORE;
		string temp;
		getline(cin, temp);
		cout << "\n\tВведено " << temp;
		int attempts = 0;

		if (database->SearchAdmin(index, temp))
		{
			cout << "\nв базі знайдено адміна з такимм логіном";
			cout << "\nіндекс = " << index << endl;		
			CheckPassword(index, admin, attempts);
			role = admin;
			currentID = index + 1;
			login.SetLogin(temp);
		}
		else if (database->SearchStudent(index, login.GetLogin()))
		{
			cout << "\nв базі знайдено студента з такимм логіном";
			CheckPassword(index, student, attempts);
			role = student;
			currentID = index + 1;
			login.SetLogin(temp);
		}
		else
		{
			cout << "\nнічого не знайшли!";
			int choice;
			choice = choiceM("\n1 - once more, 2 - signup, 3 - back to Menu");
			switch (choice)
			{
			case 1: LogIn(); break;
			case 2: SignUp(); break;
			case 3: Menu(); break;
			default: throw 1;
			}

		}
	}

	void SignUp()
	{
		/*
		Реєстрація нового користувача
		*/
		if (role == unlogged)
		{
			int attempts = 0;
			InsertLogin(attempts);
			password.Insert(attempts);
			mail.Insert();
			phone.InsertPhone();
			if (choice("student", "admin")) role = student;
			else role = admin;
			if (role == student)
			{
				Student newstudent(login, password, phone, mail);
				database->AddStudent(newstudent);
				currentID = database->Getstudents().size();
			}
			else if (role == admin)
			{
				Admin newadmin(login, password, phone, mail);
				database->AddAdmin(newadmin);
				currentID = database->Getadmins().size();
			}
		}
		else cout << "you should log out first\n";
	};

	void UnLog()
	{
	/* вихід із системи */
		role = unlogged;
		login.SetLogin("");
		password.SetPassword("");
	}

	void InsertLogin(int &attempts)
	{
		Login temp;
		temp.Insert();
		if (attempts >= 5) throw 2;
		if (!CheckLogin(temp.GetLogin(), attempts)) InsertLogin(attempts);
		else
		{
			login = temp; attempts = 0;
		}
	}

	/* перевірка на унікальність */
	bool CheckLogin(string txt, int& attempts)
	{
		if (!database->SearchAdmin(txt) && !database->SearchStudent(txt))
			return true;
		else
		{
			ErrorMessage("This login is already used, try another!\n");
			attempts++;/*обмеження до 5 спроб*/
			return false;
		}
	}


	void CheckPassword(int num, int role, int &attempts)
	{
		/* перевірка чи правильний пароль */
		try {
			string temppassword; 
			WelcomeMessage( "Enter password\n");
			getline(cin, temppassword);
			if (role == admin)
			{
				if (!temppassword.compare(database->Getadmins(num).GetPassword()))
					cout << "success\n";
				else
				{
					cout << "try once more\n";
					attempts++;/*обмеження до 5 спроб*/
					if (attempts > 5) {
 						throw 2;
					}
					CheckPassword(num, role, attempts);
				}
			}
			else if (role == student)
			{
				if (!temppassword.compare(database->Getstudents(num).GetPassword()))
					cout << "\nsuccess";
				else
				{
					cout << "try once more\n";
					attempts++;
					if (attempts >= 5) throw 2;
					CheckPassword(num, role, attempts);
				}
			}
		}
		catch(int)
		{
			throw 2;
		}
	}
	void Exit()
	{
		Message(14, "Are you sure you want to exit?");
		if (choice("No", "Yes")) Menu();
		else throw 0;
	}

	void Quiz()
	{
		/* прохдження тесту */
		if (currentID == 0 || role != student) cout << "\nтести можуть проходити лише зареєстровані студенти";
		else
		{
			cout << "\nви проходите тест як студент " << database->Getstudents(currentID - 1).GetLogin();
			quiz->Demo();
		}
	}

	void Write()
	{
	/* запис БД у файл */
		cout << "\nwriting to file " << database->GetFilename();
		database->Write();
	}


};




