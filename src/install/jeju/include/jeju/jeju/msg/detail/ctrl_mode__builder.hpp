// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from jeju:msg/CtrlMode.idl
// generated code does not contain a copyright notice

#ifndef JEJU__MSG__DETAIL__CTRL_MODE__BUILDER_HPP_
#define JEJU__MSG__DETAIL__CTRL_MODE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "jeju/msg/detail/ctrl_mode__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace jeju
{

namespace msg
{

namespace builder
{

class Init_CtrlMode_ctrl_speed
{
public:
  explicit Init_CtrlMode_ctrl_speed(::jeju::msg::CtrlMode & msg)
  : msg_(msg)
  {}
  ::jeju::msg::CtrlMode ctrl_speed(::jeju::msg::CtrlMode::_ctrl_speed_type arg)
  {
    msg_.ctrl_speed = std::move(arg);
    return std::move(msg_);
  }

private:
  ::jeju::msg::CtrlMode msg_;
};

class Init_CtrlMode_ctrl_algo
{
public:
  Init_CtrlMode_ctrl_algo()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CtrlMode_ctrl_speed ctrl_algo(::jeju::msg::CtrlMode::_ctrl_algo_type arg)
  {
    msg_.ctrl_algo = std::move(arg);
    return Init_CtrlMode_ctrl_speed(msg_);
  }

private:
  ::jeju::msg::CtrlMode msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::jeju::msg::CtrlMode>()
{
  return jeju::msg::builder::Init_CtrlMode_ctrl_algo();
}

}  // namespace jeju

#endif  // JEJU__MSG__DETAIL__CTRL_MODE__BUILDER_HPP_
