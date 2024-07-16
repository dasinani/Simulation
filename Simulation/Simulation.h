#pragma once
#include <fstream>
#include "Queue.h"
#include "Processor.h"
#include <iostream>
#include <vector>

class Simulation
{
private:
	Queue higherPriorityQueue;
	Queue waitingQueue;
	Queue normalQueue;
	int totalA = 0, totalB = 0, totalC = 0, totalD = 0;
	int completedA = 0, completedB = 0, completedC = 0, completedD = 0;
	int overallJobNum = 0;
	int maxJobsInQueue = 0;
	int totalQueueSize = 0;
	int totalTimeJobsInQueue = 0, avgTimeJobsInQueue = 0;
	int totalTimeProcessing = 0, totalTimeIdle = 0;
	std::vector<Processor> allProcessors;


public:
	void initalizeProcessors();
	void updateBusy(int clock);
	void updateIdleOrRunTime(int clock);
	void processJob(Job jobArrived, int clock, std::ofstream& logFile);
	void checkJobFinished(int clock, std::ofstream& logFile);
	int countAllQueues();
	void printSimulation(int clock1, std::ofstream& logFile);
	void updateMetrics(int clock);
	void outputMetrics(int clock);

};
