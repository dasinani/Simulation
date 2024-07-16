Created a Queue class which uses linked lists to act like a queue. Created a Processor class which is responsible for updating the processors if it is busy or not and setting the id for each processor. 
It also sets the job for that specific processor. The last class called a Simulation creates three queues which are higher priority queue, then waiting queue, then normal queue. Tags each job that arrives with
an ID. Job type D is highest priority so if the current job being processed isn't D, it will kick the job out to start processing the job type D. The job that got interrupted will be in the waiting queue.
Jobs that aren't interrupted or job type D goes in the normal queue. If the current job being processed is job type D and another job type D arrives, then place the job in the higher priority queue. The class
also keeps track of the statistics. For the main file, it reads in a line from a file to get the job data. After running the program, the log file gets created to show the simulation.


RESULTS
At Time: 10,000
Number of processors   Current queue size   Total Jobs completed   Total Time CPU(s) were idle  Total Time CPU(s) were processing   Max Jobs in queue   
1                      4898                 856                    7                            9993                                4898                
2                      3862                 1891                   15                           19985                               3862                
3                      2335                 3417                   27                           29973                               2335                
4                      842                  4909                   45                           39955                               843                 
5                      1                    5749                   4626                         45374                               11 
6                      0                    5749                   14,626                       45,374                              6 
7                      0                    5749                   24,626                       45,374                              4 
8                      0                    5749                   34,626                       45,374                              2 

According to the table, the number of processors that are the most efficient is 5 processors. The current
queue size is very low and has the highest completed total jobs while the total time CPU(s) were idle is
the lowest. At processors more than five, The processors are processing the jobs way too fast and are
not working at a consistent speed where their full capabilities is being utilized. It is inefficient because
we are using processors, but they are not doing any work. Also, the total time CPU(s) were idle
dramatically increased going from number of processor 5 to 6. At processors less than five shows the
processors being overwhelmed with too many jobs. The current queue size is the highest meaning it
can’t get jobs done at an appropriate speed.
