// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include "global.h"
#include"messages.h"

class Login
{
	string login;

public:

	void SetLogin(string txt)
	{
		login = txt;
	}
	string GetLogin()
	{
		return login;
	}

	void Insert()
	{
		Message(green,"Enter login\n");
		string temp;
		CINIGNORE;
		getline(cin, temp);
		if (temp != "-" && !CheckLogin(temp)) Insert();
		SetLogin(temp);
	}
	
	bool CheckLogin(string temp)
	{
		if (temp.length() < 5)
		{
			Message(yellow,"Login must contain at least 5 symbols\n");
			return false;
		}
		else return true;
	}




	
};

