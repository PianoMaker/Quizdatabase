#pragma once
#include "global.h"
#include "Question.h"


class Quizbase
{
	int role; // адмін/студент
	string filename;
	vector<Question> questions;
	Category* categories; // список категорій питань
	int lastID; // ID останнього питання в базі
	ifstream read;
	ofstream write;

public:
	Quizbase(string filename, Category* categories) : filename(filename), categories(categories)
	{
		/* Під час ініціалізації системи БД зчитується з файлу */
		Read();
		Sleep(500);
		cout << "\nініціалізували банк питань за адресою файлу " << filename;
		Sleep(500);
	}
	int GetNrOfQuestions()
	{
		return questions.size();
	}
	/* додати питання */
	void Add()
	{
		/* викликається з Quiz -> AdminQuiz */
		Question newquestion(categories); // створення питання - через конструктор
		questions.push_back(newquestion);
		questions[questions.size() - 1].SetID(lastID + 1);
		lastID++;
		Write();			// запис до БД //
	}
	void DeleteMenu()
	{
		/* викликається з Quiz -> AdminQuiz */
		{
			int index = choiceM("яке питання видалити?\n");
			Delete(index - 1); 
		}
	}

	void Delete(int index)
	{
		questions.erase(questions.begin() + index);
	}


	/* редагувати питання з відповідями */
	void Edit()
	{
		for (int i = 0; i < questions.size(); i++)
			cout << i + 1 << " " << questions[i].GetQuestion() << endl;
		int num;
		Message(green, "Введіть номер питання, яке слід відредагувати\n");
		while (true)
		{
			cin.clear();
			cin.ignore();
			cin >> num;
			if (cin.fail() || num<1 || num > questions.size())
				Message(red, "некоректний номер\n");
			else break;
		}
		
		questions[num - 1].EditQuestion();

		Message(yellow, "Правильна відповідь:\n");
		cout << questions[num - 1].GetCorrectAnswer();
		Message(green, "\nВведіть правильну відповідь\n");
		questions[num - 1].EditCorrectAnswer();
		Message(green, "Переглянути неправильні відповіді?\n");
		int choice;
		do
		{
			int nrofanswer;
			choice = choiceM("1 - переглянути, 2 - редагувати, 3 - видалити, 4 - додати ще, 0 - повернутись до меню");
			switch (choice)
			{
			case 1:
				for (int i = 1; i < questions[num - 1].GetNrOfAnswers(); i++)
					cout << i << " " << questions[num - 1].GetCustomAnswer(i) << endl;
				break;
			case 2:
				
				Message(green, "Введіть номер відповіді, яку слід відредагувати\n");
				while (true)
				{
					cin.clear();
					cin.ignore();
					cin >> nrofanswer;
					if (cin.fail() || nrofanswer<1 || nrofanswer >= questions[num - 1].GetNrOfAnswers())
						Message(red, "некоректний номер\n");
					else break;
				}
				questions[num - 1].EditCustomAnswer(nrofanswer);
				Message(gray, "\nвідповідь відредаговано\n");
				break;
			case 3:
				Message(green, "Введіть номер відповіді, яку слід видалити\n");
				while (true)
				{
					cin.clear();
					cin.ignore();
					cin >> nrofanswer;
					if (cin.fail() || nrofanswer<1 || nrofanswer >= questions[num - 1].GetNrOfAnswers())
						Message(red, "некоректний номер\n");
					else break;
				}
				questions[num - 1].DeleteIncorrectAnswer(nrofanswer);
				Message(gray, "\nвідповідь видалено");
				break;
			case 4:
				questions[num - 1].AddIncorrectAnswer(); break;
			case 0: return;
			default: cout << "некоректний вибір\n"; break;

			}


		} while (choice);



		Write();			//...//
	}

	void Show()
	{
		cout << "усього питань: " << questions.size() << endl;
		for (int i = 0; i < questions.size(); i++)
		{
			Message(green, to_string(i + 1) + ". ");
			questions[i].ShowProperly();
		}
		int choice = (choiceM("1 - додати питання, 2 - редагувати питання, 3-видалити питання, 0 - назад до меню"));
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
		if (choice("додати питання", "назад до меню")) Add();
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
		/* запис БД у файл */
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
			if (token != "QUESTION ") break;//починає роботу з рядку, що починається словом QUESTION, інше ігнорує
			getline(iss, token, '&');//після цього знаку - назва катеорії
			ID = stoi(token);
			getline(iss, token, '\n');
			category = token;
			getline(read, token, '\n');
			question = token;
			// вичитуємо відповіді і рахуємо скільки їх
			while (true)
			{
				getline(read, token, '\n');
				if (token == "[end]") break;
				answers.push_back(token);
				num = answers.size();
			}
			Question newquestion(num, categories, question, answers, category, ID);
			questions.push_back(newquestion);
			lastID = ID;//встановлюємо ID останнього квесту
		}

	}

};

