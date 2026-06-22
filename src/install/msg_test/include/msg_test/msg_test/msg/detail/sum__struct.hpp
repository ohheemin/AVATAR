// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from msg_test:msg/Sum.idl
// generated code does not contain a copyright notice

#ifndef MSG_TEST__MSG__DETAIL__SUM__STRUCT_HPP_
#define MSG_TEST__MSG__DETAIL__SUM__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__msg_test__msg__Sum __attribute__((deprecated))
#else
# define DEPRECATED__msg_test__msg__Sum __declspec(deprecated)
#endif

namespace msg_test
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Sum_
{
  using Type = Sum_<ContainerAllocator>;

  explicit Sum_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->a = 0l;
      this->b = 0l;
      this->sum = 0l;
    }
  }

  explicit Sum_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->a = 0l;
      this->b = 0l;
      this->sum = 0l;
    }
  }

  // field types and members
  using _a_type =
    int32_t;
  _a_type a;
  using _b_type =
    int32_t;
  _b_type b;
  using _sum_type =
    int32_t;
  _sum_type sum;

  // setters for named parameter idiom
  Type & set__a(
    const int32_t & _arg)
  {
    this->a = _arg;
    return *this;
  }
  Type & set__b(
    const int32_t & _arg)
  {
    this->b = _arg;
    return *this;
  }
  Type & set__sum(
    const int32_t & _arg)
  {
    this->sum = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    msg_test::msg::Sum_<ContainerAllocator> *;
  using ConstRawPtr =
    const msg_test::msg::Sum_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<msg_test::msg::Sum_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<msg_test::msg::Sum_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      msg_test::msg::Sum_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<msg_test::msg::Sum_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      msg_test::msg::Sum_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<msg_test::msg::Sum_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<msg_test::msg::Sum_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<msg_test::msg::Sum_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__msg_test__msg__Sum
    std::shared_ptr<msg_test::msg::Sum_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__msg_test__msg__Sum
    std::shared_ptr<msg_test::msg::Sum_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Sum_ & other) const
  {
    if (this->a != other.a) {
      return false;
    }
    if (this->b != other.b) {
      return false;
    }
    if (this->sum != other.sum) {
      return false;
    }
    return true;
  }
  bool operator!=(const Sum_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Sum_

// alias to use template instance with default allocator
using Sum =
  msg_test::msg::Sum_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace msg_test

#endif  // MSG_TEST__MSG__DETAIL__SUM__STRUCT_HPP_
