#ifndef ROUNDROBIN_H_
#define ROUNDROBIN_H_

#include "scheduling.h"

class RoundRobin : public Scheduler
{
    unsigned timeQuantum;
  public:
    RoundRobin(unsigned num, unsigned quantum);
    RoundRobin() = default;
    RoundRobin(const RoundRobin&)            = delete;
    RoundRobin &operator=(const RoundRobin&) = delete;
    RoundRobin(RoundRobin&&)                 = delete;
    RoundRobin &operator=(RoundRobin&&)      = delete;
    ~RoundRobin()                            = default;

    void calcEndTime();
};

#endif
