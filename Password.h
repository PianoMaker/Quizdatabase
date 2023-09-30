#pragma once
#include"global.h"
#include"Login.h"
#include "messages.h"

class Password
{
	string password;
	MultiMessage message;
public:
	void SetPassword(string txt)
	{
		password = txt;
	}
	string GetPassword()
	{
		return password;
	}

	/*встановлення паролю */
	void Insert(int &attempts)
	{
		if (!attempts) {
			Message(green,"\nInsert new password");
			cout << "\nminimum " << magicvalue << " symbols, at least 1 digit, 1 letter and 1 punch\n";
		}
		string temp;
		getline(cin, temp);
		attempts++;
		if (!CheckPassword(temp)) Insert(attempts);
		else SetPassword(temp);
	}

	bool CheckPassword(string temp)
	{
		message.Refresh();
		CheckSize(temp);
		CheckDigits(temp);
		CheckAlpha(temp);
		CheckNonAlpha(temp);
		message.Show();
		return message.Accept();
	}


	bool CheckSize(string temp)
	{
		if (temp.length() < magicvalue)
		{
			message.Add("Login must contain at least " + (to_string(magicvalue)) + " symbols");
			return false;
		}
		else return true;
	}
	bool CheckDigits(string temp)
	{
		for (int i = 0; i < temp.length(); i++)
		{
			if (isdigit(temp[i])) return true;
		}
		message.Add("Password must contain at least 1 digit");
		return false;		
	}
	bool CheckAlpha(string temp)
	{
		for (int i = 0; i < temp.length(); i++)
		{
			if (isalpha(temp[i])) return true;
		}
		message.Add("Password must contain at least 1 punch symbol");
		return false;
	}
	bool CheckNonAlpha(string temp)
	{
		for (int i = 0; i < temp.length(); i++)
		{
			if (ispunct(temp[i])) return true;
		}
		message.Add("Password must contain at least 1 non-letter symbol");
		return false;
	}


};

