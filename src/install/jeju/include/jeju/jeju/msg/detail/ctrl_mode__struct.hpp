// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from jeju:msg/CtrlMode.idl
// generated code does not contain a copyright notice

#ifndef JEJU__MSG__DETAIL__CTRL_MODE__STRUCT_HPP_
#define JEJU__MSG__DETAIL__CTRL_MODE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__jeju__msg__CtrlMode __attribute__((deprecated))
#else
# define DEPRECATED__jeju__msg__CtrlMode __declspec(deprecated)
#endif

namespace jeju
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct CtrlMode_
{
  using Type = CtrlMode_<ContainerAllocator>;

  explicit CtrlMode_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->ctrl_algo = 0;
      this->ctrl_speed = 0;
    }
  }

  explicit CtrlMode_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->ctrl_algo = 0;
      this->ctrl_speed = 0;
    }
  }

  // field types and members
  using _ctrl_algo_type =
    int8_t;
  _ctrl_algo_type ctrl_algo;
  using _ctrl_speed_type =
    int8_t;
  _ctrl_speed_type ctrl_speed;

  // setters for named parameter idiom
  Type & set__ctrl_algo(
    const int8_t & _arg)
  {
    this->ctrl_algo = _arg;
    return *this;
  }
  Type & set__ctrl_speed(
    const int8_t & _arg)
  {
    this->ctrl_speed = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    jeju::msg::CtrlMode_<ContainerAllocator> *;
  using ConstRawPtr =
    const jeju::msg::CtrlMode_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<jeju::msg::CtrlMode_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<jeju::msg::CtrlMode_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      jeju::msg::CtrlMode_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<jeju::msg::CtrlMode_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      jeju::msg::CtrlMode_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<jeju::msg::CtrlMode_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<jeju::msg::CtrlMode_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<jeju::msg::CtrlMode_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__jeju__msg__CtrlMode
    std::shared_ptr<jeju::msg::CtrlMode_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__jeju__msg__CtrlMode
    std::shared_ptr<jeju::msg::CtrlMode_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const CtrlMode_ & other) const
  {
    if (this->ctrl_algo != other.ctrl_algo) {
      return false;
    }
    if (this->ctrl_speed != other.ctrl_speed) {
      return false;
    }
    return true;
  }
  bool operator!=(const CtrlMode_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct CtrlMode_

// alias to use template instance with default allocator
using CtrlMode =
  jeju::msg::CtrlMode_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace jeju

#endif  // JEJU__MSG__DETAIL__CTRL_MODE__STRUCT_HPP_
