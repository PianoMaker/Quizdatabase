#pragma once
#include"global.h";
#include"Database.h"


class Quiz
{
private:
	int result;
	Database* database;


public:
	Quiz(Database* database) : database(database)
	{
		result = 0;
	}
	int Demo()
	{
		cout << "\nпроходимо тест. бета-версія: генеруємо випадкову оцінку";
		result = rand() % 12 + 1;
		cout << "\nвітаю, ви отримали " << result << endl;
		return result;
		//database->Getstudents()[num].
	}
	void Save()
	{
		database->Write();
	}

};
