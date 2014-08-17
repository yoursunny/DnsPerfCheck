#include "execute-at-interval.hpp"

#include <time.h>

namespace dpc {

void
executeAtInterval(std::chrono::nanoseconds interval, std::function<void()> f)
{
  timespec t1, tNext;
  while (true) {
    clock_gettime(CLOCK_MONOTONIC, &t1);
    try {
      f();
    }
    catch (StopExecution&) {
      return;
    }
    std::chrono::nanoseconds::rep t2 = t1.tv_sec * 1000000000 + t1.tv_nsec +
                                       interval.count();
    tNext.tv_sec = t2 / 1000000000;
    tNext.tv_nsec = t2 % 1000000000;
    clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &tNext, nullptr);
  }
}

} // namespace dpc
