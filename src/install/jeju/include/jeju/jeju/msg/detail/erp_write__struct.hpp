// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from jeju:msg/ERPWrite.idl
// generated code does not contain a copyright notice

#ifndef JEJU__MSG__DETAIL__ERP_WRITE__STRUCT_HPP_
#define JEJU__MSG__DETAIL__ERP_WRITE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__jeju__msg__ERPWrite __attribute__((deprecated))
#else
# define DEPRECATED__jeju__msg__ERPWrite __declspec(deprecated)
#endif

namespace jeju
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ERPWrite_
{
  using Type = ERPWrite_<ContainerAllocator>;

  explicit ERPWrite_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->is_auto = false;
      this->is_estop = false;
      this->gear = 0;
      this->speed = 0;
      this->steer = 0;
      this->brake = 0;
    }
  }

  explicit ERPWrite_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->is_auto = false;
      this->is_estop = false;
      this->gear = 0;
      this->speed = 0;
      this->steer = 0;
      this->brake = 0;
    }
  }

  // field types and members
  using _is_auto_type =
    bool;
  _is_auto_type is_auto;
  using _is_estop_type =
    bool;
  _is_estop_type is_estop;
  using _gear_type =
    uint8_t;
  _gear_type gear;
  using _speed_type =
    uint16_t;
  _speed_type speed;
  using _steer_type =
    int16_t;
  _steer_type steer;
  using _brake_type =
    uint8_t;
  _brake_type brake;

  // setters for named parameter idiom
  Type & set__is_auto(
    const bool & _arg)
  {
    this->is_auto = _arg;
    return *this;
  }
  Type & set__is_estop(
    const bool & _arg)
  {
    this->is_estop = _arg;
    return *this;
  }
  Type & set__gear(
    const uint8_t & _arg)
  {
    this->gear = _arg;
    return *this;
  }
  Type & set__speed(
    const uint16_t & _arg)
  {
    this->speed = _arg;
    return *this;
  }
  Type & set__steer(
    const int16_t & _arg)
  {
    this->steer = _arg;
    return *this;
  }
  Type & set__brake(
    const uint8_t & _arg)
  {
    this->brake = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    jeju::msg::ERPWrite_<ContainerAllocator> *;
  using ConstRawPtr =
    const jeju::msg::ERPWrite_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<jeju::msg::ERPWrite_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<jeju::msg::ERPWrite_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      jeju::msg::ERPWrite_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<jeju::msg::ERPWrite_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      jeju::msg::ERPWrite_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<jeju::msg::ERPWrite_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<jeju::msg::ERPWrite_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<jeju::msg::ERPWrite_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__jeju__msg__ERPWrite
    std::shared_ptr<jeju::msg::ERPWrite_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__jeju__msg__ERPWrite
    std::shared_ptr<jeju::msg::ERPWrite_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ERPWrite_ & other) const
  {
    if (this->is_auto != other.is_auto) {
      return false;
    }
    if (this->is_estop != other.is_estop) {
      return false;
    }
    if (this->gear != other.gear) {
      return false;
    }
    if (this->speed != other.speed) {
      return false;
    }
    if (this->steer != other.steer) {
      return false;
    }
    if (this->brake != other.brake) {
      return false;
    }
    return true;
  }
  bool operator!=(const ERPWrite_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ERPWrite_

// alias to use template instance with default allocator
using ERPWrite =
  jeju::msg::ERPWrite_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace jeju

#endif  // JEJU__MSG__DETAIL__ERP_WRITE__STRUCT_HPP_
