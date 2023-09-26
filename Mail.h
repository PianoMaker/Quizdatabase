#pragma once
#include "Global.h"
#include "messages.h"


/*е-пошта*/
class Mail
{
private:
	string mail;
	MultiMessage message;
public:
	void SetMail(string txt)
	{
		mail = txt;
	}
	string GetMail()
	{
		return mail;
	}

	void Insert()
	{
		WelcomeMessage("Enter mail\n");
		string temp;
		getline(cin, temp);
		if (!CheckMail(temp)) Insert();
		else SetMail(temp);
	}

	bool CheckMail(string temp) // перевірка пошти
	{
		message.Refresh();
		int size = temp.length();

		int atcount = 0, atposition = 0, dotposition = -1, tempposition = 0, underscoreposition = -1, hyphenposition = -1;

		for (int i = 0; i < size; i++)//пробіли та нелатинські літeри 
		{
			if (temp[i] < 33 || temp[i] > 126)  message.Add("forbidden chars");
		}
		for (int i = 0; i < size; i++)//равлик
			if (temp[i] == '@') {
				atcount++;
				atposition = i;
			}
		if (atcount != 1 || atposition < 3 || atposition > 64 || size - atposition < 3) message.Add("incorrect \"@\" use");
		for (int i = 0; i < size; i++)//крапки
			if (temp[i] == '.') {
				dotposition = i;
				if (dotposition == 0 || size - dotposition < 3 || dotposition - atposition == 1
					|| dotposition - atposition == -1 || dotposition - tempposition < 3) message.Add("incorrect use of dots");
				tempposition = i;
			}
		for (int i = atposition + 1; i < size; i++)//доменне ім’я (після равлика)
			if (isalnum(temp[i]) == false && temp[i] != '-' && temp[i] != '.')  message.Add("incorrect domain name");
		if (dotposition < atposition)
		{
			message.Add("incorrect domain name");//обов'язкова наявність крапки в доменному імені
		}
		for (int i = atposition + 1; i < size; i++)//положення дефіса
			if (temp[i] == '-') hyphenposition = i;
		if (hyphenposition - atposition == 1 || hyphenposition == size - 1) message.Add("incorrect use of hyphens");

		if (temp[dotposition + 1] == 'r' && temp[dotposition + 2] == 'u' && temp[dotposition + 3] == '\0') // 
		{
			message.Add("We don't work with users from this country");
		}
		message.Show();
		return message.Accept();
	}
};