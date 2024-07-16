#pragma once
#include <iostream>
#include "Queue.h"

class Processor
{
private:
	int id = 0;
	int idleTime = 0;
	int runTime = 0;
	int timeRemaining = 0;
	int individualProcessingTime = 0;
	Job currentJob;
	bool isBusy;



public:
	Processor();
	void setIsBusy(bool isBusy);
	bool getIsBusy();
	int getId();
	void setId(int id1);

	int getRuntimeOrIdletime();
	void incrementRunTime();
	void incrementIdleTime();
	void restartRunTimeAndIdleTime();
	void incrementIndividualProcessingTime();
	int getIndividualProcessingTime();
	void restartIndividualProcessingTime();

	void setCurrentJob(Job aJob);
	Job getCurrentJob();



};
