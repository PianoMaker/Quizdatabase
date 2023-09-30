#pragma once
#include"global.h"
class Results
{
private:
	int questionID;
	bool ifcorrect;
public:
	Results()
	{
		questionID = 0;
	}

	Results(string tempresnum, string tempresbool) 
	{
	// застосовується під час зчитування файлу (Quizbase -> Read)
		questionID = stoi(tempresnum);
		if (tempresbool == "+") ifcorrect = true;
		else ifcorrect = false;
	};
	Results(int questionID, bool ifcorrect) : questionID(questionID), ifcorrect(ifcorrect) {};
	void Show()
	{
		cout << questionID;
		if (ifcorrect) cout << " +"; else cout << " -";
	}
	
	bool IfSuccess () { return ifcorrect; }
	string GetString()
	{
		//підготовка до запису в файл
		string res;
		res.append(to_string(questionID)).append(":");
		if (ifcorrect) res.append("+");
		else res.append("-");
		return res;
	}
	int GetQID()
	{
		return questionID;
	}
	void SetqID(int num)
	{
		questionID = num;
	}
	void SetResult(bool ifsuccess)
	{
		ifcorrect = ifsuccess;
	}



};

