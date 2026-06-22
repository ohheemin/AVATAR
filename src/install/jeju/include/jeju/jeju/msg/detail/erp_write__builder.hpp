// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from jeju:msg/ERPWrite.idl
// generated code does not contain a copyright notice

#ifndef JEJU__MSG__DETAIL__ERP_WRITE__BUILDER_HPP_
#define JEJU__MSG__DETAIL__ERP_WRITE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "jeju/msg/detail/erp_write__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace jeju
{

namespace msg
{

namespace builder
{

class Init_ERPWrite_brake
{
public:
  explicit Init_ERPWrite_brake(::jeju::msg::ERPWrite & msg)
  : msg_(msg)
  {}
  ::jeju::msg::ERPWrite brake(::jeju::msg::ERPWrite::_brake_type arg)
  {
    msg_.brake = std::move(arg);
    return std::move(msg_);
  }

private:
  ::jeju::msg::ERPWrite msg_;
};

class Init_ERPWrite_steer
{
public:
  explicit Init_ERPWrite_steer(::jeju::msg::ERPWrite & msg)
  : msg_(msg)
  {}
  Init_ERPWrite_brake steer(::jeju::msg::ERPWrite::_steer_type arg)
  {
    msg_.steer = std::move(arg);
    return Init_ERPWrite_brake(msg_);
  }

private:
  ::jeju::msg::ERPWrite msg_;
};

class Init_ERPWrite_speed
{
public:
  explicit Init_ERPWrite_speed(::jeju::msg::ERPWrite & msg)
  : msg_(msg)
  {}
  Init_ERPWrite_steer speed(::jeju::msg::ERPWrite::_speed_type arg)
  {
    msg_.speed = std::move(arg);
    return Init_ERPWrite_steer(msg_);
  }

private:
  ::jeju::msg::ERPWrite msg_;
};

class Init_ERPWrite_gear
{
public:
  explicit Init_ERPWrite_gear(::jeju::msg::ERPWrite & msg)
  : msg_(msg)
  {}
  Init_ERPWrite_speed gear(::jeju::msg::ERPWrite::_gear_type arg)
  {
    msg_.gear = std::move(arg);
    return Init_ERPWrite_speed(msg_);
  }

private:
  ::jeju::msg::ERPWrite msg_;
};

class Init_ERPWrite_is_estop
{
public:
  explicit Init_ERPWrite_is_estop(::jeju::msg::ERPWrite & msg)
  : msg_(msg)
  {}
  Init_ERPWrite_gear is_estop(::jeju::msg::ERPWrite::_is_estop_type arg)
  {
    msg_.is_estop = std::move(arg);
    return Init_ERPWrite_gear(msg_);
  }

private:
  ::jeju::msg::ERPWrite msg_;
};

class Init_ERPWrite_is_auto
{
public:
  Init_ERPWrite_is_auto()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ERPWrite_is_estop is_auto(::jeju::msg::ERPWrite::_is_auto_type arg)
  {
    msg_.is_auto = std::move(arg);
    return Init_ERPWrite_is_estop(msg_);
  }

private:
  ::jeju::msg::ERPWrite msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::jeju::msg::ERPWrite>()
{
  return jeju::msg::builder::Init_ERPWrite_is_auto();
}

}  // namespace jeju

#endif  // JEJU__MSG__DETAIL__ERP_WRITE__BUILDER_HPP_
