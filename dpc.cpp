#include <getopt.h>
#include "core/execute-at-interval.hpp"
#include "db/mysql-db.hpp"
#include "dns/resolver.hpp"
#include "dns/random-host.hpp"

namespace dpc {

void
usage()
{
  std::cout << "dpc -h -D db-name -u db-user -p db-password -i interval\n"
               "  -h: print this help\n"
               "  -D: specify database name (required)\n"
               "  -u: specify database user (required)\n"
               "  -p: specify database password (required)\n"
               "  -i: specify DNS query interval in seconds (default 60s, minimum 5s)\n";
}

int
main(int argc, char** argv)
{
  std::string dbName;
  std::string dbUser;
  std::string dbPassword;
  std::chrono::seconds queryInterval(60);
  int opt;
  while ((opt = getopt(argc, argv, "hD:u:p:i:")) != -1) {
    switch (opt) {
    case 'h':
      usage();
      return 0;
    case 'D':
      dbName = optarg;
      break;
    case 'u':
      dbUser = optarg;
      break;
    case 'p':
      dbPassword = optarg;
      break;
    case 'i':
      queryInterval = std::chrono::seconds(atoi(optarg));
      break;
    default:
      usage();
      return 1;
    }
  }
  if (dbName.empty() || dbUser.empty() || dbPassword.empty() ||
      queryInterval < std::chrono::seconds(5)) {
    usage();
    return 1;
  }

  mysqlpp::Connection conn(dbName.c_str(), nullptr, dbUser.c_str(), dbPassword.c_str());
  if (!conn) {
    std::cerr << "cannot open database connection" << std::endl;
    return 2;
  }
  MySqlDb db(conn);

  Resolver resolver;

  executeAtInterval(queryInterval, [&db, &resolver](){
    std::vector<Domain> domains = db.listDomains();
    std::for_each(domains.begin(), domains.end(), [&db, &resolver](const Domain& domain){
      if (!domain.enabled)
        return;
      std::string hostname = makeRandomHost(domain.name);
      ProbeLog pl;
      pl.timestamp = std::chrono::system_clock::now();
      pl.domainId = domain.id;
      pl.queryTime = std::chrono::duration_cast<std::chrono::milliseconds>(
                     resolver.benchDomain(hostname));
      db.insertProbeLog(pl);
      std::cerr << std::chrono::system_clock::to_time_t(pl.timestamp)
                << " " << hostname
                << " " << pl.queryTime.count() << std::endl;
    });
  });
  return 0;
}

} // namespace dpc

int
main(int argc, char** argv)
{
  return dpc::main(argc, argv);
}
