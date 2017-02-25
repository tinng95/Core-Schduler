#include "Core.h"



Core::Core()
{
}

Core::Core(int startTime)
{
	this->SLICE = startTime;
	isBusy = false;
}


Core::~Core()
{
}

void Core::setFinishTime(int time)
{
	finishTime = time;
}

void Core::setSLICE(int slice)
{
	SLICE = slice;
}

void Core::setIsBusy(bool isBusy)
{
	this->isBusy = isBusy;
}

void Core::setProcess(Process * currentProcess)
{
	this->currentProcess = currentProcess;
}

int Core::getSLICE()
{
	return SLICE;
}

int Core::getFinishTime()
{
	return finishTime;
}

bool Core::getIsBusy()
{
	return isBusy;
}

Process * Core::getProcess()
{
	return currentProcess;
}
