// Copyright © 2020  Philip Lindh 
// All rights reserved

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

    int GetProcessors();

    void ForkSum(int processes);

    void ThreadSum(int threads);

private:

    float test1 = 0;
    float test2 = 0;
    float test3 = 0;

    int threshold = 50000;

    unsigned long long int sum;
    unsigned long long int ComputeSum(int start, int end);

    static void ComputeSumStatic(int start, int end);

};