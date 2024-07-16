#include "Simulation.h"
#include "Queue.h"
#include "Processor.h"
#include <iostream>

void Simulation::initalizeProcessors()
{
	int choice, id = 0;
	std::cout << "\nPlease enter number of processors: ";
	std::cin >> choice;

	for (int i = 0; i < choice; i++)
	{
		id++;
		Processor oneProcessor;
		oneProcessor.setId(id);
		allProcessors.push_back(oneProcessor);
	}
}

void Simulation::updateBusy(int clock) //updating if the processors are processing something
{
	for (Processor& oneProcessor : allProcessors)
	{
		if (higherPriorityQueue.isEmpty() && waitingQueue.isEmpty() && normalQueue.isEmpty()
			&& (oneProcessor.getCurrentJob().arrivalTime == 0 || oneProcessor.getCurrentJob().arrivalTime == -1))
		{
			oneProcessor.setIsBusy(false);
		}

		else
		{
			oneProcessor.setIsBusy(true);
		}
	}

}

void Simulation::updateIdleOrRunTime(int clock) //updating the run time or idle time
{
	for (Processor& oneProcessor : allProcessors)
	{
		if (oneProcessor.getIsBusy())
		{
			oneProcessor.incrementRunTime();
			oneProcessor.incrementIndividualProcessingTime();
			totalTimeProcessing++;			
		}

		else
		{
			oneProcessor.incrementIdleTime();
			totalTimeIdle++;
		}
	}

}

void Simulation::processJob(Job jobArrived, int clock, std::ofstream& logFile) //if a job arrived
{
	if (clock == jobArrived.arrivalTime)
	{
		overallJobNum++;
		jobArrived.overallJobNum = overallJobNum;

		if (jobArrived.jobType == 'A')
		{
			totalA++;
			jobArrived.jobTypeNum = totalA;
		}

		else if (jobArrived.jobType == 'B')
		{
			totalB++;
			jobArrived.jobTypeNum = totalB;
		}

		else if (jobArrived.jobType == 'C')
		{
			totalC++;
			jobArrived.jobTypeNum = totalC;
		}


		else if (jobArrived.jobType == 'D')
		{
			totalD++;
			jobArrived.jobTypeNum = totalD;
		}


		logFile << "\nTime: " << clock << "- Arrival:  Overall Job: " << jobArrived.overallJobNum <<
			", Job " << jobArrived.jobType << ": " << jobArrived.jobTypeNum << " Processing Time: " <<
			jobArrived.processingTime;

		for (Processor& oneProcessor : allProcessors) //if processors aren't busy have it working on a job that arrived
		{
			if (!oneProcessor.getIsBusy())
			{
				oneProcessor.setCurrentJob(jobArrived);
				oneProcessor.restartIndividualProcessingTime();
				oneProcessor.restartRunTimeAndIdleTime();
				oneProcessor.setIsBusy(true);

				logFile << "\nTime: " << clock << "- Begin Processing Job: " << oneProcessor.getCurrentJob().overallJobNum <<
					", Job " << oneProcessor.getCurrentJob().jobType << ": " << oneProcessor.getCurrentJob().jobTypeNum <<
					" in CPU " << oneProcessor.getId();
				return; //exit out of function
			}
		}

		for (Processor& oneProcessor : allProcessors) //if all the processors are busy
		{
			if (oneProcessor.getIsBusy() && jobArrived.jobType == 'D' && //if job arrived is D, interrupt the current job and have the processor process the D job instead and also keeping track of how much it processed
				oneProcessor.getCurrentJob().jobType != 'D')
			{
				Job currentJob1 = oneProcessor.getCurrentJob();
				currentJob1.processingTime = currentJob1.processingTime - oneProcessor.getIndividualProcessingTime();
			

				waitingQueue.enqueue(currentJob1);
						

				//		std::cout << "\n\nNew Processing Time: " << currentJob1.processingTime << " Jobtype: " << 
					//		currentJob1.jobType;

				oneProcessor.setCurrentJob(jobArrived);
				oneProcessor.restartIndividualProcessingTime();
				oneProcessor.restartRunTimeAndIdleTime();
				oneProcessor.setIsBusy(true);

				logFile << "\nTime: " << clock << "- Begin Processing Job: " << oneProcessor.getCurrentJob().overallJobNum <<
					", Job " << oneProcessor.getCurrentJob().jobType << ": " << oneProcessor.getCurrentJob().jobTypeNum << " in CPU " << oneProcessor.getId();
				//	std::cout << "\n\nGet individula processing time: " << oneProcessor.getIndividualProcessingTime();
				return;
			}

		}

		for (Processor& oneProcessor : allProcessors) // if the current job is D, put the job that arrived in the higher priority queue
		{
			if (oneProcessor.getIsBusy() && jobArrived.jobType == 'D' &&
				oneProcessor.getCurrentJob().jobType == 'D')
			{
				higherPriorityQueue.enqueue(jobArrived);
				return;
			}

		}

		for (Processor& oneProcessor : allProcessors) //if the job that arrived isn't D, place it in the normal queue
		{
			if (oneProcessor.getIsBusy() && jobArrived.jobType != 'D')
			{
				normalQueue.enqueue(jobArrived);

				//	std::cout << "\nDid it get into the normal queue: ";
				return;
			}


		}

	}

}

void Simulation::checkJobFinished(int clock, std::ofstream& logFile)
{
	for (Processor& oneProcessor : allProcessors)
	{
		if (oneProcessor.getIndividualProcessingTime() == oneProcessor.getCurrentJob().processingTime
			&& oneProcessor.getCurrentJob().arrivalTime != -1 && oneProcessor.getCurrentJob().processingTime != 0) //if processor finished current job, restart the clock
		{
			logFile << "\nTime: " << clock << "- Complete Processing Job: " << oneProcessor.getCurrentJob().overallJobNum <<
				", Job " << oneProcessor.getCurrentJob().jobType << ": " << oneProcessor.getCurrentJob().jobTypeNum;
			oneProcessor.restartIndividualProcessingTime();
			oneProcessor.restartRunTimeAndIdleTime();

			if (oneProcessor.getCurrentJob().jobType == 'A')
				completedA++;
			else if (oneProcessor.getCurrentJob().jobType == 'B')
				completedB++;
			else if (oneProcessor.getCurrentJob().jobType == 'C')
				completedC++;
			else if (oneProcessor.getCurrentJob().jobType == 'D')
				completedD++;
		

			if (!higherPriorityQueue.isEmpty()) //if higher priority queue not empty pull that job to be processed
			{
				Job firstJobInQueue = higherPriorityQueue.getFirstJobInQueue();
				firstJobInQueue.timeExitsQueue = clock;
				oneProcessor.setCurrentJob(firstJobInQueue);
				oneProcessor.setIsBusy(true);


				logFile << "\nTime: " << clock << "- Begin Processing Job: " << oneProcessor.getCurrentJob().overallJobNum <<
					", Job " << oneProcessor.getCurrentJob().jobType << ": " << oneProcessor.getCurrentJob().jobTypeNum <<
					" in CPU " << oneProcessor.getId() << "   Total time job was in queue: ";

				higherPriorityQueue.dequeue();
			}

			else if (!waitingQueue.isEmpty()) // if the higher priority queue is empty, check the next queue which is the waiting queue
			{
				Job firstJobInQueue = waitingQueue.getFirstJobInQueue();
				firstJobInQueue.timeExitsQueue = clock;
				oneProcessor.setCurrentJob(firstJobInQueue);
				oneProcessor.setIsBusy(true);

			
				logFile << "\nTime: " << clock << "- Begin Processing Job: " << oneProcessor.getCurrentJob().overallJobNum <<
					", Job " << oneProcessor.getCurrentJob().jobType << ": " << oneProcessor.getCurrentJob().jobTypeNum <<
					" in CPU " << oneProcessor.getId() << "   Total time job was in queue: ";

				logFile << "\n\nProcessing time for waiting job " << oneProcessor.getCurrentJob().processingTime;

				waitingQueue.dequeue();			
			}

			else if (!normalQueue.isEmpty()) //if both the waiting queue and the priority queue is check the normal queue and process the job
			{
				Job firstJobInQueue = normalQueue.getFirstJobInQueue();
				firstJobInQueue.timeExitsQueue = clock;
				oneProcessor.setCurrentJob(firstJobInQueue);
				oneProcessor.setIsBusy(true);

				
				logFile << "\nTime: " << clock << "- Begin Processing Job: " << oneProcessor.getCurrentJob().overallJobNum <<
					", Job " << oneProcessor.getCurrentJob().jobType << ": " << oneProcessor.getCurrentJob().jobTypeNum <<
					" in CPU " << oneProcessor.getId() << "   Total time job was in queue: ";

				normalQueue.dequeue();						
			}

			else //if all the queues are empty set the processor to default which means it is not busy anymore
			{
				Job currentJob1 = { ' ', 0, 0, 0 };
				oneProcessor.setCurrentJob(currentJob1);
				oneProcessor.setIsBusy(false);
				//std::cout << "\n\n NOTBUSY Time: " << clock << " Begin Processing Job: " << oneProcessor.getCurrentJob().overallJobNum <<
				//	", Job " << oneProcessor.getCurrentJob().jobType << ": " << oneProcessor.getCurrentJob().jobTypeNum <<
				//	" in CPU " << oneProcessor.getId();
			}

		}
	}

}

int Simulation::countAllQueues()
{
	int total = higherPriorityQueue.countQueue() + waitingQueue.countQueue()
		+ normalQueue.countQueue();

	return total;
}

void Simulation::printSimulation(int clock1, std::ofstream& logFile)
{
	logFile << "\nTime: " << clock1 << "  Queue: ";

	if (countAllQueues() == 0)
		logFile << " Empty; ";
	else
		logFile << " " << countAllQueues();

	for (Processor& oneProcessor : allProcessors)
	{
		if (oneProcessor.getIsBusy())
		{
			logFile << " CPU " << oneProcessor.getId() << " Run Time : " << oneProcessor.getRuntimeOrIdletime();
			//	<< " Individual Processing Time: " << oneProcessor.getIndividualProcessingTime();
			//Job job = oneProcessor.getCurrentJob();
		   // job.printJob();
		}
		else
			logFile << " CPU " << oneProcessor.getId() << " Idle Time : " << oneProcessor.getRuntimeOrIdletime();
	}

	logFile << "\n\n";
}

void Simulation::updateMetrics(int clock)
{
	if (maxJobsInQueue < countAllQueues())
		maxJobsInQueue = countAllQueues();


	totalQueueSize += countAllQueues();

}

void Simulation::outputMetrics(int clock)
{
	if (clock == 550 || clock == 10000)
	{
		std::cout << "\nMetrics at Time: " << clock
			<< "\n\n\nNumber of processor(s) being used: " << allProcessors.size()
			<< "\nCurrent queue size: " << countAllQueues()
			<< "\nAverage queue size: " << totalQueueSize / clock

			<< "\nMaximum jobs in queue: " << maxJobsInQueue
			

			<< "\nTotal number of A jobs arrived: " << totalA
			<< "\nTotal number of A jobs completed: " << completedA
			<< "\nTotal number of B jobs arrived: " << totalB
			<< "\nTotal number of B jobs completed: " << completedB
			<< "\nTotal number of C jobs arrived: " << totalC
			<< "\nTotal number of C jobs completed: " << completedC
			<< "\nTotal number of D jobs arrived: " << totalD
			<< "\nTotal number of D jobs completed: " << completedD
			<< "\nTotal jobs completed: " << completedA + completedB + completedC + completedD

			<< "\nTotal time CPU(s) were processing: " << totalTimeProcessing
			<< "\nTotal time CPU(s) were idle: " << totalTimeIdle << "\n\n\n";

	}


}