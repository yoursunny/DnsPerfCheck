#ifndef DPC_DB_DB_HPP
#define DPC_DB_DB_HPP

#include "domain.hpp"
#include "probe-log.hpp"

namespace dpc {

/** \brief represents a database that can store probing records
 */
class Db : noncopyable
{
public:
  Db();

  virtual
  ~Db();

public:
  virtual std::vector<Domain>
  listDomains() = 0;

  virtual void
  insertProbeLog(const ProbeLog& record) = 0;
};

} // namespace dpc

#endif // DPC_DB_DB_HPP
