#include "HardwareSpecs.h"

#include <math.h>

#include "sys/sysinfo.h"
#include "sys/utsname.h"
#include <sys/types.h>
#include <sys/wait.h>

#include <iostream>
using namespace std;

HardwareSpecs::HardwareSpecs() 
{
    
}

HardwareSpecs::~HardwareSpecs() 
{
    
}

int HardwareSpecs::Sum(int a, int b, int c, int d) 
{
    return a + b + c + d;
}

int HardwareSpecs::GetProcessors() 
{
    return std::thread::hardware_concurrency();
}

int HardwareSpecs::ForkSum(int processes) 
{ 

    for (int i = 0; i < processes; i++)
    {
        auto childpid = fork();
        if (childpid == 0)
        {
            ComputeSum(threshold);
            cout << "[" << getpid() << "]" << " Sum: " << sum << endl;

            break;
        }
    }
    return 0;
}

void HardwareSpecs::ComputeSum(int threshold) 
{
    for (int i = 1; i < threshold; ++i)
    {
        for (int j = 1; j < i; ++j)
        {
            sum += sqrt(i * j);
        }
    }
}
