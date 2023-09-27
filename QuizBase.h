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
		/* ϳ� ��� ����������� ������� �� ��������� � ����� */
		Read();
		Sleep(500);
		cout << "\n������������ ���� ������ �� ������� ����� " << filename;
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
		/* ����� �� � ���� */
		write.open(filename);
		//...//
	}
	void Show()
	{
		cout << "������ ������: " << questions.size() << endl;
		for (int i = 0; i < questions.size(); i++)
			questions[i].ShowProperly();
		if (choice("������ �������", "����� �� ����")) Add(); 
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

