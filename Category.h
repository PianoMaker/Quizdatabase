#pragma once
#include "global.h"
#include"messages.h"
class Category
{
private:
	vector<string> categories;
	string categoryfile;
	ifstream read;
	ofstream write;
public:
	Category(string categoryfile) : categoryfile(categoryfile)
	{
		Read();
	};
	void AddCat(string txt)
	{
		categories.push_back(txt);
		Write();
	}
	string GetCat(int num)
	{
		return categories[num];
	}
	void ShowAll()
	{
		for (string i : categories)
		{
			Color(8);
			cout << i << " ";
		}
	};
	bool IfMatch(string txt)
	{
		for (int i = 0; i < categories.size(); i++)
			if (categories[i] == txt)
					return true;
		return false;
	}
	bool IfEligible(string txt)
	{
		for (int i = 0; i < txt.size(); i++)
			if (isalpha(txt[i])) return true;
		return false;
	}
	string EnterCat()
	{
		int num = 0;
		WelcomeMessage("Вкажіть категорію\n");
		Message(7, "оберіть з існуючих:\n");
		ShowAll();
		Message(7, "або введіть назву нової категорії\n");
		while (true)
		{
			string choice;
			getline(cin, choice);
			if (IfMatch(choice))
				return choice;
			else if (stoi(choice) > 0 && (stoi(choice) < categories.size())) 
				return categories[stoi(choice)];
			else if (IfEligible(choice))
			{
				AddCat(choice); return choice;
			}
			else ErrorMessage("у назві категорії мають бути літери, спробуйте ще раз\n");
		}
	}
	void Write()
	{}
	;
	void Read()
	{};

};