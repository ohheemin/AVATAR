// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from jeju:msg/LaneData.idl
// generated code does not contain a copyright notice

#ifndef JEJU__MSG__DETAIL__LANE_DATA__BUILDER_HPP_
#define JEJU__MSG__DETAIL__LANE_DATA__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "jeju/msg/detail/lane_data__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace jeju
{

namespace msg
{

namespace builder
{

class Init_LaneData_right_points
{
public:
  explicit Init_LaneData_right_points(::jeju::msg::LaneData & msg)
  : msg_(msg)
  {}
  ::jeju::msg::LaneData right_points(::jeju::msg::LaneData::_right_points_type arg)
  {
    msg_.right_points = std::move(arg);
    return std::move(msg_);
  }

private:
  ::jeju::msg::LaneData msg_;
};

class Init_LaneData_left_points
{
public:
  explicit Init_LaneData_left_points(::jeju::msg::LaneData & msg)
  : msg_(msg)
  {}
  Init_LaneData_right_points left_points(::jeju::msg::LaneData::_left_points_type arg)
  {
    msg_.left_points = std::move(arg);
    return Init_LaneData_right_points(msg_);
  }

private:
  ::jeju::msg::LaneData msg_;
};

class Init_LaneData_center_points
{
public:
  explicit Init_LaneData_center_points(::jeju::msg::LaneData & msg)
  : msg_(msg)
  {}
  Init_LaneData_left_points center_points(::jeju::msg::LaneData::_center_points_type arg)
  {
    msg_.center_points = std::move(arg);
    return Init_LaneData_left_points(msg_);
  }

private:
  ::jeju::msg::LaneData msg_;
};

class Init_LaneData_steer
{
public:
  explicit Init_LaneData_steer(::jeju::msg::LaneData & msg)
  : msg_(msg)
  {}
  Init_LaneData_center_points steer(::jeju::msg::LaneData::_steer_type arg)
  {
    msg_.steer = std::move(arg);
    return Init_LaneData_center_points(msg_);
  }

private:
  ::jeju::msg::LaneData msg_;
};

class Init_LaneData_detected
{
public:
  Init_LaneData_detected()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LaneData_steer detected(::jeju::msg::LaneData::_detected_type arg)
  {
    msg_.detected = std::move(arg);
    return Init_LaneData_steer(msg_);
  }

private:
  ::jeju::msg::LaneData msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::jeju::msg::LaneData>()
{
  return jeju::msg::builder::Init_LaneData_detected();
}

}  // namespace jeju

#endif  // JEJU__MSG__DETAIL__LANE_DATA__BUILDER_HPP_
