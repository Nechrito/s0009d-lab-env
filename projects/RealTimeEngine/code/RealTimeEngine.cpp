#include "config.h"
#include "Application.h"

#include "HardwareSpecs.h"

#include <stdio.h> 
#include <iostream>

using namespace std;

bool isInteger(const string& s)
{
   if(s.empty() || !isdigit(s[0]))
   	return false;

   char * p;
   strtol(s.c_str(), &p, 10);

   return (*p == 0);
}

int main(int argc, char** argv)
{
	if(argc == 1) 
    {
		printf("No arguments, running lightning program \n");

		Application app;
		if (app.Open())
		{
			app.Run();
		}
	}
    else 
    {
		HardwareSpecs specs;

		for(int i = 1; i < argc; i++)
		{
			auto argument = string(argv[i]);

			if (isInteger(argument))
			{
				continue;
			}

			// Print num processors, hostname, hardware platform & total amount of memory
			if (argument == "-i")
			{
				auto processors = specs.GetProcessors();
				printf("Processors: %d \n", processors);
			}

			// Fork an X amount of processes that each print out its PID, calculate the sum
			else if (argument == "-f")
			{
				int forkCount = atoi(argv[i + 1]);
    			cout << "Calculating sum on " << forkCount << " forks" << endl;
				specs.ForkSum(forkCount);
			}

			// Similar to -f but using threads instead of forks
			else if (argument == "-t")
			{
				int threadCount = atoi(argv[i + 1]);
    			cout << "Calculating sum on " << threadCount << " threads" << endl;
				specs.ThreadSum(threadCount);
			}
		} 
    }

	
}
