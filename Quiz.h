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
		cout << "\n��������� ����. ����-�����: �������� ��������� ������";
		result = rand() % 12 + 1;
		cout << "\n����, �� �������� " << result << endl;
		return result;
		//database->Getstudents()[num].
	}
	void Save()
	{
		database->Write();
	}

};
