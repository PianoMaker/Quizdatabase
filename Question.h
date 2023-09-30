#pragma once
#include"global.h"
#include <algorithm>
#include <random>
#include "Category.h"
#define ENTER Message(gray, "�������� Enter, ��� ������ ��� ���\n");

class Question
{
private:

	int nrofanswers;
	int ID;
	string question;
	string* answers;
	string category;
	Category* categories;
	Results* results;

public:
	/* �� ����������� ������� ���'��� ���  1 ��������� ������, ������ ��������� � ������ */
	Question(Category *categories) : nrofanswers(1), categories(categories)
	{
		answers = new string[nrofanswers];
		AddQuestion();
		AddCorrectAnswer();
		AddIncorrectAnswer();
		category = categories->EnterCat();
		Message(gray,"question has been succesfully added\n");

	}

	Question(int nrofanswers, Category* categories) : nrofanswers(nrofanswers), categories(categories)
	{
		answers = new string[nrofanswers];
	}
	Question(int nrofanswers, Category* categories, string question, vector<string>answers, string category, int ID) : nrofanswers(nrofanswers), categories(categories)
	{
		this->question = question;
		this->answers = new string[nrofanswers];
		for (int i = 0; i < nrofanswers; i++)
			this->answers[i] = answers[i];
		this->category = category;
		this->ID = ID;
	}
	Question(const Question& obj)
	{
		nrofanswers = obj.nrofanswers;
		question = obj.question;
		category = obj.category;
		categories = obj.categories;
		answers = new string[nrofanswers];
		for (int i = 0; i < nrofanswers; i++)
			answers[i] = obj.answers[i];
		ID = obj.ID;

	}
	
	Question operator = (Question obj)
	{
		nrofanswers = obj.nrofanswers;
		question = obj.question;
		answers = new string[nrofanswers];
		for (int i = 0; i < nrofanswers;i++)
			answers[i] = obj.answers[i];
		ID = obj.ID;
		return *this;
	}
	
	Question operator += (string ans)
	{

		string* temp = new string[nrofanswers + 1];
		for (int i = 0; i < nrofanswers; i++)
			temp[i] = answers[i];
		temp[nrofanswers] = ans;
		delete answers;
		answers = temp;
		nrofanswers++;
	}
	string GetQuestion()
	{
		return question;
	}
	int GetNrOfAnswers()
	{
		return nrofanswers;
	}
	string GetCorrectAnswer()
	{
		return answers[0];
	}
	string GetCustomAnswer(int num)
	{
		return answers[num];
	}
	string GetCategory()
	{
		return category;
	}
	int GetID()
	{
		return ID;
	}
	void AddQuestion()
	{
		Message(green,"������ �������\n");
		CINIGNORE;
		getline(cin, question);
	}
	void AddCorrectAnswer()
	{
		Message(green,"������ ��������� �������\n");
		CINIGNORE;
		getline(cin, answers[0]);
	}
	void AddIncorrectAnswer()
	{
		bool more;
		Message(green, "������ ���������� �������\n");
		do
		{
		string ans;
		getline(cin, ans);
		string* temp = new string[nrofanswers + 1];
		for (int i = 0; i < nrofanswers; i++)
			temp[i] = answers[i];
		temp[nrofanswers] = ans;
		delete[] answers;
		answers = temp;
		nrofanswers++;
		more = choice("������ ��? 1 - ���", "2 - ͳ\n");
		} while (more);
	}
	void DeleteIncorrectAnswer(int num)
	{
		string* temp = new string[nrofanswers - 1];
		for (int i = 0; i < num; i++)
			temp[i] = answers[i];
		for (int i = num; i < nrofanswers; i++)
			temp[i] = answers[i + 1];
		delete[] answers;
		answers = temp;
	}


	void EditQuestion()
	{
		string temp;
		cout << question << endl;
		ENTER;
		CINIGNORE;
		getline(cin, temp);
		if (temp.size())
		{
			question = temp;// �������� ���� ���� ����� �� �������
			Message(gray,"question has been edited\n");
		}
	}

	void EditCorrectAnswer()
	{
		string temp;
		ENTER;
		//CINIGNORE;
		getline(cin, temp);
		if (temp.size())
		{
			answers[0] = temp;// �������� ���� ���� ����� �� �������
			Message(gray, "answer has been edited\n");
		}
	}

	void EditCustomAnswer(int nrofanswer)
	{
		string temp;

		cout << answers[nrofanswer] << endl;
		ENTER;
		CINIGNORE;
		getline(cin, temp);
		if (temp.size())
		{
			answers[nrofanswer] = temp;// �������� ���� ���� ����� �� �������
			Message(gray, "answer has been edited\n");
		}
	}
	


	/* ������� � ����������� ��������� �� ����� */
	void ShowProperly()
	{
		Message(green,question + "\n");
		Message(gray,"��������: " + GetCategory() + ", ID: " +  to_string(GetID()) + "\n");
		for (int i = 0; i < nrofanswers; i++)
			cout << "\t-" << i + 1 << " " << answers[i] << endl;
	}
	/* ���� */



	bool MakeQuiz(int &questionID)
	{
		questionID = ID;
		int clue = -1;
		Message(green,question + "\n");// ������� �� �����
		string* temp = new string[nrofanswers]; 
		for (int i = 0; i < nrofanswers; i++)
			temp[i] = answers[i];
		/* �������� ������� ������ � ����������� ������� */
		shuffle(temp, temp + nrofanswers, default_random_engine(rand()));
		/* ������� �������� �� ����� */
		for (int i = 0; i < nrofanswers; i++)
			cout << i << " - " << temp[i] << endl;
		/* ����� ����� ���������� */
		for (int i = 0; i < nrofanswers; i++)
			if (temp[i] == answers[0]) clue = i;

		delete[] temp;
		Message(green,"\n��� � �������� ���������?\n");
		CINIGNORE;
		bool accept = true;
		do
		{
			int choice;
			cin >> choice;
			if (choice < 1 || choice > nrofanswers || cin.fail())
			{
				// ���� ������� ��������� ����� ������ ��� ���������� ������  
				Message(yellow, "������ �������� �� 0 � " + to_string(nrofanswers));
				accept = false;
			}
			else if (choice == clue)
			{
				Message(green,"success\n"); return true;
			}
			else if (clue == -1)
			{
				// ���� ���� ���������� �� ���� ��������
				cout << "�������, ������� � ���������, ��������� �� ������������\n";  return true;
			}
		} while (!accept);
		Message(yellow, "unsuccess\n");

		
		return false;
	}
	void SetID(int num)
	{
		this->ID = num;
	}

	~Question()
	{
		delete[] answers;
	}
};

