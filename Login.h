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
		WelcomeMessage("Enter login\n");
		string temp;
		CINIGNORE;
		getline(cin, temp);
		if (!CheckLogin(temp)) Insert();
		SetLogin(temp);
	}
	
	bool CheckLogin(string temp)
	{
		if (temp.length() < 5)
		{
			Message(14,"Login must contain at least 5 symbols\n");
			return false;
		}
		else return true;
	}




	
};

