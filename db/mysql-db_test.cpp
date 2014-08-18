#include "mysql-db.hpp"

#include "gtest.hpp"

namespace dpc {

TEST(MySqlDbTest, All) {
  mysqlpp::Connection conn("dpc_unittest", nullptr, "dpc_unittest", "I7HXycSbf");
  conn.query("DELETE FROM probelogs").execute();

  MySqlDb db(conn);

  std::vector<Domain> domains;
  ASSERT_NO_THROW(domains = db.listDomains());
  ASSERT_GE(domains.size(), 2);
  EXPECT_TRUE(std::any_of(domains.begin(), domains.end(),
              [](const Domain& domain){ return domain.enabled; }));
  EXPECT_TRUE(std::any_of(domains.begin(), domains.end(),
              [](const Domain& domain){ return !domain.enabled; }));

  ProbeLog pl1;
  pl1.timestamp = std::chrono::system_clock::from_time_t(1408000000);
  pl1.domainId = domains[0].id;
  pl1.queryTime = std::chrono::milliseconds(1000);
  ASSERT_NO_THROW({ db.insertProbeLog(pl1); });

  ProbeLog pl2;
  pl2.timestamp = std::chrono::system_clock::from_time_t(1408000005);
  pl2.domainId = domains[0].id;
  pl2.queryTime = std::chrono::milliseconds(2000);
  ASSERT_NO_THROW({ db.insertProbeLog(pl2); });

  ProbeLog pl3;
  pl3.timestamp = std::chrono::system_clock::from_time_t(1408000010);
  pl3.domainId = domains[1].id;
  pl3.queryTime = std::chrono::milliseconds(1000);
  ASSERT_NO_THROW({ db.insertProbeLog(pl3); });

  mysqlpp::StoreQueryResult report = conn.query("SELECT * FROM report")
                                     .store();
  ASSERT_EQ(2, report.num_rows());
  std::for_each(report.begin(), report.end(), [&domains](const mysqlpp::Row& row){
    if (row["domain_name"] == domains[0].name) {
      EXPECT_EQ(static_cast<int>(row["avg_query_time"]), 1500);
      EXPECT_EQ(static_cast<int>(row["stddev_query_time"]), 500);
      EXPECT_EQ(static_cast<int>(row["n_queries"]), 2);
      EXPECT_EQ(static_cast<time_t>(static_cast<mysqlpp::DateTime>(row["first_timestamp"])),
                1408000000);
      EXPECT_EQ(static_cast<time_t>(static_cast<mysqlpp::DateTime>(row["last_timestamp"])),
                1408000005);
    }
    else if (row["domain_name"] == domains[1].name) {
      EXPECT_EQ(static_cast<int>(row["avg_query_time"]), 1000);
      EXPECT_EQ(static_cast<int>(row["stddev_query_time"]), 0);
      EXPECT_EQ(static_cast<int>(row["n_queries"]), 1);
      EXPECT_EQ(static_cast<time_t>(static_cast<mysqlpp::DateTime>(row["first_timestamp"])),
                1408000010);
      EXPECT_EQ(static_cast<time_t>(static_cast<mysqlpp::DateTime>(row["last_timestamp"])),
                1408000010);
    }
    else {
      ADD_FAILURE() << "unexpected domain";
    }
  });

  conn.disconnect();
}

} // namespace dpc
