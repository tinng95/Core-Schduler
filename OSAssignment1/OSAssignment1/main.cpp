#include <iostream>
#include <string.h>
#include <string>
#include <list>
#include <vector>
#include "Disk.h"
#include "Core.h"
#include "Instruction.h"
#include "IODisplay.h"
#include "Process.h"
using namespace std;

void diskProgess(Disk* disk, list<Process*>* diskQ, int &clock, list<Process*>* readyQ);
void start(int NCore, int SLICE, vector<Process> processes);

int main(int argc, char** argv) {
	int NCore = 0;
	int SLICE = 0;
	string tempstring;
	int tempNum;
	cin >> tempstring;
	if (tempstring == "NCORES")
	{
		cin >> tempNum;
		NCore = tempNum;
	}
	else {
		cout << "Error Input of NCORE, system terimate!" << endl;
		return 0;
	}

	cin >> tempstring;
	if (tempstring == "SLICE")
	{
		cin >> tempNum;
		SLICE = tempNum;
	}
	else {
		cout << "Error Input of SLICE, system terimate!" << endl;
		return 0;
	}

	bool isProcessAvaliable = false;
	vector<Instruction> instructions;
	vector<Process> processes;
	int newTime;

	while (true)
	{
		cin >> tempstring;
		cin >> tempNum;


		if (tempstring == "CORE" || tempstring == "DISK" || tempstring == "DISPLAY" || tempstring == "INPUT")
		{
			instructions.push_back(Instruction(tempstring, tempNum));
		}
		else if (tempstring == "NEW")
		{
			if (isProcessAvaliable)
			{
				processes.push_back(Process(processes.size(), newTime, instructions));
			}
			newTime = tempNum;
			instructions.clear();
			isProcessAvaliable = true;
		}
		if (cin.eof())
		{
			processes.push_back(Process(processes.size(), newTime, instructions));
			break;
		}
	}


	start(NCore, SLICE, processes);
	return 0;
}

void diskProgess(Disk* disk, list<Process*>* diskQ, int &clock, list<Process*>* readyQ)
{
	if (diskQ->size() > 0)
	{
		disk->setCurrentProcess(diskQ->front());
		if (disk->getCurrentProcess()->getCurrentCommand()->getData() > 0)
		{
			diskQ->pop_front();
			disk->setIsBusy(true);
			disk->setFinishTime(clock + disk->getCurrentProcess()->getCurrentCommand()->getData());
		}

		else
		{
			diskQ->pop_front();
			disk->getCurrentProcess()->addCounter();
			if (!disk->getCurrentProcess()->getIsComplete())
			{
				readyQ->push_back(disk->getCurrentProcess());
				diskProgess(disk, diskQ, clock, readyQ);
			}
		}

	}
	else
	{
		disk->setIsBusy(false);
	}
}

void start(int NCore, int SLICE, vector<Process> processes) {
	vector<Core> cores;
	Disk disk;
	IODisplay io;
	int finishedCore = 0;
	int processesIndex = 0;

	int timer = 0;
	vector<Process*> processCount;
	list<Process*> readyQ;
	list<Process*> diskQ;

	for (int i = 0; i < NCore; i++)
	{
		cores.push_back(Core(SLICE));
	}

	while (true)
	{
		if (processesIndex < processes.size())
		{
			if (processes[processesIndex].getStartTime() == timer)
			{
				readyQ.push_back(&processes[processesIndex]);
				processCount.push_back(&processes[processesIndex]);
				processesIndex++;
			}
		}
		// Check if disk/IO free
		if (disk.getFinishTime() == timer && disk.getIsBusy())
		{
			// put back in readyQ
			disk.getCurrentProcess()->addCounter();
			readyQ.push_back(disk.getCurrentProcess());
			diskProgess(&disk, &diskQ, timer, &readyQ);
		}
		else if (!disk.getIsBusy())
		{
			diskProgess(&disk, &diskQ, timer, &readyQ);
		}

		// IO Process Check
		for (int i = 0; i < io.getFinishTime()->size(); i++)
		{
			if (io.getFinishTime()->at(i) == timer)
			{
				io.getCurrentProcesses()->at(i)->addCounter();
				if (!io.getCurrentProcesses()->at(i)->getIsComplete())
				{
					readyQ.push_back(io.getCurrentProcesses()->at(i));
				}

				// Reset the IO
				io.getCurrentProcesses()->erase(io.getCurrentProcesses()->begin() + i);
				io.getFinishTime()->erase(io.getFinishTime()->begin() + i);
				i--;
			}
		}

		// Update CORES
		for (int i = 0; i < cores.size(); i++)
		{
			if (cores[i].getFinishTime() == timer && cores[i].getIsBusy())
			{
				cores[i].getProcess()->addCounter();
				cores[i].setIsBusy(false);
				if (!cores[i].getProcess()->getIsComplete())
				{
					if (cores[i].getProcess()->getCurrentCommand()->getInstruction() == "DISK")
					{
						diskQ.push_back(cores[i].getProcess());
						if (!disk.getIsBusy())
						{
							diskProgess(&disk, &diskQ, timer, &readyQ);
						}
					}
					else if (cores[i].getProcess()->getCurrentCommand()->getInstruction() == "DISPLAY" || cores[i].getProcess()->getCurrentCommand()->getInstruction() == "INPUT")
					{
						io.getCurrentProcesses()->push_back(cores[i].getProcess());
						io.getFinishTime()->push_back(timer + cores[i].getProcess()->getCurrentCommand()->getData());
					}
					else
					{
						readyQ.push_back(cores[i].getProcess());
					}
				}
				//New process
				if (readyQ.size() > 0)
				{
					cores[i].setProcess(readyQ.front());
					if (cores[i].getProcess()->getCurrentCommand()->getData() > cores[i].getSLICE())
					{
						cores[i].setFinishTime(timer + SLICE);
						cores[i].getProcess()->getCurrentCommand()->setData(cores[i].getProcess()->getCurrentCommand()->getData() - SLICE);
						cores[i].getProcess()->minusCounter();
					}
					else
					{
						cores[i].setFinishTime(timer + cores[i].getProcess()->getCurrentCommand()->getData());
					}
					readyQ.pop_front();
					cores[i].setIsBusy(true);
				}
			}
			else if (!cores[i].getIsBusy())
			{
				if (readyQ.size() > 0)
				{
					cores[i].setProcess(readyQ.front());
					if (cores[i].getProcess()->getCurrentCommand()->getData() > cores[i].getSLICE())
					{
						cores[i].setFinishTime(timer + SLICE);
						cores[i].getProcess()->getCurrentCommand()->setData(cores[i].getProcess()->getCurrentCommand()->getData() - SLICE);
						cores[i].getProcess()->minusCounter();
					}
					else
					{
						cores[i].setFinishTime(timer + cores[i].getProcess()->getCurrentCommand()->getData());
					}

					readyQ.pop_front();
					cores[i].setIsBusy(true);
				}
			}
		}
		// Check completed Core
		for (int i = 0; i < processCount.size(); i++)
		{
			if (processCount[i]->getIsComplete())
			{
				// Core Check
				int busyCoreNum = 0;
				for (int i = 0; i < cores.size(); i++)
				{
					if (cores[i].getIsBusy())
					{
						busyCoreNum++;
					}
				}
				// Ready Check
				if (!readyQ.empty())
				{
					list<Process*> temp = readyQ;
					for (int i = 0; i < temp.size(); i++)
					{
						temp.pop_back();
					}
				}

				//Disk Check
				if (!diskQ.empty())
				{
					list<Process*> temp = diskQ;
					for (int i = 0; i < temp.size(); i++)
					{
						temp.pop_front();
					}
				}

				// ProcessOutPut
				cout << "Process completed at time: " << timer << "ms"<< endl;
				cout << "Current number of busy cores: " << busyCoreNum << endl;
				cout << "READY QUEUE: ";
				if (readyQ.empty())
				{
					cout << "Empty" << endl;
				}
				else {
					cout << readyQ.size() << endl;
				}
				cout << "DISK QUEUE: ";
				if (diskQ.empty())
				{
					cout << "Empty" << endl;
				}
				else {
					cout << diskQ.size() << endl;
				}
				int temp = 0;
				for (int i = 0; i < processCount.size(); i++) {

					cout << "Process " << i + finishedCore << " is started at " << processCount[i]->getStartTime() << "ms and is ";
					if (processCount[i]->getIsComplete()) {
						cout << "TERMINATED" << endl;
						temp++;
					}
					else if (processCount[i]->getCurrentCommand()->getInstruction() == "DISK" ||
						processCount[i]->getCurrentCommand()->getInstruction() == "INPUT" ||
						processCount[i]->getCurrentCommand()->getInstruction() == "DISPLAY") {
						cout << "BLOCKED" << endl;
					}
					else {
						cout << "RUNNING" << endl;
					}
				}
				finishedCore += temp;
				cout << endl << endl;
				processCount.erase(processCount.begin() + i);

			}
		}

		if (processCount.size() == 0)
		{
			break;
		}

		timer++;
	}

}
