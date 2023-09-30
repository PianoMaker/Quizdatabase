#pragma once
#include"global.h"

/*кольорове повідомлення*/
void Message(int color, string txt)
{

	Color(color);
	cout << txt;
	Color(7);
}



/* повідомлення для списку помилок під час генерування текстових полів */
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
	/* накопичує повідомлення про помилки */
	void Add(string message)
	{
		accept = false;
		this->message.append("\n\t- ").append(message);
	}
	/* виводить усі помилки на еркан (якщо виявлені) */
	void Show()
	{
		if (!accept) {
			Message(red,"Errors found:\n");
			cout << message;
			Message(6, "\nTry again\n");
		}
	}
	/* в разі повторного циклу необхідно оновити */
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