// Copyright © 2020  Philip Lindh 
// All rights reserved

#include "HardwareSpecs.h"

#include <math.h>
#include "CMath.h"

#include <thread>
#include "sys/sysinfo.h"
#include "sys/utsname.h"
#include <sys/types.h>
#include <sys/wait.h>

#include <iostream>
using namespace std;

HardwareSpecs::HardwareSpecs() { }

HardwareSpecs::~HardwareSpecs() { }

int HardwareSpecs::GetProcessors() 
{
    return std::thread::hardware_concurrency();
}

void HardwareSpecs::ForkSum(int processes) 
{ 
    auto start = CMath::CurrentTime();

    for (int i = 0; i < processes; i++)
    {
        auto childpid = fork();
        if (childpid == 0)
        {
            auto temp = ComputeSum(1, threshold);

            cout << "[" << getpid() << "]" << " Sum: " << temp << " | Time Elapsed: " << CMath::TimeSince(start) << "s" << endl;

            sum = 0;

            exit(1);
        }
    }
}

void HardwareSpecs::ThreadSum(int threadCount) 
{
    auto start = CMath::CurrentTime();
    vector<thread> threads;

    for (int i = 0; i < threadCount; i++)
    {
        thread t = thread(&HardwareSpecs::ComputeSumStatic, 1, threshold);
        threads.push_back(move(t));
    }

    for (thread& t : threads)
    {
        if (t.joinable())
        {
            t.join();
        }
    }

}

unsigned long long int HardwareSpecs::ComputeSum(int start, int end) 
{
    unsigned long long int temp = 0;
    for (int i = start; i < end; ++i)
    {
        for (int j = 1; j < i; ++j)
        {
            temp += sqrt(i * j);
        }
    }
    return temp;
}

void HardwareSpecs::ComputeSumStatic(int start, int end) 
{
    unsigned long long int temp = 0;
    for (int i = start; i < end; ++i)
    {
        for (int j = 1; j < i; ++j)
        {
            temp += sqrt(i * j);
        }
    }

    cout << "[Thread]" << " Sum: " << temp << endl;
}
