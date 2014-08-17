#ifndef DPC_CORE_EXECUTION_INTERVAL_HPP
#define DPC_CORE_EXECUTION_INTERVAL_HPP

#include "common.hpp"

namespace dpc {

/** \brief a throwable object to terminate executeAtInterval
 */
class StopExecution
{
};

void
executeAtInterval(std::chrono::nanoseconds interval, std::function<void()> f);

} // namespace dpc

#endif // DPC_CORE_EXECUTION_INTERVAL_HPP
