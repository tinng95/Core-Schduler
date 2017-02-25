#pragma once
#include <iostream>
#include <vector>
#include "Instruction.h"

using namespace std;
class Process
{
public:
	Process();
	Process(int coreID, int startTime, vector<Instruction> instructions);
	Instruction* getCurrentCommand();

	void addCounter();
	void minusCounter();
	
	bool getIsComplete();
	int getStartTime();
	int getCoreID();
private:
	int counter = 0;
	int coreID = 0;
	int startTime = 0;
	vector<Instruction> instructions;
};
