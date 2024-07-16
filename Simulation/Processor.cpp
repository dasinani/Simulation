#include <iostream>
#include "Queue.h"
#include "Processor.h"

Processor::Processor()
{
	currentJob = { ' ', 0, 0, -1, 0 };
}


void Processor::setIsBusy(bool isBusy1) { isBusy = isBusy1; }

bool Processor::getIsBusy() { return isBusy; }

int Processor::getId() { return id; }

void Processor::setId(int id1) { id = id1; }

int Processor::getRuntimeOrIdletime()
{
	if (isBusy)
		return runTime;
	else
		return idleTime;
}

void Processor::incrementRunTime()
{
	runTime++;
}

void Processor::incrementIdleTime()
{
	idleTime++;
}

void Processor::restartRunTimeAndIdleTime()
{
	idleTime = 0;
	runTime = 0;
}

void Processor::incrementIndividualProcessingTime()
{
	individualProcessingTime++;
}

int Processor::getIndividualProcessingTime() { return individualProcessingTime; }

void Processor::restartIndividualProcessingTime()
{
	individualProcessingTime = 0;
}

void Processor::setCurrentJob(Job aJob) { currentJob = aJob; }

Job Processor::getCurrentJob() { return currentJob; }