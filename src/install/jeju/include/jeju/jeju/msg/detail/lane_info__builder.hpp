// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from jeju:msg/LaneInfo.idl
// generated code does not contain a copyright notice

#ifndef JEJU__MSG__DETAIL__LANE_INFO__BUILDER_HPP_
#define JEJU__MSG__DETAIL__LANE_INFO__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "jeju/msg/detail/lane_info__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace jeju
{

namespace msg
{

namespace builder
{

class Init_LaneInfo_speed_mode
{
public:
  explicit Init_LaneInfo_speed_mode(::jeju::msg::LaneInfo & msg)
  : msg_(msg)
  {}
  ::jeju::msg::LaneInfo speed_mode(::jeju::msg::LaneInfo::_speed_mode_type arg)
  {
    msg_.speed_mode = std::move(arg);
    return std::move(msg_);
  }

private:
  ::jeju::msg::LaneInfo msg_;
};

class Init_LaneInfo_lane_mode
{
public:
  explicit Init_LaneInfo_lane_mode(::jeju::msg::LaneInfo & msg)
  : msg_(msg)
  {}
  Init_LaneInfo_speed_mode lane_mode(::jeju::msg::LaneInfo::_lane_mode_type arg)
  {
    msg_.lane_mode = std::move(arg);
    return Init_LaneInfo_speed_mode(msg_);
  }

private:
  ::jeju::msg::LaneInfo msg_;
};

class Init_LaneInfo_center_line_yaw
{
public:
  explicit Init_LaneInfo_center_line_yaw(::jeju::msg::LaneInfo & msg)
  : msg_(msg)
  {}
  Init_LaneInfo_lane_mode center_line_yaw(::jeju::msg::LaneInfo::_center_line_yaw_type arg)
  {
    msg_.center_line_yaw = std::move(arg);
    return Init_LaneInfo_lane_mode(msg_);
  }

private:
  ::jeju::msg::LaneInfo msg_;
};

class Init_LaneInfo_center_line_y
{
public:
  explicit Init_LaneInfo_center_line_y(::jeju::msg::LaneInfo & msg)
  : msg_(msg)
  {}
  Init_LaneInfo_center_line_yaw center_line_y(::jeju::msg::LaneInfo::_center_line_y_type arg)
  {
    msg_.center_line_y = std::move(arg);
    return Init_LaneInfo_center_line_yaw(msg_);
  }

private:
  ::jeju::msg::LaneInfo msg_;
};

class Init_LaneInfo_center_line_x
{
public:
  Init_LaneInfo_center_line_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LaneInfo_center_line_y center_line_x(::jeju::msg::LaneInfo::_center_line_x_type arg)
  {
    msg_.center_line_x = std::move(arg);
    return Init_LaneInfo_center_line_y(msg_);
  }

private:
  ::jeju::msg::LaneInfo msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::jeju::msg::LaneInfo>()
{
  return jeju::msg::builder::Init_LaneInfo_center_line_x();
}

}  // namespace jeju

#endif  // JEJU__MSG__DETAIL__LANE_INFO__BUILDER_HPP_
