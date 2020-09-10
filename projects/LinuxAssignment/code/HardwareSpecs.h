#pragma once
#include "unistd.h" // system calls for linux
#include <stdio.h> 
#include <thread>

// Git, Linux, Porting, Threading, Scripting
// https://ltu.instructure.com/courses/10553/assignments/79123
class HardwareSpecs
{
public:

    // ctor
    HardwareSpecs();
    ~HardwareSpecs();

    // maths
    int Sum(int a, int b, int c = 0, int d = 0);

    // data
    int GetProcessors();

    int ForkSum(int processes);
private:
    int threshold = 50000;
    unsigned long long int sum;
    void ComputeSum(int threshold);

};