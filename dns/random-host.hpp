#ifndef DPC_DNS_RANDOM_HOST_HPP
#define DPC_DNS_RANDOM_HOST_HPP

#include "common.hpp"

namespace dpc {

/** \brief make a random host name
 */
std::string
makeRandomHost(const std::string& domain);

} // namespace dpc

#endif // DPC_DNS_RANDOM_HOST_HPP
