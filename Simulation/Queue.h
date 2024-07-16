#pragma once
#include <iostream>

struct Job
{
	char jobType;
	int overallJobNum;
	int jobTypeNum;
	int arrivalTime;
	int processingTime;
	int timeEntersQueue, timeExitsQueue;

	void printJob()
	{
		std::cout << "Job Type: " << jobType;
		std::cout << " JobTypeNum: " << jobTypeNum << " Overall Job Num: " << overallJobNum;
		std::cout << "\nArrivalTime: " << arrivalTime << "\nProcessing Time: " << processingTime;
	}

};

struct Node
{
	Job jobData;
	Node* next;
};

class Queue {

private:
	Node* head = nullptr;


public:
	Job getFirstJobInQueue();
	void enqueue(Job& oneJob);
	void dequeue();
	bool isEmpty();
	int countQueue();
	void printQueue();

};
