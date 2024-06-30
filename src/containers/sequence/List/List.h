#ifndef A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_CONTAINERS_SEQUENCE_LIST_LIST_H_
#define A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_CONTAINERS_SEQUENCE_LIST_LIST_H_

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <limits>

namespace s21 {
template <typename T>
class List {
 private:
  struct Node;

 public:
  template <bool IsConst>
  class ListIteratorBase {
   public:
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = std::conditional_t<IsConst, const T *, T *>;
    using reference = std::conditional_t<IsConst, const T &, T &>;

    ListIteratorBase() = default;

    explicit ListIteratorBase(Node *node) : current_{node} {}

    ListIteratorBase(const ListIteratorBase<IsConst> &other) = default;

    template <bool WasConst, class = std::enable_if_t<IsConst && !WasConst>>
    ListIteratorBase(const ListIteratorBase<WasConst> &other)
        : current_{other.base()} {}

    [[nodiscard]] reference operator*() const { return current_->data; }

    [[nodiscard]] pointer operator->() const { return &(current_->data); }

    ListIteratorBase &operator++() {
      current_ = current_->next;
      return *this;
    }

    ListIteratorBase operator++(int) {
      ListIteratorBase previous{*this};
      current_ = current_->next;
      return previous;
    }

    ListIteratorBase &operator--() {
      current_ = current_->prev;
      return *this;
    }

    ListIteratorBase operator--(int) {
      ListIteratorBase previous{*this};
      current_ = current_->prev;
      return previous;
    }

    [[nodiscard]] bool operator==(const ListIteratorBase &other) const {
      return (current_ == other.current_);
    }

    [[nodiscard]] bool operator!=(const ListIteratorBase &other) const {
      return (current_ != other.current_);
    }

    [[nodiscard]] Node *base() const { return current_; }

   private:
    Node *current_{};
  };

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = ListIteratorBase<false>;
  using const_iterator = ListIteratorBase<true>;
  using size_type = std::size_t;

  List() : head_{new Node{}}, tail_{new Node{}}, size_{0} {
    link_head_and_tail();
  }

  explicit List(size_type n) : head_{new Node{}}, tail_{new Node{}}, size_{0} {
    link_head_and_tail();
    for (size_type i{0}; i < n; ++i) {
      push_back(value_type{});
    }
  }

  List(const std::initializer_list<value_type> &items)
      : head_{new Node{}}, tail_{new Node{}}, size_{0} {
    link_head_and_tail();
    for (const auto &item : items) {
      push_back(item);
    }
  }

  List(const List &other) : head_{new Node{}}, tail_{new Node{}}, size_{0} {
    link_head_and_tail();
    Node *current{other.begin().base()};
    while (current != other.end().base()) {
      push_back(current->data);
      current = current->next;
    }
  }

  List(List &&other) {
    head_ = other.head_;
    tail_ = other.tail_;
    size_ = other.size_;

    other.head_ = new Node{};
    other.tail_ = new Node{};
    other.link_head_and_tail();
    other.size_ = 0;
  }

  ~List() {
    clear();

    delete head_;
    delete tail_;
  }

  List &operator=(const List &other) {
    if (this != &other) {
      clear();

      Node *current{other.begin().base()};
      while (current != other.end().base()) {
        push_back(current->data);
        current = current->next;
      }
    }

    return *this;
  }

  List &operator=(List &&other) {
    if (this != &other) {
      clear();
      delete head_;
      delete tail_;

      head_ = other.head_;
      tail_ = other.tail_;
      size_ = other.size_;

      other.head_ = new Node{};
      other.tail_ = new Node{};
      other.link_head_and_tail();
      other.size_ = 0;
    }

    return *this;
  }

  [[nodiscard]] reference front() { return *begin(); }

  [[nodiscard]] const_reference front() const { return *cbegin(); }

  [[nodiscard]] reference back() { return *std::prev(end()); }

  [[nodiscard]] const_reference back() const { return *std::prev(cend()); }

  [[nodiscard]] iterator begin() noexcept { return iterator{head_->next}; }

  [[nodiscard]] const_iterator begin() const noexcept {
    return const_iterator{head_->next};
  }

  [[nodiscard]] iterator end() noexcept { return iterator{tail_}; }

  [[nodiscard]] const_iterator end() const noexcept { return iterator{tail_}; }

  [[nodiscard]] const_iterator cbegin() const noexcept {
    return const_iterator{head_->next};
  }

  [[nodiscard]] const_iterator cend() const noexcept {
    return const_iterator{tail_};
  }

  [[nodiscard]] bool empty() const noexcept { return (begin() == end()); }

  [[nodiscard]] size_type size() const noexcept { return size_; }

  [[nodiscard]] size_type max_size() const noexcept {
    size_type max_difference{
        std::numeric_limits<typename iterator::difference_type>::max()};
    size_type max_allocator_size{std::allocator<Node>{}.max_size()};
    return std::min(max_difference, max_allocator_size);
  }

  void clear() noexcept {
    Node *current{head_->next};
    while (current != tail_) {
      Node *old_node{current};
      current = current->next;
      delete old_node;
    }

    link_head_and_tail();

    size_ = 0;
  }

  iterator insert(iterator position, const_reference value) {
    Node *new_node{new Node{value}};
    if (size_ == 0) {
      head_->next = new_node;
      tail_->prev = new_node;
      new_node->next = tail_;
      new_node->prev = head_;
    } else {
      Node *node_at_position{position.base()};
      new_node->prev = node_at_position->prev;
      new_node->next = node_at_position;
      node_at_position->prev->next = new_node;
      node_at_position->prev = new_node;
    }

    ++size_;

    return iterator(new_node);
  }

  void erase(iterator position) {
    if (empty()) return;

    Node *node_at_position{position.base()};
    node_at_position->prev->next = node_at_position->next;
    node_at_position->next->prev = node_at_position->prev;
    delete node_at_position;

    --size_;
  }

  void push_back(const_reference value) { insert(end(), value); }

  void pop_back() { erase(std::prev(end())); }

  void push_front(const_reference value) { insert(begin(), value); }

  void pop_front() { erase(begin()); }

  void swap(List &other) {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);
  }

  void merge(List &other) {
    if (this != &other) {
      Node *this_current{begin().base()};
      Node *other_current{other.begin().base()};
      while (this_current != tail_ && other_current != other.tail_) {
        if (this_current->data < other_current->data) {
          this_current = this_current->next;
        } else {
          insert_after_current(this_current, other_current);
        }
      }

      while (other_current != other.tail_) {
        insert_after_current(this_current, other_current);
      }

      other.link_head_and_tail();

      size_ += other.size_;
      other.size_ = 0;
    }
  }

  void splice(const_iterator position, List &other) {
    Node *node_at_previous_position{position.base()->prev};
    Node *other_first_element{other.begin().base()};
    Node *other_last_element{std::prev(other.end()).base()};

    node_at_previous_position->next->prev = other_last_element;
    other_last_element->next = node_at_previous_position->next;
    node_at_previous_position->next = other_first_element;
    other_first_element->prev = node_at_previous_position;

    other.link_head_and_tail();

    size_ += other.size_;
    other.size_ = 0;
  }

  void reverse() noexcept {
    if (size_ < 2) return;

    Node *current{head_};

    while (current != nullptr) {
      Node *temp{current->next};
      current->next = current->prev;
      current->prev = temp;
      current = temp;
    }

    std::swap(head_, tail_);
  }

  void unique() {
    if (size_ < 2) return;

    Node *current{begin().base()};
    while (current->next != tail_) {
      Node *next_element{current->next};
      if (next_element->data == current->data) {
        current->next = next_element->next;
        next_element->next->prev = current;
        delete next_element;
        --size_;
      } else {
        current = current->next;
      }
    }
  }

  void sort() {
    if (size_ < 2) return;

    merge_sort(head_);
  }

  template <typename... Args>
  iterator insert_many(iterator position, Args &&...arguments) {
    std::initializer_list<value_type> items{arguments...};

    iterator current_position{position};
    iterator first_inserted_position{position};
    for (const auto &item : items) {
      current_position = insert(current_position, item);

      if (first_inserted_position == position)
        first_inserted_position = current_position;

      ++current_position;
    }

    return first_inserted_position;
  }

  template <typename... Args>
  void insert_many_back(Args &&...arguments) {
    insert_many(end(), arguments...);
  }

  template <typename... Args>
  void insert_many_front(Args &&...arguments) {
    insert_many(begin(), arguments...);
  }

 private:
  void link_head_and_tail() {
    head_->next = tail_;
    tail_->prev = head_;
  }

  void insert_after_current(Node *&this_current, Node *&other_current) {
    Node *other_current_next{other_current->next};
    other_current->prev = this_current->prev;
    other_current->next = this_current;
    this_current->prev->next = other_current;
    this_current->prev = other_current;

    other_current = other_current_next;
  }

  Node *merge_sort(Node *head) {
    if (head == tail_ || head->next == tail_) return head;

    Node *left_part{head};
    Node *right_part{split_in_half(head)};

    left_part = merge_sort(left_part);
    right_part = merge_sort(right_part);

    return merge(left_part, right_part);
  }

  Node *merge(Node *left_part, Node *right_part) {
    if (left_part == tail_) return right_part;
    if (right_part == tail_) return left_part;

    Node *result = head_;

    if (left_part->data <= right_part->data) {
      result = left_part;
      result->next = merge(left_part->next, right_part);
      result->next->prev = result;
    } else {
      result = right_part;
      result->next = merge(left_part, right_part->next);
      result->next->prev = result;
    }

    return result;
  }

  Node *split_in_half(Node *head) {
    Node *fast{head};
    Node *slow{head};

    while (fast->next != tail_ && fast->next->next != tail_) {
      fast = fast->next->next;
      slow = slow->next;
    }

    Node *middle{slow->next};
    slow->next = tail_;

    return middle;
  }

 private:
  struct Node {
    Node *next{nullptr};
    Node *prev{nullptr};
    value_type data{};

    Node() = default;

    explicit Node(const value_type &value) : data{value} {}
  };

  Node *head_{};
  Node *tail_{};
  size_type size_{};
};
}  // namespace s21

#endif  // A2_SIMPLENAVIGATOR_V1_0_CPP_1_SRC_CONTAINERS_SEQUENCE_LIST_LIST_H_
