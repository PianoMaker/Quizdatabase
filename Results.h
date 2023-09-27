#pragma once
#include"global.h"
class Results
{
private:
	int questionnr;
	bool ifcorrect;
public:
	Results() {};
	Results(int questionnr, bool ifcorrect) : questionnr(questionnr), ifcorrect(ifcorrect) {};
	void Show()
	{
		cout << questionnr;
		if (ifcorrect) cout << " +"; else cout << " -";
	}
	bool GetResult() { return ifcorrect; }
};

