#pragma once
#include"global.h"

/*��������� �����������*/
void Message(int color, string txt)
{

	Color(color);
	cout << txt;
	Color(7);
}



/* ����������� ��� ������ ������� �� ��� ����������� ��������� ���� */
class MultiMessage
{
private:
	bool accept;
	string message;
public:

	MultiMessage()
	{
		accept = true;
		message = "";
	}
	/* �������� ����������� ��� ������� */
	void Add(string message)
	{
		accept = false;
		this->message.append("\n\t- ").append(message);
	}
	/* �������� �� ������� �� ����� (���� ��������) */
	void Show()
	{
		if (!accept) {
			Message(red,"Errors found:\n");
			cout << message;
			Message(6, "\nTry again\n");
		}
	}
	/* � ��� ���������� ����� ��������� ������� */
	void Refresh()
	{
		accept = true;
		message.erase();
		message = "Errors found: ";
	}
	bool Accept()
	{
		return accept;
	}
};