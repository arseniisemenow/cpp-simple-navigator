#ifndef A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_ADAPTORS_QUEUE_QUEUE_H_
#define A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_ADAPTORS_QUEUE_QUEUE_H_

#include <cstddef>
#include <initializer_list>

#include "containers/sequence/List/List.h"

namespace s21 {
template <typename T, class Container = List<T>>
class Queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

 public:
  Queue() = default;

  Queue(const std::initializer_list<T> &items) {
    for (const auto &item : items) {
      push(item);
    }
  }

  Queue(const Queue &other) : container_{other.container_} {}

  Queue(Queue &&other) : container_{std::move(other.container_)} {}

  ~Queue() = default;

  Queue &operator=(const Queue &other) {
    container_ = other.container_;
    return *this;
  }

  Queue &operator=(Queue &&other) {
    container_ = std::move(other.container_);
    return *this;
  }

  [[nodiscard]] reference front() { return *container_.begin(); }

  [[nodiscard]] const_reference front() const { return *container_.cbegin(); }

  [[nodiscard]] reference back() { return *std::prev(container_.end()); }

  [[nodiscard]] const_reference back() const {
    return *std::prev(container_.cend());
  }

  [[nodiscard]] bool empty() const { return container_.empty(); }

  [[nodiscard]] size_type size() const { return container_.size(); }

  void push(const_reference value) { container_.push_back(value); }

  void pop() { container_.pop_front(); }

  void swap(Queue &other) { container_.swap(other.container_); }

  template <typename... Args>
  void insert_many_back(Args &&...arguments) {
    container_.insert_many_back(arguments...);
  }

 private:
  Container container_{};
};
}  // namespace s21

#endif  // A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_ADAPTORS_QUEUE_QUEUE_H_
