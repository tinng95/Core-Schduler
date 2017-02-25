#include "IODisplay.h"



IODisplay::IODisplay()
{
}


IODisplay::~IODisplay()
{
}

void IODisplay::setFinishTime(vector<int> finishTime)
{
	this->finishTime = finishTime;
}

vector<Process*>* IODisplay::getCurrentProcesses()
{
	return &currentProcesses;
}

vector<int>* IODisplay::getFinishTime()
{
	return &finishTime;
}

void IODisplay::setCurrentProcesses(vector<Process*> currentProcesses)
{
	this->currentProcesses = currentProcesses;
}
