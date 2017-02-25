#pragma once
#include <iostream>
#include <vector>
#include "Process.h"
using namespace std;
class IODisplay
{
public:
	IODisplay();
	~IODisplay();
	void setCurrentProcesses(vector<Process*> currentProcesses);
	void setFinishTime(vector<int> finishTime);

	vector<Process*>* getCurrentProcesses();
	vector<int>* getFinishTime();
private:
	vector<Process*> currentProcesses;
	vector<int> finishTime;
};

