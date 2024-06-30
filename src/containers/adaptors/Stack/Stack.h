#ifndef A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_ADAPTORS_STACK_STACK_H_
#define A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_ADAPTORS_STACK_STACK_H_

#include <cstddef>
#include <initializer_list>

#include "containers/sequence/list/List.h"

namespace s21 {
template <typename T, class Container = List<T>>
class Stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

 public:
  Stack() = default;

  Stack(const std::initializer_list<T> &items) {
    for (const auto &item : items) {
      push(item);
    }
  }

  Stack(const Stack &other) : container_{other.container_} {}

  Stack(Stack &&other) : container_{std::move(other.container_)} {}

  ~Stack() = default;

  Stack &operator=(const Stack &other) {
    container_ = other.container_;
    return *this;
  }

  Stack &operator=(Stack &&other) {
    container_ = std::move(other.container_);
    return *this;
  }

  [[nodiscard]] reference top() { return *container_.begin(); }

  [[nodiscard]] const_reference top() const { return *container_.cbegin(); }

  [[nodiscard]] bool empty() const { return container_.empty(); }

  [[nodiscard]] size_type size() const { return container_.size(); }

  void push(const_reference value) { container_.push_front(value); }

  void pop() { container_.pop_front(); }

  void swap(Stack &other) { container_.swap(other.container_); }

  template <typename... Args>
  void insert_many_front(Args &&...arguments) {
    std::initializer_list<value_type> items{arguments...};
    for (const auto &item : items) {
      push(item);
    }
  }

 private:
  Container container_{};
};
}  // namespace s21

#endif  // A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_ADAPTORS_STACK_STACK_H_
