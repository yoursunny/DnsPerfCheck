#include "mysql-db.hpp"

namespace dpc {

MySqlDb::MySqlDb(mysqlpp::Connection& conn)
  : m_conn(conn)
  , m_insertQuery(conn.query("INSERT probelogs (dt, domain, query_time) "
                             "VALUES (%0q:timestamp, %1:domain, %2:queryTime)"))
{
  m_insertQuery.parse();
}

MySqlDb::~MySqlDb()
{
}

std::vector<Domain>
MySqlDb::listDomains()
{
  mysqlpp::StoreQueryResult dataset = m_conn.query("SELECT * FROM domains").store();
  std::vector<Domain> domains;
  domains.reserve(dataset.num_rows());
  std::for_each(dataset.begin(), dataset.end(), [&domains](const mysqlpp::Row& row){
    domains.emplace_back();
    domains.back().id = static_cast<int>(row["ID"]);
    domains.back().name = static_cast<std::string>(row["name"]);
    domains.back().enabled = static_cast<bool>(row["enabled"]);
  });
  return domains;
}

void
MySqlDb::insertProbeLog(const ProbeLog& record)
{
  mysqlpp::DateTime dt(std::chrono::system_clock::to_time_t(record.timestamp));
  m_insertQuery.execute(dt, record.domainId, record.queryTime.count());
}

} // namespace dpc
