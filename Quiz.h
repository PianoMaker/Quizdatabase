#pragma once
#include"global.h";
#include"Database.h"
#include"QuizBase.h"
#include"Results.h"




class Quiz
{
private:

	Database* database;
	Quizbase* quizbase;
	vector<Results> results;


public:
	Quiz(Database* database, Quizbase* quizbase) : database(database), quizbase(quizbase)
	{
		
	}
	/* меню для адміна (виклик із Profile) */
	void AdminQuiz()
	{
		while(true)
		{
			int choice = choiceM("1 - переглянути питання, 2 - додати питання, 3 - видалити питання, \
4 - випробувати тест, 0 - вийти з меню\n");
			switch (choice)
			{
			case 0: return;
			case 1: quizbase->Show(); break;
			case 2: quizbase->Add(); break;
			case 3: quizbase->DeleteMenu(); break;
			case 4: 
			{
				int progress = choiceM("з якого питання почати?\n");
				int QuestionID; //
				quizbase->GetQuestion()[progress].MakeQuiz(QuestionID); 
				progress++;
				break;
			}
			default: break;
			}	
		}		
	}
	/* меню для студента  (виклик із Profile) */ 
	void StudentQuiz(int &progress, vector<Results> &results)
	{
		Results newresult;
		while (true)
		{
			int choice = choiceM("1 - переглянути результати, 2 - пройти тестування, 0 - вихід з меню\n");
			switch (choice)
			{
			case 0: return;
			case 1: cout << "пройдено = " << progress << "питань\n"; Show(); break;
			case 2: if (progress < quizbase->GetNrOfQuestions())
			{
				int QuestionID;//ідентифікатор питання, передаємо з & і записуємо значення
				bool success = (quizbase->GetQuestion()[progress].MakeQuiz(QuestionID));
				newresult.SetResult(success);
				newresult.SetqID(QuestionID);
				results.push_back(newresult);//запис результату
				progress++;
				system("pause");
			}
			else cout << "усі питання пройдено!\n";
			break;
			default: Message(red,"невірний вибір, спробуйте ще раз\n"); return;
			}
		}

	}
	
	/* результати тестування */
	void Show()
	{
		for (int i = 0; i < results.size(); i++)
		{
			cout << "питання № " << i << endl;
			results[i].Show();
		}
		
	}



	void Save()
	{
		database->Write();
		Message(gray,"результати записано\n");
	}

};
