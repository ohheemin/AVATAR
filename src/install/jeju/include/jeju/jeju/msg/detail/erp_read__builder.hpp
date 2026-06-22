// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from jeju:msg/ERPRead.idl
// generated code does not contain a copyright notice

#ifndef JEJU__MSG__DETAIL__ERP_READ__BUILDER_HPP_
#define JEJU__MSG__DETAIL__ERP_READ__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "jeju/msg/detail/erp_read__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace jeju
{

namespace msg
{

namespace builder
{

class Init_ERPRead_etx1
{
public:
  explicit Init_ERPRead_etx1(::jeju::msg::ERPRead & msg)
  : msg_(msg)
  {}
  ::jeju::msg::ERPRead etx1(::jeju::msg::ERPRead::_etx1_type arg)
  {
    msg_.etx1 = std::move(arg);
    return std::move(msg_);
  }

private:
  ::jeju::msg::ERPRead msg_;
};

class Init_ERPRead_etx0
{
public:
  explicit Init_ERPRead_etx0(::jeju::msg::ERPRead & msg)
  : msg_(msg)
  {}
  Init_ERPRead_etx1 etx0(::jeju::msg::ERPRead::_etx0_type arg)
  {
    msg_.etx0 = std::move(arg);
    return Init_ERPRead_etx1(msg_);
  }

private:
  ::jeju::msg::ERPRead msg_;
};

class Init_ERPRead_alive
{
public:
  explicit Init_ERPRead_alive(::jeju::msg::ERPRead & msg)
  : msg_(msg)
  {}
  Init_ERPRead_etx0 alive(::jeju::msg::ERPRead::_alive_type arg)
  {
    msg_.alive = std::move(arg);
    return Init_ERPRead_etx0(msg_);
  }

private:
  ::jeju::msg::ERPRead msg_;
};

class Init_ERPRead_enc
{
public:
  explicit Init_ERPRead_enc(::jeju::msg::ERPRead & msg)
  : msg_(msg)
  {}
  Init_ERPRead_alive enc(::jeju::msg::ERPRead::_enc_type arg)
  {
    msg_.enc = std::move(arg);
    return Init_ERPRead_alive(msg_);
  }

private:
  ::jeju::msg::ERPRead msg_;
};

class Init_ERPRead_brake
{
public:
  explicit Init_ERPRead_brake(::jeju::msg::ERPRead & msg)
  : msg_(msg)
  {}
  Init_ERPRead_enc brake(::jeju::msg::ERPRead::_brake_type arg)
  {
    msg_.brake = std::move(arg);
    return Init_ERPRead_enc(msg_);
  }

private:
  ::jeju::msg::ERPRead msg_;
};

class Init_ERPRead_steer
{
public:
  explicit Init_ERPRead_steer(::jeju::msg::ERPRead & msg)
  : msg_(msg)
  {}
  Init_ERPRead_brake steer(::jeju::msg::ERPRead::_steer_type arg)
  {
    msg_.steer = std::move(arg);
    return Init_ERPRead_brake(msg_);
  }

private:
  ::jeju::msg::ERPRead msg_;
};

class Init_ERPRead_speed
{
public:
  explicit Init_ERPRead_speed(::jeju::msg::ERPRead & msg)
  : msg_(msg)
  {}
  Init_ERPRead_steer speed(::jeju::msg::ERPRead::_speed_type arg)
  {
    msg_.speed = std::move(arg);
    return Init_ERPRead_steer(msg_);
  }

private:
  ::jeju::msg::ERPRead msg_;
};

class Init_ERPRead_gear
{
public:
  explicit Init_ERPRead_gear(::jeju::msg::ERPRead & msg)
  : msg_(msg)
  {}
  Init_ERPRead_speed gear(::jeju::msg::ERPRead::_gear_type arg)
  {
    msg_.gear = std::move(arg);
    return Init_ERPRead_speed(msg_);
  }

private:
  ::jeju::msg::ERPRead msg_;
};

class Init_ERPRead_estop
{
public:
  explicit Init_ERPRead_estop(::jeju::msg::ERPRead & msg)
  : msg_(msg)
  {}
  Init_ERPRead_gear estop(::jeju::msg::ERPRead::_estop_type arg)
  {
    msg_.estop = std::move(arg);
    return Init_ERPRead_gear(msg_);
  }

private:
  ::jeju::msg::ERPRead msg_;
};

class Init_ERPRead_aorm
{
public:
  explicit Init_ERPRead_aorm(::jeju::msg::ERPRead & msg)
  : msg_(msg)
  {}
  Init_ERPRead_estop aorm(::jeju::msg::ERPRead::_aorm_type arg)
  {
    msg_.aorm = std::move(arg);
    return Init_ERPRead_estop(msg_);
  }

private:
  ::jeju::msg::ERPRead msg_;
};

class Init_ERPRead_x
{
public:
  explicit Init_ERPRead_x(::jeju::msg::ERPRead & msg)
  : msg_(msg)
  {}
  Init_ERPRead_aorm x(::jeju::msg::ERPRead::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_ERPRead_aorm(msg_);
  }

private:
  ::jeju::msg::ERPRead msg_;
};

class Init_ERPRead_t
{
public:
  explicit Init_ERPRead_t(::jeju::msg::ERPRead & msg)
  : msg_(msg)
  {}
  Init_ERPRead_x t(::jeju::msg::ERPRead::_t_type arg)
  {
    msg_.t = std::move(arg);
    return Init_ERPRead_x(msg_);
  }

private:
  ::jeju::msg::ERPRead msg_;
};

class Init_ERPRead_s
{
public:
  explicit Init_ERPRead_s(::jeju::msg::ERPRead & msg)
  : msg_(msg)
  {}
  Init_ERPRead_t s(::jeju::msg::ERPRead::_s_type arg)
  {
    msg_.s = std::move(arg);
    return Init_ERPRead_t(msg_);
  }

private:
  ::jeju::msg::ERPRead msg_;
};

class Init_ERPRead_header
{
public:
  Init_ERPRead_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ERPRead_s header(::jeju::msg::ERPRead::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_ERPRead_s(msg_);
  }

private:
  ::jeju::msg::ERPRead msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::jeju::msg::ERPRead>()
{
  return jeju::msg::builder::Init_ERPRead_header();
}

}  // namespace jeju

#endif  // JEJU__MSG__DETAIL__ERP_READ__BUILDER_HPP_
