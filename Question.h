#pragma once
#include"global.h"
class Question
{
private:
	string filename;
	ifstream read;
	int nr;
	int clue;

	

public:
	Question(string filename, int nt) : filename(filename), nr(nr)
	{
		filename = "question_" + nr;
		cout << "\nініціалізували базу потоки за адресою файлу " << filename;
		Read();
	}
	void Read()
	{
		read.open(filename);
		if (!read) ErrorMessage("\nfile is inaccessible\n");
		else cout << "\nreading file\n";
		/*
		питання та ключ читаються з файлу, 
		*/
	}
	int Answer()
	{
		/*
		користувач обирає відповідь і отримує на виході оцінку
		*/
	}
	


};

