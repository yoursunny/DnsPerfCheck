#include "resolver.hpp"

#include <time.h>

namespace dpc {

Resolver::Resolver()
{
  ldns_resolver_new_frm_file(&m_resolver, nullptr);
}

Resolver::~Resolver()
{
  ldns_resolver_deep_free(m_resolver);
}

std::chrono::nanoseconds
Resolver::benchDomain(const std::string& domain)
{
  ldns_rdf* queryDomain = ldns_dname_new_frm_str(domain.c_str());

  timespec t1, t2;
  // use clock_gettime, because std::chrono::steady_clock support is questionable
  clock_gettime(CLOCK_MONOTONIC, &t1);
  ldns_pkt* pkt = ldns_resolver_query(m_resolver, queryDomain, LDNS_RR_TYPE_SOA,
                                      LDNS_RR_CLASS_IN, LDNS_RD);
  clock_gettime(CLOCK_MONOTONIC, &t2);

  ldns_pkt_free(pkt);
  ldns_rdf_free(queryDomain);

  return std::chrono::nanoseconds((t2.tv_sec - t1.tv_sec) * 1000000000LL +
                                  (t2.tv_nsec - t1.tv_nsec));
}

} // namespace dpc
