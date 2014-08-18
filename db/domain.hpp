#ifndef DPC_DB_DOMAIN_HPP
#define DPC_DB_DOMAIN_HPP

#include "common.hpp"

namespace dpc {

/** \brief represents a domain record
 */
struct Domain
{
  int id;
  std::string name;
  bool enabled;
};

} // namespace dpc

#endif // DPC_DB_DOMAIN_HPP
