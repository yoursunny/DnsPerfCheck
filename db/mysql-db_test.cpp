#include "mysql-db.hpp"

#include "gtest.hpp"

namespace dpc {

TEST(MySqlDbTest, Insert_Report) {
  mysqlpp::Connection conn("dpc_unittest", nullptr, "dpc_unittest", "I7HXycSbf");
  conn.query("DELETE FROM probelog").execute();

  MySqlDb db(conn);

  Record rec1;
  rec1.timestamp = std::chrono::system_clock::from_time_t(1408000000);
  rec1.domain = "example.com";
  rec1.queryTime = std::chrono::milliseconds(1000);
  ASSERT_NO_THROW({ db.insert(rec1); });

  Record rec2;
  rec2.timestamp = std::chrono::system_clock::from_time_t(1408000005);
  rec2.domain = "example.com";
  rec2.queryTime = std::chrono::milliseconds(2000);
  ASSERT_NO_THROW({ db.insert(rec2); });

  Record rec3;
  rec3.timestamp = std::chrono::system_clock::from_time_t(1408000010);
  rec3.domain = "example.net";
  rec3.queryTime = std::chrono::milliseconds(1000);
  ASSERT_NO_THROW({ db.insert(rec3); });

  mysqlpp::StoreQueryResult report = conn.query("SELECT * FROM report")
                                     .store();
  ASSERT_EQ(2, report.num_rows());
  std::for_each(report.begin(), report.end(), [](const mysqlpp::Row& row){
    if (row["domain"] == "example.com") {
      EXPECT_EQ(static_cast<int>(row["avg_query_time"]), 1500);
      EXPECT_EQ(static_cast<int>(row["stddev_query_time"]), 500);
      EXPECT_EQ(static_cast<int>(row["n_queries"]), 2);
      EXPECT_EQ(static_cast<time_t>(static_cast<mysqlpp::DateTime>(row["first_timestamp"])),
                1408000000);
      EXPECT_EQ(static_cast<time_t>(static_cast<mysqlpp::DateTime>(row["last_timestamp"])),
                1408000005);
    }
    else if (row["domain"] == "example.net") {
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
