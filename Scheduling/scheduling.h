#ifndef SCHEDULING_H_
#define SCHEDULING_H_

#include <vector>

class Scheduler
{
  public:

    double avgWaitingTime;
    double avgTurnAroundTime;

    struct Data
    {
        unsigned arrivalTime;
        //When process start to execute
        unsigned burstTime;
        //only for priority Scheduling
        unsigned priority;

        Data(unsigned arrivalTime, unsigned burstTime, unsigned priority):
            arrivalTime(std::move(arrivalTime)),
            burstTime(std::move(burstTime)),
            priority(std::move(priority))
            {}
        Data() = default;
    };

    std::vector<Data> data;
    //process wait to execute after they have arrived
    std::vector<unsigned> waitingTime;
    //total time taken by processes
    std::vector<unsigned> turnAroundTime;
    //time when a process end
    std::vector<unsigned> endTime;

    Scheduler(unsigned num = 0);
    Scheduler(const Scheduler&)            = delete;
    Scheduler &operator=(const Scheduler&) = delete;
    Scheduler(Scheduler&&)                 = delete;
    Scheduler &operator=(Scheduler&&)      = delete;
    ~Scheduler()                           = default;

    void calcWaitingTime();
    void calcTurnAroundTime();
    virtual void calcEndTime() = 0;
    void printInfo() const;
};

#endif
