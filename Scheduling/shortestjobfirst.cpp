#include <iostream>
#include <array>
#include <vector>
#include <algorithm> // std::find
#include <iterator> // std::begin, std::end
#include <limits> //std::numeric_limits
#include "scheduling.h"
#include "shortestjobfirst.h"


ShortestJobFirst::ShortestJobFirst(unsigned num) :Scheduler(num)
                                                  {}

void ShortestJobFirst::calcEndTime()
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
        if (timeCounter <= data[dataSize -1].arrivalTime)
        {
            unsigned minBurstTime = std::numeric_limits<uint>::max();
            //Find index with minimum burst Time remaining
            for (std::size_t i = 0; i < burstTimeCopy.size(); i++)
            {
                if (burstTimeCopy[i] != 0 && burstTimeCopy[i] < minBurstTime
                  && data[i].arrivalTime <= timeCounter)
                {
                    minBurstTime = burstTimeCopy[i];
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
            unsigned minBurstTime = std::numeric_limits<uint>::max();
            //Find index with minimum burst Time remaining
            for (std::size_t i = 0; i < burstTimeCopy.size(); i++)
            {
                if (burstTimeCopy[i] != 0 && burstTimeCopy[i] < minBurstTime)
                {
                    minBurstTime = burstTimeCopy[i];
                    currActiveProcessID = i;
                }
            }
            timeCounter += minBurstTime;
            endTime[currActiveProcessID] = timeCounter;
            burstTimeCopy[currActiveProcessID] = 0;
        }
    }
}

int main()
{
    int num;
    std::cout << "Enter the number of processes\n";
    std::cin >> num;
    ShortestJobFirst batch(num);
    batch.calcEndTime();
    batch.calcTurnAroundTime();
    batch.calcWaitingTime();
    batch.printInfo();
}
