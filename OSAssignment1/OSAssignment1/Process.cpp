#include "Process.h"



Process::Process()
{
	coreID = 0;
	startTime = 0;
}

Process::Process(int coreID, int startTime, vector<Instruction> instructions)
{
	this->coreID = coreID;
	this->startTime = startTime;
	this->instructions = instructions;

	counter = 0;
}

Instruction * Process::getCurrentCommand()
{
	return &instructions[counter];
}

void Process::addCounter()
{
	counter++;
}

void Process::minusCounter()
{
	counter--;
}

bool Process::getIsComplete()
{
	return counter == instructions.size();
}

int Process::getStartTime()
{
	return startTime;
}

int Process::getCoreID()
{
	return coreID;
}



