#ifndef DPC_DNS_RESOLVER_HPP
#define DPC_DNS_RESOLVER_HPP

#include "common.hpp"
#include <ldns/ldns.h>

namespace dpc {

class Resolver : noncopyable
{
public:
  Resolver();

  ~Resolver();

public:
  /** \brief benchmark the response speed of nameserver by querying SOA of a domain name
   *  \note caller can prepend a randomized component to domain to bypass DNS cache
   */
  std::chrono::nanoseconds
  benchDomain(const std::string& domain);

private:
  ldns_resolver* m_resolver;
};

} // namespace dpc

#endif // DPC_DNS_RESOLVER_HPP
