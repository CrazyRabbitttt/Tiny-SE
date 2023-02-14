#ifndef ICEE_INCLUDE_CORE_QUEUE_H_
#define ICEE_INCLUDE_CORE_QUEUE_H_

#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>

namespace Icee {

using std::condition_variable;
using std::mutex;
using std::queue;

template <typename T>
class ThreadSafeQueue {
 public:
  void Push(T new_value) {
    auto data = std::make_shared<T>(std::move(new_value));
    std::lock_guard<std::mutex> lock(latch_);
    queue_.push(data);
    cv_.notify_one();
  }

  void WaitAndPop(T &value) {
    std::unique_lock<mutex> lock(latch_);
    cv_.wait(lock, [this]() { !return queue_.empty(); });  // wait for the value in the queue
    value = std::move(*(queue_.front()));
    queue_.pop();
  }

  std::shared_ptr<T> WaitAndPop() {
    std::unique_lock<mutex> lock(latch_);
    cv_.wait(lock, [this]() { !return queue_.empty(); });  // wait for the value in the queue
    auto res = queue_.front();
    queue_.pop();
    return res;
  }

  bool TryPop(T &value) {
    std::lock_guard<mutex> lock(latch_);
    if (queue_.empty()) {
      return false;
    }
    value = *(queue_.front());
    queue_.pop();
    return true;
  }

  std::shared_ptr<T> TryPop() {
    std::lock_guard<mutex> lock(latch_);
    if (queue_.empty()) {
      return std::shared_ptr<T>();
    }
    auto res = queue_.front();
    queue_.pop();
    return res;
  }

  bool Empty() {
    std::lock_guard<mutex> lock(latch_);
    return queue_.empty();
  }

 private:
  mutable std::mutex latch_;
  std::queue<std::shared_ptr<T> > queue_;
  std::condition_variable cv_;
};

}  // namespace Icee
#endif
