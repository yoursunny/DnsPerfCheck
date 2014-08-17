#include "mysql-db.hpp"

namespace dpc {

MySqlDb::MySqlDb(mysqlpp::Connection& conn)
  : m_conn(conn)
  , m_insertQuery(conn.query("INSERT probelog (dt, domain, query_time) "
                             "VALUES (%0q:timestamp, %1q:domain, %2:queryTime)"))
{
  m_insertQuery.parse();
}

MySqlDb::~MySqlDb()
{
}

void
MySqlDb::insert(const Record& record)
{
  mysqlpp::DateTime dt(std::chrono::system_clock::to_time_t(record.timestamp));
  m_insertQuery.execute(dt, record.domain, record.queryTime.count());
}

} // namespace dpc
