#include <iostream>
#include <vector>
#include <algorithm> // std::find
#include <iterator> // std::begin, std::end
#include <limits> //std::numeric_limits
#include "scheduling.h"
#include "roundrobin.h"

RoundRobin::RoundRobin(unsigned num, unsigned quantum): Scheduler(num)
}

void RoundRobin::calcEndTime()
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
    while (!(std::all_of(burstTimeCopy.begin(), burstTimeCopy.end(),
            [] (unsigned e) { return e == 0; })))
    {
        unsigned currActiveProcessID = 0;
        auto it = burstTimeCopy.begin();
        while (it != burstTimeCopy.end())
        {
            if (burstTimeCopy[currActiveProcessID] > timeQuantum)
            {
                burstTimeCopy[currActiveProcessID] -= timeQuantum;
                timeCounter += timeQuantum;
            }
            else if (burstTimeCopy[currActiveProcessID] > 0)
            {
                timeCounter += burstTimeCopy[currActiveProcessID];
                burstTimeCopy[currActiveProcessID] = 0;
                endTime[currActiveProcessID] = timeCounter;
            }
            currActiveProcessID++;
            it++;
        }
    }
}

int main()
{
    unsigned num, timeQuantum;
    std::cout << "Enter number of process: ";
    std::cin >> num;
    std::cout << "\nEnter time quantum : ";
    std::cin >> timeQuantum;
    RoundRobin roundRobin(num, timeQuantum);
    roundRobin.calcEndTime();
    roundRobin.calcTurnAroundTime();
    roundRobin.calcWaitingTime();
    roundRobin.printInfo();
}
