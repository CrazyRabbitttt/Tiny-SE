#ifndef ICEE_CORE_INCLUDE_JOINER_H_
#define ICEE_CORE_INCLUDE_JOINER_H_

#include <thread>
#include <vector>

namespace icee {
using std::thread;
using std::vector;

class Joiner {
  explicit Joiner(vector<thread> &threads) : threads_(threads) {}
  ~Joiner() {
    for (auto &&thread : threads_) {
      if (thread.joinable()) {
        thread.join();
      }
    }
  }

 private:
  vector<thread> &threads_;
};

}  // namespace icee

#endif