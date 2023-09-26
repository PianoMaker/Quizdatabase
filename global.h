// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <windows.h>
#include <sstream> 
#include <iomanip>

#define CINIGNORE if(cin.peek() == '\n') cin.ignore();
using namespace std;


const int magicvalue = 5; // ������� ����� �������� ������, �� ������� ���� ��� �����


/* ������ ����������� 
- �������, �����������, ��������������� */
enum role { student, admin, unlogged }; 

void Color(int color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void Header()
{
	/*�����*/
	Color(10);
	cout << setw(50) << setfill('-') << "" << endl;
	Color(11);
	cout << "������� ������� �� ������� ��� 2024!\n";
	Color(10);
	cout << setw(50) << setfill('-') << "" << endl;
	Color(7);
}

bool choice(string text1, string text2)
{
	/*���� �� ���� �����������*/
	string choice;
	do {
		cout << "\n����: 1 - " << text1 << ", 2 - " << text2 << endl;
		CINIGNORE;
		getline(cin, choice);
		if (choice == "1") return true;
		else if (choice == "2") return false;
	} while (true);
}

int choiceM(string text)
{
	/*���� �� �������� �����������*/
	int choice;
	do {
		cout << text << endl;
		cin >> choice;
		if (choice >= 0) return choice;

	} while (true);
}

char XOR(char ch, int clue)
{
    /* ���������� */
	return ch ^ clue;
}

string XOR(string str, int clue)
{
	string codedstr;
	char *temp = new char[str.length() + 1];
	for (int i = 0; i < str.length(); i++)
		temp[i] = XOR(str[i], clue);
	temp[str.length()] = '\0';
	codedstr = string(temp);
	delete[] temp;
	return codedstr;
}
