#include "random-host.hpp"

#include <random>

namespace dpc {

static std::mt19937 g_rng;
static const std::string RANDOM_HOST_CHARS = "abcdefghijklmnopqrstuvwxyz0123456789";
static std::uniform_int_distribution<size_t> g_charDist(0, RANDOM_HOST_CHARS.size() - 1);
static const size_t MIN_LENGTH = 8;
static const size_t MAX_LENGTH = 16;
static std::uniform_int_distribution<size_t> g_lengthDist(MIN_LENGTH, MAX_LENGTH);

std::string
makeRandomHost(const std::string& domain)
{
  size_t hostLength = g_lengthDist(g_rng);
  std::string host;
  host.reserve(hostLength + 1 + domain.size());

  for (size_t i = 0; i < hostLength; ++i) {
    host.push_back(RANDOM_HOST_CHARS[g_charDist(g_rng)]);
  }

  host.push_back('.');
  host.append(domain);
  return host;
}

} // namespace dpc
