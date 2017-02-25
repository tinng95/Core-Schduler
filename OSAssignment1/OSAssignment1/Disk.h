#pragma once
#include "Process.h"
class Disk
{
public:
	Disk();
	~Disk();

	void setCurrentProcess(Process *currentProcess);
	void setFinishTime(int finishTime);
	void setIsBusy(bool isBusy);

	Process* getCurrentProcess();
	int getFinishTime();
	bool getIsBusy();

private:
	Process* currentProcess = NULL;
	int finishTime = 0;
	bool isBusy = false;
};

