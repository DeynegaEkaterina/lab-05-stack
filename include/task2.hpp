//
// Created by ekaterina on 03.02.2021.
//

#ifndef TEMPLATE_TASK2_HPP
#define TEMPLATE_TASK2_HPP


template <typename T>
class Stack2 {
 public:
  Stack2() = default;

  Stack2(const Stack2 &stack) = delete;
  auto operator=(const Stack2 &stack) = delete;

  Stack2(Stack2 &&stack) noexcept {
    this->top = stack.top;
    stack.top = nullptr;
  }
  auto operator=(Stack2 &&stack) noexcept -> Stack2 & {
    this->top = stack.top;
    stack.top = nullptr;
  }

  template<typename...Args>
  void push_emplace(Args&&...value){
    top = new NodeStack<T>{{std::forward<Args>(value)...}, top};
  }

  void push(T &&value) {
    top = new NodeStack<T>{std::forward<T>(value), top};
  }

  const T &head() const {
    if (top)
      return top->value;
    else {
      throw std::runtime_error("Empty stack head");
    }
  }

  T pop() {
    if (top){
      auto *tmp = top;
      T data = std::move(top->value);
      top = top->prev;
      delete tmp;
      return data;
    }else {
      throw std::runtime_error("Empty stack pop");
    }
}

void clearer() {
    while (top) {
      NodeStack<T> *tmp = top->prev;
      delete (top);
      top = tmp;
    }
}

~Stack2() { clearer(); }

 private:
  NodeStack<T> *top = nullptr;
};
#endif  // TEMPLATE_TASK2_HPP
