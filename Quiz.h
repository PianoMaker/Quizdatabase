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
	/* ���� ��� ����� (������ �� Profile) */
	void AdminQuiz()
	{
		while(true)
		{
			int choice = choiceM("1 - ����������� �������, 2 - ������ �������, 3 - �������� �������, \
4 - ����������� ����, 0 - ����� � ����\n");
			switch (choice)
			{
			case 0: return;
			case 1: quizbase->Show(); break;
			case 2: quizbase->Add(); break;
			case 3: quizbase->DeleteMenu(); break;
			case 4: 
			{
				int progress = choiceM("� ����� ������� ������?\n");
				int QuestionID; //
				quizbase->GetQuestion()[progress].MakeQuiz(QuestionID); 
				progress++;
				break;
			}
			default: break;
			}	
		}		
	}
	/* ���� ��� ��������  (������ �� Profile) */ 
	void StudentQuiz(int &progress, vector<Results> &results)
	{
		Results newresult;
		while (true)
		{
			int choice = choiceM("1 - ����������� ����������, 2 - ������ ����������, 0 - ����� � ����\n");
			switch (choice)
			{
			case 0: return;
			case 1: cout << "�������� = " << progress << "������\n"; Show(); break;
			case 2: if (progress < quizbase->GetNrOfQuestions())
			{
				int QuestionID;//������������� �������, �������� � & � �������� ��������
				bool success = (quizbase->GetQuestion()[progress].MakeQuiz(QuestionID));
				newresult.SetResult(success);
				newresult.SetqID(QuestionID);
				results.push_back(newresult);//����� ����������
				progress++;
				system("pause");
			}
			else cout << "�� ������� ��������!\n";
			break;
			default: Message(red,"������� ����, ��������� �� ���\n"); return;
			}
		}

	}
	
	/* ���������� ���������� */
	void Show()
	{
		for (int i = 0; i < results.size(); i++)
		{
			cout << "������� � " << i << endl;
			results[i].Show();
		}
		
	}



	void Save()
	{
		database->Write();
		Message(gray,"���������� ��������\n");
	}

};
