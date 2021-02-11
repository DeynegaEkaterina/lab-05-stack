// Copyright 2020 Your Name <your_email>

#include <gtest/gtest.h>
#include "task1.hpp"

template<typename T>
struct Fruits{
  T apple;
  T banana;
  T orange;
};

TEST(Example, EmptyTest) {
    EXPECT_TRUE(true);
}

TEST(Stack, NonCopiable_Movable){
  EXPECT_TRUE(std::is_move_constructible<Stack<int>>::value);
  EXPECT_TRUE(std::is_move_assignable<Stack<int>>::value);
  EXPECT_FALSE(std::is_copy_constructible<Stack<int>>::value);
  EXPECT_FALSE(std::is_copy_assignable<Stack<int>>::value);
  EXPECT_TRUE(std::is_nothrow_move_constructible<Stack<int>>::value);
}

TEST(Stack, Push_rvalue){
  Stack<double> a;

  EXPECT_THROW(a.head(), std::runtime_error);

  a.push(6.98);
  EXPECT_EQ(a.head(), 6.98);

  double tmp = 0.34;
  a.push(std::move(tmp));
  EXPECT_EQ(a.head(), 0.34);
}

TEST(Stack, Push_lvalue){
  Stack<std::string> zoo;

  EXPECT_THROW(zoo.head(), std::runtime_error);

  std::string cow = "moo";
  zoo.push(cow);
  EXPECT_EQ(zoo.head(), "moo");

  std::string cat = "myow";
  std::string dog = "gav";
  zoo.push(cat);
  zoo.push(dog);
  EXPECT_EQ(zoo.head(), "gav");
}

TEST(Stack, Pop){
  Stack<int> b;
  EXPECT_THROW(b.head(), std::runtime_error);

  b.push(1);
  b.push(2);
  b.push(3);
  b.pop();
  EXPECT_EQ(b.head(), 2);

  b.pop();
  EXPECT_EQ(b.head(), 1);

  b.pop();
  EXPECT_THROW(b.head(), std::runtime_error);
}

TEST(Stack, head){
  Stack<int> b;
  b.push(1);
  EXPECT_EQ(b.head(), 1);
  b.push(2);
  EXPECT_EQ(b.head(), 2);
  b.push(3);
  EXPECT_EQ(b.head(), 3);
}

TEST(Stack, Struct){
  Stack<Fruits<int>> amount;
  Fruits<int> test_struct1{1, 2,3 };
  amount.push(test_struct1);
  EXPECT_EQ(amount.head().apple, 1);
  EXPECT_EQ(amount.head().banana, 2);
  EXPECT_EQ(amount.head().orange, 3);

  Fruits<int> test_struct2{4, 5,6 };
  Fruits<int> test_struct3{7, 8, 9 };
  amount.push(test_struct2);
  amount.push(test_struct3);
  EXPECT_EQ(amount.head().apple, 7);
  EXPECT_EQ(amount.head().banana, 8);
  EXPECT_EQ(amount.head().orange, 9);

  amount.pop();
  EXPECT_EQ(amount.head().apple, 4);
  EXPECT_EQ(amount.head().banana, 5);
  EXPECT_EQ(amount.head().orange, 6);
}

