// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from jeju:msg/ERPRead.idl
// generated code does not contain a copyright notice

#ifndef JEJU__MSG__DETAIL__ERP_READ__STRUCT_HPP_
#define JEJU__MSG__DETAIL__ERP_READ__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__jeju__msg__ERPRead __attribute__((deprecated))
#else
# define DEPRECATED__jeju__msg__ERPRead __declspec(deprecated)
#endif

namespace jeju
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ERPRead_
{
  using Type = ERPRead_<ContainerAllocator>;

  explicit ERPRead_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->s = 0;
      this->t = 0;
      this->x = 0;
      this->aorm = 0;
      this->estop = 0;
      this->gear = 0;
      this->speed = 0;
      this->steer = 0;
      this->brake = 0;
      this->enc = 0l;
      this->alive = 0;
      this->etx0 = 0;
      this->etx1 = 0;
    }
  }

  explicit ERPRead_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->s = 0;
      this->t = 0;
      this->x = 0;
      this->aorm = 0;
      this->estop = 0;
      this->gear = 0;
      this->speed = 0;
      this->steer = 0;
      this->brake = 0;
      this->enc = 0l;
      this->alive = 0;
      this->etx0 = 0;
      this->etx1 = 0;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _s_type =
    uint8_t;
  _s_type s;
  using _t_type =
    uint8_t;
  _t_type t;
  using _x_type =
    uint8_t;
  _x_type x;
  using _aorm_type =
    uint8_t;
  _aorm_type aorm;
  using _estop_type =
    uint8_t;
  _estop_type estop;
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
  using _enc_type =
    int32_t;
  _enc_type enc;
  using _alive_type =
    uint8_t;
  _alive_type alive;
  using _etx0_type =
    uint8_t;
  _etx0_type etx0;
  using _etx1_type =
    uint8_t;
  _etx1_type etx1;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__s(
    const uint8_t & _arg)
  {
    this->s = _arg;
    return *this;
  }
  Type & set__t(
    const uint8_t & _arg)
  {
    this->t = _arg;
    return *this;
  }
  Type & set__x(
    const uint8_t & _arg)
  {
    this->x = _arg;
    return *this;
  }
  Type & set__aorm(
    const uint8_t & _arg)
  {
    this->aorm = _arg;
    return *this;
  }
  Type & set__estop(
    const uint8_t & _arg)
  {
    this->estop = _arg;
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
  Type & set__enc(
    const int32_t & _arg)
  {
    this->enc = _arg;
    return *this;
  }
  Type & set__alive(
    const uint8_t & _arg)
  {
    this->alive = _arg;
    return *this;
  }
  Type & set__etx0(
    const uint8_t & _arg)
  {
    this->etx0 = _arg;
    return *this;
  }
  Type & set__etx1(
    const uint8_t & _arg)
  {
    this->etx1 = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    jeju::msg::ERPRead_<ContainerAllocator> *;
  using ConstRawPtr =
    const jeju::msg::ERPRead_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<jeju::msg::ERPRead_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<jeju::msg::ERPRead_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      jeju::msg::ERPRead_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<jeju::msg::ERPRead_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      jeju::msg::ERPRead_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<jeju::msg::ERPRead_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<jeju::msg::ERPRead_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<jeju::msg::ERPRead_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__jeju__msg__ERPRead
    std::shared_ptr<jeju::msg::ERPRead_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__jeju__msg__ERPRead
    std::shared_ptr<jeju::msg::ERPRead_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ERPRead_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->s != other.s) {
      return false;
    }
    if (this->t != other.t) {
      return false;
    }
    if (this->x != other.x) {
      return false;
    }
    if (this->aorm != other.aorm) {
      return false;
    }
    if (this->estop != other.estop) {
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
    if (this->enc != other.enc) {
      return false;
    }
    if (this->alive != other.alive) {
      return false;
    }
    if (this->etx0 != other.etx0) {
      return false;
    }
    if (this->etx1 != other.etx1) {
      return false;
    }
    return true;
  }
  bool operator!=(const ERPRead_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ERPRead_

// alias to use template instance with default allocator
using ERPRead =
  jeju::msg::ERPRead_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace jeju

#endif  // JEJU__MSG__DETAIL__ERP_READ__STRUCT_HPP_
