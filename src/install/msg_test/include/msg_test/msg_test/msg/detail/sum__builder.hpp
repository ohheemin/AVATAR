// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from msg_test:msg/Sum.idl
// generated code does not contain a copyright notice

#ifndef MSG_TEST__MSG__DETAIL__SUM__BUILDER_HPP_
#define MSG_TEST__MSG__DETAIL__SUM__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "msg_test/msg/detail/sum__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace msg_test
{

namespace msg
{

namespace builder
{

class Init_Sum_sum
{
public:
  explicit Init_Sum_sum(::msg_test::msg::Sum & msg)
  : msg_(msg)
  {}
  ::msg_test::msg::Sum sum(::msg_test::msg::Sum::_sum_type arg)
  {
    msg_.sum = std::move(arg);
    return std::move(msg_);
  }

private:
  ::msg_test::msg::Sum msg_;
};

class Init_Sum_b
{
public:
  explicit Init_Sum_b(::msg_test::msg::Sum & msg)
  : msg_(msg)
  {}
  Init_Sum_sum b(::msg_test::msg::Sum::_b_type arg)
  {
    msg_.b = std::move(arg);
    return Init_Sum_sum(msg_);
  }

private:
  ::msg_test::msg::Sum msg_;
};

class Init_Sum_a
{
public:
  Init_Sum_a()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Sum_b a(::msg_test::msg::Sum::_a_type arg)
  {
    msg_.a = std::move(arg);
    return Init_Sum_b(msg_);
  }

private:
  ::msg_test::msg::Sum msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::msg_test::msg::Sum>()
{
  return msg_test::msg::builder::Init_Sum_a();
}

}  // namespace msg_test

#endif  // MSG_TEST__MSG__DETAIL__SUM__BUILDER_HPP_
