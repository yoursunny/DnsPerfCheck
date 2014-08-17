#ifndef DPC_DB_RECORD_HPP
#define DPC_DB_RECORD_HPP

#include "common.hpp"

namespace dpc {

/** \brief represents a query time record
 */
struct Record
{
  std::chrono::system_clock::time_point timestamp;
  std::string domain;
  std::chrono::milliseconds queryTime;
};

} // namespace dpc

#endif // DPC_DB_RECORD_HPP
