#include <iostream>
#include <vector>
#include <algorithm> // std::find
#include <iterator> // std::begin, std::end
#include <limits> //std::numeric_limits
#include "scheduling.h"
#include "priority.h"

Priority::Priority(unsigned num): Scheduler(num)
                                  {}

void Priority::calcEndTime()
{
    //If arrival time is not sorted
    //sort burst time according to arrival time
    static const auto byArrival = [](const Data &a, const Data &b)
    {
        return a.arrivalTime < b.arrivalTime;
    };
    std::sort(data.begin(), data.end(), byArrival);

    //copy values of burst time in new vector
    std::vector<unsigned> burstTimeCopy;
    for (auto it = data.begin(); it != data.end(); ++it)
    {
        unsigned val = (*it).burstTime;
        burstTimeCopy.push_back(val);
    }

    unsigned timeCounter = 0;
    unsigned currActiveProcessID = 0;
    while (!(std::all_of(burstTimeCopy.begin(), burstTimeCopy.end(),
            [] (unsigned e) { return e == 0; })))
    {
        std::size_t dataSize = data.size();
        //All processes are not arrived
        if (timeCounter <= data[dataSize - 1].arrivalTime)
        {
            unsigned maxPriority = std::numeric_limits<uint>::max();
            for (std::size_t i = 0; i < burstTimeCopy.size(); i++)
            {
                if (burstTimeCopy[i] != 0 && data[i].priority < maxPriority
                    && data[i].arrivalTime <= timeCounter)
                {
                    maxPriority = data[i].priority;
                    currActiveProcessID = i;
                }
            }
            burstTimeCopy[currActiveProcessID] -= 1;
            timeCounter++;
            if (burstTimeCopy[currActiveProcessID] == 0)
            {
                endTime[currActiveProcessID] = timeCounter;
            }
        }
        else //When all processes are arrived
        {
            unsigned maxPriority = std::numeric_limits<uint>::max();
            for (std::size_t i = 0 ; i < burstTimeCopy.size(); i++)
            {
                if (burstTimeCopy[i] != 0 && data[i].priority < maxPriority)
                {
                    maxPriority = data[i].priority;
                    currActiveProcessID = i;
                }
            }
            timeCounter += burstTimeCopy[currActiveProcessID];
            burstTimeCopy[currActiveProcessID] = 0;
            endTime[currActiveProcessID] = timeCounter;
        }
    }
}

int main()
{
    int num;
    std::cout << "Enter the number of processes\n";
    std::cin >> num;
    Priority prioritySchedule(num);
    prioritySchedule.calcEndTime();
    prioritySchedule.calcTurnAroundTime();
    prioritySchedule.calcWaitingTime();
    prioritySchedule.printInfo();
}
