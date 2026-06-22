// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from jeju:msg/LaneInfo.idl
// generated code does not contain a copyright notice

#ifndef JEJU__MSG__DETAIL__LANE_INFO__STRUCT_HPP_
#define JEJU__MSG__DETAIL__LANE_INFO__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__jeju__msg__LaneInfo __attribute__((deprecated))
#else
# define DEPRECATED__jeju__msg__LaneInfo __declspec(deprecated)
#endif

namespace jeju
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LaneInfo_
{
  using Type = LaneInfo_<ContainerAllocator>;

  explicit LaneInfo_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->lane_mode = false;
      this->speed_mode = 0;
    }
  }

  explicit LaneInfo_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->lane_mode = false;
      this->speed_mode = 0;
    }
  }

  // field types and members
  using _center_line_x_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _center_line_x_type center_line_x;
  using _center_line_y_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _center_line_y_type center_line_y;
  using _center_line_yaw_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _center_line_yaw_type center_line_yaw;
  using _lane_mode_type =
    bool;
  _lane_mode_type lane_mode;
  using _speed_mode_type =
    int8_t;
  _speed_mode_type speed_mode;

  // setters for named parameter idiom
  Type & set__center_line_x(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->center_line_x = _arg;
    return *this;
  }
  Type & set__center_line_y(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->center_line_y = _arg;
    return *this;
  }
  Type & set__center_line_yaw(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->center_line_yaw = _arg;
    return *this;
  }
  Type & set__lane_mode(
    const bool & _arg)
  {
    this->lane_mode = _arg;
    return *this;
  }
  Type & set__speed_mode(
    const int8_t & _arg)
  {
    this->speed_mode = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    jeju::msg::LaneInfo_<ContainerAllocator> *;
  using ConstRawPtr =
    const jeju::msg::LaneInfo_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<jeju::msg::LaneInfo_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<jeju::msg::LaneInfo_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      jeju::msg::LaneInfo_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<jeju::msg::LaneInfo_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      jeju::msg::LaneInfo_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<jeju::msg::LaneInfo_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<jeju::msg::LaneInfo_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<jeju::msg::LaneInfo_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__jeju__msg__LaneInfo
    std::shared_ptr<jeju::msg::LaneInfo_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__jeju__msg__LaneInfo
    std::shared_ptr<jeju::msg::LaneInfo_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LaneInfo_ & other) const
  {
    if (this->center_line_x != other.center_line_x) {
      return false;
    }
    if (this->center_line_y != other.center_line_y) {
      return false;
    }
    if (this->center_line_yaw != other.center_line_yaw) {
      return false;
    }
    if (this->lane_mode != other.lane_mode) {
      return false;
    }
    if (this->speed_mode != other.speed_mode) {
      return false;
    }
    return true;
  }
  bool operator!=(const LaneInfo_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LaneInfo_

// alias to use template instance with default allocator
using LaneInfo =
  jeju::msg::LaneInfo_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace jeju

#endif  // JEJU__MSG__DETAIL__LANE_INFO__STRUCT_HPP_
