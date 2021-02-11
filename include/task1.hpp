// Copyright 2020 by keeethyyy_

#ifndef INCLUDE_TASK1_HPP_
#define INCLUDE_TASK1_HPP_
#include <iostream>

#endif // INCLUDE_TASK1_HPP_

template <typename T>
struct NodeStack{
  T value;
  NodeStack *prev= nullptr;
};

template <typename T>
class Stack{

 public:
  Stack() = default;

  Stack(const Stack &stack) = delete;
  auto operator = (const Stack &stack) = delete;

  Stack(Stack &&stack) noexcept {
    this->top = stack.top;
    stack.top = nullptr;
  }
  auto operator = (Stack &&stack)  noexcept -> Stack&{
    this->top = stack.top;
    stack.top = nullptr;
  }

  void push(T &&value){
    NodeStack<T> *tmp;
    tmp = top;
    top = new NodeStack<T>;
    top->prev = tmp;
    top->value = value;
  }

  void push(const T &value){
    NodeStack<T> *tmp;
    tmp = top;
    top = new NodeStack<T>;
    top->prev = tmp;
    top->value = std::move(value);
  }

  void pop(){
    if (top){
      NodeStack<T> *_top = top->prev;
      delete top;
      top = _top;
    }else {
      throw std::runtime_error("Empty stack pop");
    }
  }

  const T& head() const{
    if(top)
    return top->value;
    else{
      throw std::runtime_error("Empty stack head");
    }
  }

  void clearer(){
      while (top) {
        NodeStack<T> *tmp = top->prev;
        delete (top);

        top = tmp;
      }
  }

  ~Stack(){
   clearer();
  };

 private:
  NodeStack<T> *top = nullptr;
};
