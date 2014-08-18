#ifndef DPC_DB_MYSQL_DB_HPP
#define DPC_DB_MYSQL_DB_HPP

#include "db.hpp"

#include <mysql++/mysql++.h>

namespace dpc {

/** \brief implements Db with MySql
 *  \note The database must be initialized with mysql-db.sql.
 *        The user must have INSERT privilege on the database.
 */
class MySqlDb : public Db
{
public:
  explicit
  MySqlDb(mysqlpp::Connection& conn);

  virtual
  ~MySqlDb();

public:
  virtual std::vector<Domain>
  listDomains();

  virtual void
  insertProbeLog(const ProbeLog& record);

private:
  mysqlpp::Connection& m_conn;
  mysqlpp::Query m_insertQuery;
};

} // namespace dpc

#endif // DPC_DB_MYSQL_DB_HPP
