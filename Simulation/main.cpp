#include <iostream>
#include <iomanip>
#include "Simulation.h"
#include "Processor.h"
#include "Queue.h"
#include <fstream>


int main()
{
	int clock = 0;
	Simulation simulation;

	simulation.initalizeProcessors();

	Job currentJob, nextJob;
	std::fstream file("queueLog.txt", std::ios::in);
	std::ofstream logFile("logFile.txt");

	file >> currentJob.jobType;
	file >> currentJob.arrivalTime;
	file >> currentJob.processingTime;

	//	CPU1.setCurrentJob(currentJob);


		//file >> nextJob.jobType;
		//file >> nextJob.arrivalTime;
		//file >> nextJob.processingTime;


	while (clock <= 10000)
	{
		clock++;
		simulation.updateBusy(clock);
		simulation.updateIdleOrRunTime(clock);
		simulation.checkJobFinished(clock, logFile);

		if (clock == currentJob.arrivalTime)
		{
			simulation.processJob(currentJob, clock, logFile);


			file >> currentJob.jobType;
			file >> currentJob.arrivalTime;
			file >> currentJob.processingTime;

			if (clock == currentJob.arrivalTime)
			{
				simulation.processJob(currentJob, clock, logFile);

				file >> currentJob.jobType;
				file >> currentJob.arrivalTime;
				file >> currentJob.processingTime;

				if (clock == currentJob.arrivalTime)
				{
					simulation.processJob(currentJob, clock, logFile);

					file >> currentJob.jobType;
					file >> currentJob.arrivalTime;
					file >> currentJob.processingTime;

					if (clock == currentJob.arrivalTime)
					{
						simulation.processJob(currentJob, clock, logFile);

						file >> currentJob.jobType;
						file >> currentJob.arrivalTime;
						file >> currentJob.processingTime;

					}


				}

			}

		}

		simulation.printSimulation(clock, logFile);
		simulation.updateMetrics(clock);
		simulation.outputMetrics(clock);
	

	}


	return 0;
}