// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include"global.h"
#include"Profile.h"
using namespace std;


int main()
{
	setlocale(LC_ALL, "ukr"); // ��� ����������� ��������
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	srand(time(NULL) + clock());

	Header();
	const string datafile = "users.csv";
	const string quizfile = "quiz.csv";
	const string catfile = "categories.csv";
	try {
		Database database(datafile);
		Category categories(catfile);
		Quizbase quizbase(quizfile, &categories);
		
		Quiz quiz(&database, &quizbase);
		Profile profile(&database, &quiz);
		while (true)
		{
			profile.Menu();
			//system("Pause>0");

		}
	}
	catch (int e)
	{
		if (!e) Message(green,"\nThank you for using our program!\n");
		if (e == 1) cout << "Wrong choice";
		if (e == 2) cout << "To recover login or password please contact administrator\n";
	}
}
