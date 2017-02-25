#include "Disk.h"



Disk::Disk()
{
	currentProcess = NULL;
	finishTime = -1;
	isBusy = false;
}


Disk::~Disk()
{
}

void Disk::setCurrentProcess(Process *currentProcess)
{
	this->currentProcess = currentProcess;
}

void Disk::setFinishTime(int finishTime)
{
	this->finishTime = finishTime;
}

void Disk::setIsBusy(bool isBusy)
{
	this->isBusy = isBusy;
}

Process * Disk::getCurrentProcess()
{
	return currentProcess;
}

int Disk::getFinishTime()
{
	return finishTime;
}

bool Disk::getIsBusy()
{
	return isBusy;
}
