// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

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
		Message(gray,"+c");
		//Read();
	};
	void AddCat(string txt)
	{
		categories.push_back(txt);
		
	}
	string GetCat(int num)
	{
		return categories[num];
	}
	/* �� ������� �� ����� */
	void ShowAll()
	{
		for (int i=0; i<categories.size(); i++)
		{
			Color(8);
			cout << i << " " << GetCat(i) << "; ";
		}
	};
	/* �� ��� ���� �������� � ����� ������ */
	bool IfMatch(string txt)
	{
		for (int i = 0; i < categories.size(); i++)
			if (categories[i] == txt)
				return true;
		return false;
	}
	/* ������� �� ����������� ���� � ���� ��� ����.������� �� ���������� */
	bool IfEligible(string txt)
	{
		for (int i = 0; i < txt.size(); i++)
			if (isalpha(txt[i])) return true;
		return false;
	}
	/* ��� ������� ������� */
	string EnterCat()
	{
		int num = 0;
		Message(green,"������ ��������\n");
		Message(7, "������ � ��������:\n");
		ShowAll();
		Message(7, "��� ������ ����� ���� �������\n");
		while (true)
		{
			string choice;
			getline(cin, choice);
			if (IfMatch(choice))
				return choice;
			/*try
			{
				if (stoi(choice) > 0 && (stoi(choice) < categories.size()))
					return categories[stoi(choice)];
			}
			catch (...)
			{
				
			}*/
			AddCat(choice); 
			cout << "choice = " << choice << endl;
			return choice;
		}
		
	}
	//void Write()
	//{}
	//;
	//void Read()
	//{};

};