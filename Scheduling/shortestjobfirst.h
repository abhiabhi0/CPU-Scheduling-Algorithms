#ifndef SHORTESTJOBFIRST_H_
#define SHORTESTJOBFIRST_H_

#include "scheduling.h"

class ShortestJobFirst : public Scheduler
{
  public:
    ShortestJobFirst(unsigned num);
    ShortestJobFirst() = default;
    ShortestJobFirst(const ShortestJobFirst&)            = delete;
    ShortestJobFirst &operator=(const ShortestJobFirst&) = delete;
    ShortestJobFirst(ShortestJobFirst&&)                 = delete;
    ShortestJobFirst &operator=(ShortestJobFirst&&)      = delete;
    ~ShortestJobFirst()                                  = default;

    void calcEndTime();
};

#endif
