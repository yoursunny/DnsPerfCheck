#include "random-host.hpp"

#include "gtest.hpp"

namespace dpc {

TEST(RandomHostTest, Basic) {
  std::cout << makeRandomHost("example.com") << std::endl;
  std::cout << makeRandomHost("example.com") << std::endl;
  std::cout << makeRandomHost("example.net") << std::endl;
  std::cout << makeRandomHost("example.net") << std::endl;
}

} // namespace dpc
