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
		cout << "\n������������ ���� ������ �� ������� ����� " << filename;
		Read();
	}
	void Read()
	{
		read.open(filename);
		if (!read) ErrorMessage("\nfile is inaccessible\n");
		else cout << "\nreading file\n";
		/*
		������� �� ���� ��������� � �����, 
		*/
	}
	int Answer()
	{
		/*
		���������� ����� ������� � ������ �� ����� ������
		*/
	}
	


};

