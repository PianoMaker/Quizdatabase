#pragma once
#include"global.h";
#include"Database.h"
#include"QuizBase.h"
#include"Results.h"


class Quiz
{
private:
	int progress;
	Database* database;
	Quizbase* quizbase;
	
	vector<Results> results;

public:
	Quiz(Database* database, Quizbase* quizbase) : database(database), quizbase(quizbase)
	{
		progress = 0;
	}
	void Admin()
	{
		int choice = choiceM("1 - переглянути питання, 2 - додати питання, 3 - випробувати тест");
		switch (choice)
		{
		case 1: quizbase->Menu(choice, admin); break;
		case 2: quizbase->Add(); break;
		case 3: quizbase->GetQuestion()[progress].MakeQuiz(); break;
		default: return;
		}
	}
	void Student()
	{
		int choice = choiceM("1 - переглянути результати, 2 - пройти тестування");
		switch (choice)
		{
		case 1: cout << "пройдено = " << progress << "питань\n"; Show(); break;
		case 2:  quizbase->GetQuestion()[progress].MakeQuiz(); break;
		default: return;
		}
	}
	
	void Show()
	{
		for (int i = 0; i < results.size(); i++)
		{
			cout << "питання № " << i;
			results[i].Show();
		}
	}

	void Save()
	{
		database->Write();
	}

};
