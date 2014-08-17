#include "execute-at-interval.hpp"

#include <time.h>

#include "gtest.hpp"

namespace dpc {

TEST(ExecuteAtIntervalTest, Regular) {
  int nCalls = 0;
  time_t t1 = time(nullptr);
  executeAtInterval(std::chrono::seconds(2), [&nCalls](){
    if (++nCalls == 3) {
      throw StopExecution();
    }
  });
  time_t t2 = time(nullptr);

  EXPECT_EQ(3, nCalls);
  EXPECT_EQ(4, t2 - t1);
}

TEST(ExecuteAtIntervalTest, SlowExecution) {
  int nCalls = 0;
  time_t t1 = time(nullptr);
  executeAtInterval(std::chrono::seconds(2), [&nCalls](){
    if (++nCalls == 3) {
      throw StopExecution();
    }
    if (nCalls == 1) {
      sleep(3);
    }
  });
  time_t t2 = time(nullptr);

  EXPECT_EQ(3, nCalls);
  EXPECT_EQ(5, t2 - t1);
}

} // namespace dpc
