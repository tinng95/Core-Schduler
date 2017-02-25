#include "Instruction.h"


Instruction::Instruction(string instruction, int data)
{
	this->instruction = instruction;
	this->data = data;
}
Instruction::Instruction()
{
}


Instruction::~Instruction()
{
	
}

void Instruction::setInstruction(string instruction)
{
	this->instruction = instruction;
}

void Instruction::setData(int data)
{
	this->data = data;
}

string Instruction::getInstruction()
{
	return instruction;
}

int Instruction::getData()
{
	return data;
}
