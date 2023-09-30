#pragma once
#include"Global.h"
#include "messages.h"

using namespace std;

class Phone
{
private:
	string phone;
	MultiMessage message;
public:
	void InsertPhone()
	{
		Message(green,"Enter phone\n");
		string temp;
		getline(cin, temp);
		if (!CheckPhone(temp)) InsertPhone();
		else SetPhone(temp);
	}
	void SetPhone(string txt)
	{
		phone = txt;
	}
	string GetPhone()
	{
		return phone;
	}

	bool CheckPhone(string temp) // �������� ��������
		//�������������� ������ - ������� ���� �� 5 �� 15, ��������� +, -, �����. 
		// ��� ��������� ������� - �������� ���� (isdigit(phone[i]) == false))
	{
		message.Refresh();
		int size = temp.length(); 
		int limit = 0;
		for (int i = 0; i < size; i++)
			if (isdigit(temp[i]) == false && temp[i] != '+' && temp[i] != '-' && temp[i] != ' ' && temp[i] != '(' && temp[i] != ')')
				message.Add("unexpected symbols");
		for (int i = 1; i < size; i++) // "+" �������� ���� �� �������
			if ((temp[i]) == '+')
				message.Add("unexpected +");
	
		for (int i = 0; i < size; i++) // ���� �������� �����
		{
			if (temp[i] == '(') limit++;
			if (limit > 1) message.Add("too many brackets");
		}
		limit = 0;
		for (int i = 0; i < size; i++)
		{
			if (temp[i] == ')') limit++;
			if (limit > 1) message.Add("too many brackets");
		}
		int tempposition = 0;
		for (int i = 0; i < size; i++)//���� ����� ����� ������
		{
			int bracketposition = 0;
			if (temp[i] == ')' || temp[i] == '(')
			{
				bracketposition = i;
				if (bracketposition - tempposition == 1 && tempposition > 0) message.Add("incorrect brackets");
				tempposition = i;
			}

			if (limit > 1) message.Add("incorrect brackets");
		}
		// ���� ���� ����� 5 �� ����� 15
		int digit = 0;
		for (int i = 0; i < size; i++)
			if (isdigit(temp[i])) digit++; // �������� ������� ����
		if (digit < 5) message.Add("too few digits");
		else if (digit > 15) message.Add("too many digits");

		message.Show();
		return message.Accept();
	}
};



