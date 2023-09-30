#pragma once
#include "global.h"
#include "Question.h"


class Quizbase
{
	int role; // ����/�������
	string filename;
	vector<Question> questions;
	Category* categories; // ������ �������� ������
	int lastID; // ID ���������� ������� � ���
	ifstream read;
	ofstream write;

public:
	Quizbase(string filename, Category* categories) : filename(filename), categories(categories)
	{
		/* ϳ� ��� ����������� ������� �� ��������� � ����� */
		Read();
		Sleep(500);
		cout << "\n������������ ���� ������ �� ������� ����� " << filename;
		Sleep(500);
	}
	int GetNrOfQuestions()
	{
		return questions.size();
	}
	/* ������ ������� */
	void Add()
	{
		/* ����������� � Quiz -> AdminQuiz */
		Question newquestion(categories); // ��������� ������� - ����� �����������
		questions.push_back(newquestion);
		questions[questions.size() - 1].SetID(lastID + 1);
		lastID++;
		Write();			// ����� �� �� //
	}
	void DeleteMenu()
	{
		/* ����������� � Quiz -> AdminQuiz */
		{
			int index = choiceM("��� ������� ��������?\n");
			Delete(index - 1); 
		}
	}

	void Delete(int index)
	{
		questions.erase(questions.begin() + index);
	}


	/* ���������� ������� � ��������� */
	void Edit()
	{
		for (int i = 0; i < questions.size(); i++)
			cout << i + 1 << " " << questions[i].GetQuestion() << endl;
		int num;
		Message(green, "������ ����� �������, ��� ��� ������������\n");
		while (true)
		{
			cin.clear();
			cin.ignore();
			cin >> num;
			if (cin.fail() || num<1 || num > questions.size())
				Message(red, "����������� �����\n");
			else break;
		}
		
		questions[num - 1].EditQuestion();

		Message(yellow, "��������� �������:\n");
		cout << questions[num - 1].GetCorrectAnswer();
		Message(green, "\n������ ��������� �������\n");
		questions[num - 1].EditCorrectAnswer();
		Message(green, "����������� ���������� ������?\n");
		int choice;
		do
		{
			int nrofanswer;
			choice = choiceM("1 - �����������, 2 - ����������, 3 - ��������, 4 - ������ ��, 0 - ����������� �� ����");
			switch (choice)
			{
			case 1:
				for (int i = 1; i < questions[num - 1].GetNrOfAnswers(); i++)
					cout << i << " " << questions[num - 1].GetCustomAnswer(i) << endl;
				break;
			case 2:
				
				Message(green, "������ ����� ������, ��� ��� ������������\n");
				while (true)
				{
					cin.clear();
					cin.ignore();
					cin >> nrofanswer;
					if (cin.fail() || nrofanswer<1 || nrofanswer >= questions[num - 1].GetNrOfAnswers())
						Message(red, "����������� �����\n");
					else break;
				}
				questions[num - 1].EditCustomAnswer(nrofanswer);
				Message(gray, "\n������� ������������\n");
				break;
			case 3:
				Message(green, "������ ����� ������, ��� ��� ��������\n");
				while (true)
				{
					cin.clear();
					cin.ignore();
					cin >> nrofanswer;
					if (cin.fail() || nrofanswer<1 || nrofanswer >= questions[num - 1].GetNrOfAnswers())
						Message(red, "����������� �����\n");
					else break;
				}
				questions[num - 1].DeleteIncorrectAnswer(nrofanswer);
				Message(gray, "\n������� ��������");
				break;
			case 4:
				questions[num - 1].AddIncorrectAnswer(); break;
			case 0: return;
			default: cout << "����������� ����\n"; break;

			}


		} while (choice);



		Write();			//...//
	}

	void Show()
	{
		cout << "������ ������: " << questions.size() << endl;
		for (int i = 0; i < questions.size(); i++)
		{
			Message(green, to_string(i + 1) + ". ");
			questions[i].ShowProperly();
		}
		int choice = (choiceM("1 - ������ �������, 2 - ���������� �������, 3-�������� �������, 0 - ����� �� ����"));
		switch (choice)
		{
		case 1:Add(); break;
		case 2:Edit(); break;
		case 3:DeleteMenu(); break;
		case 0: return; break;
		default: return;
		}

	}
	void ShowByCat(string txt)
	{
		for (int i = 0; i < questions.size(); i++)
			if (questions[i].GetCategory() == txt) questions[i].ShowProperly();
		if (choice("������ �������", "����� �� ����")) Add();
		else return;
	}
	int CatSize(string txt)
	{
		int size = 0;
		for (int i = 0; i < questions.size(); i++)
			if (questions[i].GetCategory() == txt) size++;
		return size;
	}

	vector<Question> GetQuestion()
	{
		return questions;
	}

	void Write()
	{
		/* ����� �� � ���� */
		write.open(filename);
		if (!write) Message(red, "File is unavailable\n");
		for (int i = 0; i < questions.size(); i++)
		{
			write << "QUESTION %" << questions[i].GetID() << "&" << questions[i].GetCategory() << endl;
			write << questions[i].GetQuestion() << endl;
			for (int j = 0; j < questions[i].GetNrOfAnswers(); j++)
				write << questions[i].GetCustomAnswer(j) << endl;
			write << "[end]" << endl;
		}
		write.close();
	}
	void Read()
	{
		read.open(filename);
		if (!read) Message(red, "\nFile is inaccessible\n");
		else cout << "\nreading file\n";

		int num = 0, ID;
		string line, category, question;
		vector<string> answers;
		while (getline(read, line))
		{
			answers.clear();
			istringstream iss(line);
			string token;
			getline(iss, token, '%');
			if (token != "QUESTION ") break;//������ ������ � �����, �� ���������� ������ QUESTION, ���� ������
			getline(iss, token, '&');//���� ����� ����� - ����� ������
			ID = stoi(token);
			getline(iss, token, '\n');
			category = token;
			getline(read, token, '\n');
			question = token;
			// �������� ������ � ������ ������ ��
			while (true)
			{
				getline(read, token, '\n');
				if (token == "[end]") break;
				answers.push_back(token);
				num = answers.size();
			}
			Question newquestion(num, categories, question, answers, category, ID);
			questions.push_back(newquestion);
			lastID = ID;//������������ ID ���������� ������
		}

	}

};

