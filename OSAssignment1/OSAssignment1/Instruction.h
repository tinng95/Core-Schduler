#pragma once
#include <iostream>
#include <string.h>
using namespace std;
class Instruction
{
public:
	Instruction(string instruction, int data);
	Instruction();
	~Instruction();
	
	void setInstruction(string instruction);
	void setData(int data);

	string getInstruction();
	int getData();
private:
	string instruction;
	int data = 0;
};

