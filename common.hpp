#ifndef DPC_COMMON_HPP
#define DPC_COMMON_HPP

#include <stdint.h>
#include <stddef.h>
#include <unistd.h>

#include <chrono>
#include <memory>
#include <functional>
#include <list>
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
