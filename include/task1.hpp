// Copyright 2020 by keeethyyy_

#ifndef INCLUDE_TASK1_HPP_
#define INCLUDE_TASK1_HPP_
#include <iostream>

#endif // INCLUDE_TASK1_HPP_

template <typename T>
struct NodeStack{           //узел стека на односв. списке
  T value;
  NodeStack *prev= nullptr;
};

template <typename T>
class Stack{

 public:
  Stack()  = default;

  Stack(const Stack &stack) = delete;
  auto operator = (const Stack &stack) = delete;

  Stack(Stack &&stack) noexcept {
    this->top = stack.top;
    stack.top = nullptr;
  } //компилятор выдает варнинг без ноуэксепт
  auto operator = (Stack &&stack)  noexcept {
    this->top = stack.top;
    stack.top = nullptr;
  } //то же самое
  //нужен ли trailing return type после ноуэкспет? так пропадает варнинг
  //что лучше auto или Stack&?

  void push(T&& value){
    NodeStack<T> *tmp;
    tmp = top;
    top = new NodeStack<T>;
    top->prev = tmp;
    top->value = value;
  }

  void push(const T& value){
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
      throw std::runtime_error("Empty stack");
    }
  }

  const T& head() const{
    if(top)
    return top->value;
    else{
      throw std::runtime_error("Empty stack");
    }
  }

  void clearer() {
    if (top) {
      while (top->prev) {
        NodeStack<T> *tmp = std::move(top->prev);
        delete (top);
        top = nullptr;
        //std::cout << "cleared";
        top = tmp;
      }
      delete (top);
      top = nullptr;
     // std::cout << "cleared";
    }
  }

  ~Stack(){
    clearer();
  };

 private:
  NodeStack<T> *top = nullptr;
};
