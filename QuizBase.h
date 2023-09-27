#pragma once
#include "global.h"
#include "Question.h"

class Quizbase
{
	int role;
	string filename;
	ifstream read;
	ofstream write;
	vector<Question> questions;

public:
	Quizbase(string filename) : filename(filename)
	{
		/* Під час ініціалізації системи БД зчитується з файлу */
		Read();
		Sleep(500);
		cout << "\nініціалізували банк питань за адресою файлу " << filename;
		Sleep(500);
	}

	void Add()
	{
		Question newquestion;
		questions.push_back(newquestion);

			//...//
	}
	void Read()
	{
		read.open(filename);
		if (!read) ErrorMessage("\nFile is inaccessible\n");
		else cout << "\nreading file\n";
		//...//
	}
	void Write()
	{
		/* запис БД у файл */
		write.open(filename);
		//...//
	}
	void Show()
	{
		cout << "усього питань: " << questions.size() << endl;
		for (int i = 0; i < questions.size(); i++)
			questions[i].ShowProperly();
		if (choice("додати питання", "назад до меню")) Add(); 
		else return;
		
	}


	void Menu(int choice, int role)
	{
		if (role == admin && choice == 1) Show();
		else if (role == admin && choice == 2) Add();
	}

	vector<Question> GetQuestion()
	{
		return questions;
	}
};

