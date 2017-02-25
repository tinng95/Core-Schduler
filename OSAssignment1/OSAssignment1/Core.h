#pragma once
#include "Process.h"
class Core
{
public:
	Core();
	Core(int startTime);
	~Core();
	
	void setFinishTime(int time);
	void setSLICE(int slice);
	void setIsBusy(bool isBusy);
	void setProcess(Process * currentProcess);

	int getSLICE();
	int getFinishTime();
	bool getIsBusy();
	Process* getProcess();
private:
	int SLICE = 0;
	Process* currentProcess = NULL;
	int finishTime = 0;
	bool isBusy = false;
};

