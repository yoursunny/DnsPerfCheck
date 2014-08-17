#ifndef DPC_COMMON_HPP
#define DPC_COMMON_HPP

#include <stdint.h>
#include <stddef.h>
#include <unistd.h>

#include <algorithm>
#include <chrono>
#include <functional>
#include <list>
#include <memory>
#include <set>
#include <vector>

namespace dpc {

class noncopyable
{
protected:
  noncopyable()
  {
  }

private:
  noncopyable(const noncopyable& other) = delete;

  void
  operator=(const noncopyable& other) = delete;
};

};

#endif // DPC_COMMON_HPP
