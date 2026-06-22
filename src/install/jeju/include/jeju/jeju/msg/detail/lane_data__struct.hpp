// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from jeju:msg/LaneData.idl
// generated code does not contain a copyright notice

#ifndef JEJU__MSG__DETAIL__LANE_DATA__STRUCT_HPP_
#define JEJU__MSG__DETAIL__LANE_DATA__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'center_points'
// Member 'left_points'
// Member 'right_points'
#include "geometry_msgs/msg/detail/vector3__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__jeju__msg__LaneData __attribute__((deprecated))
#else
# define DEPRECATED__jeju__msg__LaneData __declspec(deprecated)
#endif

namespace jeju
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LaneData_
{
  using Type = LaneData_<ContainerAllocator>;

  explicit LaneData_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->detected = false;
      this->steer = 0.0f;
    }
  }

  explicit LaneData_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->detected = false;
      this->steer = 0.0f;
    }
  }

  // field types and members
  using _detected_type =
    bool;
  _detected_type detected;
  using _steer_type =
    float;
  _steer_type steer;
  using _center_points_type =
    std::vector<geometry_msgs::msg::Vector3_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<geometry_msgs::msg::Vector3_<ContainerAllocator>>>;
  _center_points_type center_points;
  using _left_points_type =
    std::vector<geometry_msgs::msg::Vector3_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<geometry_msgs::msg::Vector3_<ContainerAllocator>>>;
  _left_points_type left_points;
  using _right_points_type =
    std::vector<geometry_msgs::msg::Vector3_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<geometry_msgs::msg::Vector3_<ContainerAllocator>>>;
  _right_points_type right_points;

  // setters for named parameter idiom
  Type & set__detected(
    const bool & _arg)
  {
    this->detected = _arg;
    return *this;
  }
  Type & set__steer(
    const float & _arg)
  {
    this->steer = _arg;
    return *this;
  }
  Type & set__center_points(
    const std::vector<geometry_msgs::msg::Vector3_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<geometry_msgs::msg::Vector3_<ContainerAllocator>>> & _arg)
  {
    this->center_points = _arg;
    return *this;
  }
  Type & set__left_points(
    const std::vector<geometry_msgs::msg::Vector3_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<geometry_msgs::msg::Vector3_<ContainerAllocator>>> & _arg)
  {
    this->left_points = _arg;
    return *this;
  }
  Type & set__right_points(
    const std::vector<geometry_msgs::msg::Vector3_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<geometry_msgs::msg::Vector3_<ContainerAllocator>>> & _arg)
  {
    this->right_points = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    jeju::msg::LaneData_<ContainerAllocator> *;
  using ConstRawPtr =
    const jeju::msg::LaneData_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<jeju::msg::LaneData_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<jeju::msg::LaneData_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      jeju::msg::LaneData_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<jeju::msg::LaneData_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      jeju::msg::LaneData_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<jeju::msg::LaneData_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<jeju::msg::LaneData_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<jeju::msg::LaneData_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__jeju__msg__LaneData
    std::shared_ptr<jeju::msg::LaneData_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__jeju__msg__LaneData
    std::shared_ptr<jeju::msg::LaneData_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LaneData_ & other) const
  {
    if (this->detected != other.detected) {
      return false;
    }
    if (this->steer != other.steer) {
      return false;
    }
    if (this->center_points != other.center_points) {
      return false;
    }
    if (this->left_points != other.left_points) {
      return false;
    }
    if (this->right_points != other.right_points) {
      return false;
    }
    return true;
  }
  bool operator!=(const LaneData_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LaneData_

// alias to use template instance with default allocator
using LaneData =
  jeju::msg::LaneData_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace jeju

#endif  // JEJU__MSG__DETAIL__LANE_DATA__STRUCT_HPP_
