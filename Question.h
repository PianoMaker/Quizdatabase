#pragma once
#include"global.h"
#include <algorithm>
#include <random>
#include "Category.h"
class Question
{
private:

	int nrofanswers;
	string question;
	string* answers;
	string category;
	Category* categories;

public:
	Question(Category *categories) : nrofanswers(0), categories(categories)
	{
		answers = new string[nrofanswers];
		AddQuestion();
	}

	Question(int nrofanswers) : nrofanswers(nrofanswers)
	{
		answers = new string[nrofanswers];
	}
	Question(const Question& obj)
	{
		nrofanswers = obj.nrofanswers;
		question = obj.question;
		for (int i = 0; i < nrofanswers; i++)
			answers[i] = obj.nrofanswers;
	}
	Question operator = (Question obj)
	{
		nrofanswers = obj.nrofanswers;
		question = obj.question;
		for (int i = 0; i < nrofanswers; i++)
			answers[i] = obj.nrofanswers;
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
	void AddQuestion()
	{
		WelcomeMessage("Enter question\n");
		//CINIGNORE;
		getline(cin, question);
	}
	void AddCorrectAnswer()
	{
		WelcomeMessage("Enter correct answer");
		//CINIGNORE;
		getline(cin, answers[0]);
	}
	void AddIncorrectAnswer()
	{
		string ans;
		WelcomeMessage("Enter correct answer");
		getline(cin, ans);
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
	string GetCorrectAnswer()
	{
		return answers[0];
	}
	void ShowProperly()
	{
		for (int i = 0; i < nrofanswers; i++)
			cout << answers[i] << endl;
	}
	bool MakeQuiz()
	{
		int clue;
		string* temp = new string[nrofanswers];
		for (int i = 0; i < nrofanswers; i++)
			temp[i] = answers[i];
		shuffle(temp, temp + nrofanswers, default_random_engine(0));
		for (int i = 0; i < nrofanswers; i++)
			cout << temp[i];

		for (int i = 0; i < nrofanswers; i++)
			if (temp[i] == answers[i]) clue = i;

		WelcomeMessage("яка з в≥дпов≥дей правильна?");
		CINIGNORE;
		bool accept = true;
		do
		{
			string choice;
			getline(cin, choice);
			if (stoi(choice) < 1 || stoi(choice) > nrofanswers)
			{
				Message(14, "enter value between 0 and " + to_string(nrofanswers));
				accept = false;
			}
			else if (stoi(choice) == clue) return true;
		} while (!accept);

		return false;
	}
	~Question()
	{
		delete[] answers;
	}
};

