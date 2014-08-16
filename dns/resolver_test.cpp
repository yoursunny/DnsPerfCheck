#include "resolver.hpp"

#include "gtest.hpp"

namespace dpc {

TEST(ResolverTest, BenchDomain) {
  Resolver resolver;
  std::chrono::nanoseconds d1a = resolver.benchDomain("x1.yoursunny.com");
  std::chrono::nanoseconds d2a = resolver.benchDomain("x2.yoursunny.com");
  std::chrono::nanoseconds d3a = resolver.benchDomain("x3.yoursunny.com");
  std::chrono::nanoseconds d1b = resolver.benchDomain("x1.yoursunny.com");
  std::chrono::nanoseconds d2b = resolver.benchDomain("x2.yoursunny.com");
  std::chrono::nanoseconds d3b = resolver.benchDomain("x3.yoursunny.com");

  std::cout << d1a.count() << "\n"
            << d1b.count() << "\n"
            << d2a.count() << "\n"
            << d2b.count() << "\n"
            << d3a.count() << "\n"
            << d3b.count() << "\n";
}

} // namespace dpc
