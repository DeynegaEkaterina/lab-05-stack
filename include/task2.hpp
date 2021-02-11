//
// Created by ekaterina on 03.02.2021.
//

#ifndef TEMPLATE_TASK2_HPP
#define TEMPLATE_TASK2_HPP

struct NodeStack{
  T value;
  NodeStack *prev= nullptr;
};

template <typename T>
class Stack2 {
 public:
  Stack2() = default;

  Stack2(const Stack2 &stack) = delete;
  auto operator=(const Stack &stack) = delete;

  Stack2(Stack2 &&stack) noexcept {
    this->top = stack.top;
    stack.top = nullptr;
  }
  auto operator=(Stack2 &&stack) noexcept -> Stack2 & {
    this->top = stack.top;
    stack.top = nullptr;
  }

  void push(T &&value) {
    NodeStack<T> *tmp;
    tmp = top;
    top = new NodeStack<T>;
    top->prev = tmp;
    top->value = value;
  }

  const T &head() const {
    if (top)
      return top->value;
    else {
      throw std::runtime_error("Empty stack");
    }
  }

  T pop() {
    NodeStack<T> *tmp;
    tmp = top;
    top = top->prev;
    T tmps = tmp->value;
    if (tmp) {
      delete (tmp);
      tmp = nullptr;
    }
    return tmps;
  else {
    throw std::runtime_error("Empty stack");
  }
}


void clearer() {
  if (top) {
    while (top->prev) {
      NodeStack<T> *tmp = std::move(top->prev);
      delete (top);
      top = nullptr;
      top = tmp;
    }
    delete (top);
    top = nullptr;
  }
  else{
    throw std::runtime_error("Empty stack");
  }
}

  template <typename... Args>
  void Stack2<T>::push_emplace(Args&&... value) {
    top = new NodeStack<T>{{std::forward<Args>(value)...}, top};
  }

~Stack() { clearer(); }

 private:
  NodeStack<T> *top = nullptr;
};
#endif  // TEMPLATE_TASK2_HPP
