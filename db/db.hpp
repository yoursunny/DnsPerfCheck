#ifndef DPC_DB_DB_HPP
#define DPC_DB_DB_HPP

#include "record.hpp"

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
  /** \brief insert record
   */
  virtual void
  insert(const Record& record) = 0;
};

} // namespace dpc

#endif // DPC_DB_DB_HPP
