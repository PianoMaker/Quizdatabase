#pragma once
#include"global.h"
#include <algorithm>
#include <random>
#include "Category.h"
#define ENTER Message(gray, "Натисніть Enter, щоб лишити без змін\n");

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
	/* за замовченням виділено пам'ять для  1 правильної відповіді, наступі додаються в процесі */
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
		Message(green,"Введіть питання\n");
		CINIGNORE;
		getline(cin, question);
	}
	void AddCorrectAnswer()
	{
		Message(green,"Введіть правильну відповідь\n");
		CINIGNORE;
		getline(cin, answers[0]);
	}
	void AddIncorrectAnswer()
	{
		bool more;
		Message(green, "Введіть неправиьну відповідь\n");
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
		more = choice("Додати ще? 1 - Так", "2 - Ні\n");
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
			question = temp;// редагуємо лише коли рядок не порожній
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
			answers[0] = temp;// редагуємо лише коли рядок не порожній
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
			answers[nrofanswer] = temp;// редагуємо лише коли рядок не порожній
			Message(gray, "answer has been edited\n");
		}
	}
	


	/* питання з правильними відповідями на екран */
	void ShowProperly()
	{
		Message(green,question + "\n");
		Message(gray,"категорія: " + GetCategory() + ", ID: " +  to_string(GetID()) + "\n");
		for (int i = 0; i < nrofanswers; i++)
			cout << "\t-" << i + 1 << " " << answers[i] << endl;
	}
	/* тест */



	bool MakeQuiz(int &questionID)
	{
		questionID = ID;
		int clue = -1;
		Message(green,question + "\n");// питання на екран
		string* temp = new string[nrofanswers]; 
		for (int i = 0; i < nrofanswers; i++)
			temp[i] = answers[i];
		/* алгоримт перемішує відповіді у випадковому порядку */
		shuffle(temp, temp + nrofanswers, default_random_engine(rand()));
		/* варіанти відповідей на екран */
		for (int i = 0; i < nrofanswers; i++)
			cout << i << " - " << temp[i] << endl;
		/* пошук ключа опитування */
		for (int i = 0; i < nrofanswers; i++)
			if (temp[i] == answers[0]) clue = i;

		delete[] temp;
		Message(green,"\nЯка з відповідей правильна?\n");
		CINIGNORE;
		bool accept = true;
		do
		{
			int choice;
			cin >> choice;
			if (choice < 1 || choice > nrofanswers || cin.fail())
			{
				// якщо введено неіснуючий номер відповіді або випадковий символ  
				Message(yellow, "введіть значення між 0 і " + to_string(nrofanswers));
				accept = false;
			}
			else if (choice == clue)
			{
				Message(green,"success\n"); return true;
			}
			else if (clue == -1)
			{
				// якщо ключ опитування не було знайедно
				cout << "вибачте, помилка в опитуванні, зверніться до адміністратора\n";  return true;
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

