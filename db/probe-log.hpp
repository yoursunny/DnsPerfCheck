#ifndef DPC_DB_PROBE_LOG_HPP
#define DPC_DB_PROBE_LOG_HPP

#include "common.hpp"

namespace dpc {

/** \brief represents a query time record
 */
struct ProbeLog
{
  std::chrono::system_clock::time_point timestamp;
  int domainId;
  std::chrono::milliseconds queryTime;
};

} // namespace dpc

#endif // DPC_DB_PROBE_LOG_HPP
