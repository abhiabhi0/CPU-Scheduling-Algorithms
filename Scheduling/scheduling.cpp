#include <iostream>
#include <vector>
#include "scheduling.h"

Scheduler::Scheduler(unsigned num): endTime(num, 0)
{
    unsigned arrivalVal, burstVal, priorityVal;
    data.reserve(num);
    endTime.reserve(num);
    waitingTime.reserve(num);
    turnAroundTime.reserve(num);

    std::cout << "\nEnter arrival time and burst time and priority eg(5 18 2)\n";
    std::cout << "If it is not priority scheduling enter 0 for priority\n";
    std::cout << "Lower integer has higher priority\n";
    for (unsigned i = 0; i < num; i++)
    {
        std::cout << "\nProcess" << i+1 << ": ";
        std::cin >> arrivalVal >> burstVal >> priorityVal;
        data.push_back( Data(arrivalVal, burstVal, priorityVal) );
    }
}

void Scheduler::calcTurnAroundTime()
{
    double sum = 0.00;
    for (std::size_t i = 0; i < data.size(); i++)
    {
        unsigned val = endTime[i] - data[i].arrivalTime;
        turnAroundTime.push_back(val);
        sum += (double)val;
    }
    avgTurnAroundTime = sum / turnAroundTime.size();
}

void Scheduler::calcWaitingTime()
{
    double sum = 0.00;
    for (std::size_t i = 0; i < data.size(); i++)
    {
        unsigned val = turnAroundTime[i] - data[i].burstTime;
        waitingTime.push_back(val);
        sum += (double)val;
    }
    avgWaitingTime = sum / waitingTime.size();
}

void Scheduler::printInfo() const
{
    std::cout << "ProcessID\tArrival Time\tBurst Time\tPriority\tEnd Time\tWaiting Time";
    std::cout << "\tTurnaround Time\n";
    for (std::size_t i = 0; i < data.size(); i++)
    {
        std::cout << i+1 << "\t\t" << data[i].arrivalTime << "\t\t";
        std::cout << data[i].burstTime << "\t\t" <<data[i].priority << "\t\t";
        std::cout << endTime[i] << "\t\t";
        std::cout << waitingTime[i] <<"\t\t" << turnAroundTime[i] <<'\n';
    }
    std::cout << "Average Waiting Time : " << avgWaitingTime << '\n';
    std::cout << "Average Turn Around Time : " << avgTurnAroundTime << '\n';
}
