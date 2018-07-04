#ifndef PRIORITY_H_
#define PRIORITY_H_

#include "scheduling.h"

class Priority : public Scheduler
{
  public:
    Priority(unsigned num);
    Priority() = default;
    Priority(const Priority&)            = delete;
    Priority &operator=(const Priority&) = delete;
    Priority(Priority&&)                 = delete;
    Priority &operator=(Priority&&)      = delete;
    ~Priority()                          = default;

    void calcEndTime();
};

#endif
