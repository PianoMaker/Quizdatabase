#include"global.h"


class Menues
{
	
public:
	void Show (int role, string login)
	{
		
		system("cls");
		Header();
		if (role != unlogged) GrayMessage("\nYou are logged as "); GrayMessage(login);
		/* вигляд меню для різних груп користувачів */
		if (role == unlogged)
			cout << "\n1 - login, 2 - signup, 0 - exit";
		else if (role == student)
			cout << "\n3 - log out, 5 - take quiz, 0 - exit";
		else if (role == admin)
			cout << "\n3 - log out, 4 - show database, 6 - write; 7 - read; 0 - exit";
		cout << endl;
	}
	int choice(int role)
	{
		/* вибір меню */
		do
		{
			string txt; 
			CINIGNORE;
			
			getline(cin, txt);

			if (txt == "0" || txt == "e") return 0;
			else if (role == unlogged && (txt == "1" || txt == "l" || txt == "L")) return 1;
			else if (role == unlogged && (txt == "2" || txt == "s" || txt == "S")) return 2;
			else if (role != unlogged && (txt == "3" || txt == "l" || txt == "L")) return 3;
			else if (role == admin && txt == "4") return 4;
			else if (role == student && (txt == "5" || txt == "q" || txt == "Q")) return 5;
			else if (role == admin && txt == "6") return 6;
			else if (role == admin && txt == "7") return 7;
			else if (txt == "8") return 4; // секретний
			else Message(12, "This choice is impossible, try once more\n");
		} while (true);

	}


};